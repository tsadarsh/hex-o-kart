#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoOTA.h>
#define mot1 4
#define mot2 0
#define motA_pwm 2
#define motB_pwm 14
#define ENC_R1 15
#define ENC_R2 5
#define ENC_L1 12
#define ENC_L2 13

#ifndef STASSID
#define STASSID "RUDRA_2.4G"
#define STAPSK  "hackitifucan"
#endif

const char* ssid = STASSID;
char* password = STAPSK;
const char *FWD = "2";
const char *STP = "1"; 
const char *BWD = "0";
const char *MOTOR = "/motor";

int right_counter = 0; 
int right_aState;
int right_aLastState;
int right_counter_last = 0;
int left_counter = 0; 
int left_aState;
int left_aLastState; 
int left_counter_last = 0;
long now = 0;
long last_time = 0;
long msg_time_interval = 100; // set time between each msg publish

// MQTT client
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient); 
char *mqttServer = "broker.hivemq.com";
int mqttPort = 1883;

void setup_pinMode() {
  // Motors
  pinMode(mot1, OUTPUT);
  pinMode(mot2, OUTPUT);

  // Encoders
  pinMode (ENC_R1,INPUT);
  pinMode (ENC_R2,INPUT);
  pinMode (ENC_L1,INPUT);
  pinMode (ENC_L2,INPUT);

  // PWM
  pinMode(motA_pwm, OUTPUT);
  pinMode(motB_pwm, OUTPUT);
}

void pulldown_motor_pins() {
  digitalWrite(mot1, LOW);
  digitalWrite(mot2, LOW);
}

void setup() {
  // Begin serial communication
  Serial.begin(115200);

  // Configure pins and INPUT or OUTPUT
  setup_pinMode();

  // Do not power the motors at start
  pulldown_motor_pins();

  // Connect to Wifi
  connectToWiFi();

  // Establish OTA
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.begin();
  
  setupMQTT();

  // Analog write range
//  analogWriteRange(100);

  // Read encoder value at start
  right_aLastState = digitalRead(ENC_R1);
  left_aLastState = digitalRead(ENC_L1);

  // Enable INTERRUPT in pins attached to encoder  
  attachInterrupt(digitalPinToInterrupt(ENC_R1), right_update, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_L1), left_update, CHANGE);
}

void loop() {
  ArduinoOTA.handle();
  
  if (!mqttClient.connected())
    reconnect();
  mqttClient.loop();
}

void reconnect() {
  Serial.println("Connecting to MQTT Broker...");
  while (!mqttClient.connected()) {
      Serial.println("Reconnecting to MQTT Broker..");
      String clientId = "ESP8266Client-";
      clientId += String(random(0xffff), HEX);
      
      if (mqttClient.connect(clientId.c_str())) {
        Serial.println("Connected.");
        // subscribe to topic
          mqttClient.subscribe("/motor");
      }
      
  }
}

void connectToWiFi() {
  Serial.print("Connectiog to ");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("Connected.");
}

void setupMQTT() {
  mqttClient.setServer(mqttServer, mqttPort);
  // set the callback function
  mqttClient.setCallback(callback);
}

void callback(char* topic, byte* payload, unsigned int length) {
    char chars[length+1];
    memcpy(chars, payload, length);
    chars[length] = '\0';
    String chars_str = String(chars);
    Serial.print("str: ");
    Serial.println(chars_str);
    Serial.print("Topic: ");
    Serial.println(topic);
    Serial.print("Recv: ");
    Serial.println(chars);
    String dir = chars_str.substring(0, 1);
    String left_mot_pwm = chars_str.substring(2, 6);
    String right_mot_pwm = chars_str.substring(7, 11);
    Serial.print("Dir: ");
    Serial.println(dir);
    Serial.print("L: ");
    Serial.println(left_mot_pwm);
    Serial.print("R: ");
    Serial.println(right_mot_pwm);

    analogWrite(motA_pwm, left_mot_pwm.toInt());
    analogWrite(motB_pwm, right_mot_pwm.toInt());

    if(dir == FWD) {
      // move forward
      Serial.println("FWD");
      digitalWrite(mot1, HIGH);
      digitalWrite(mot2, LOW);
    }
    else if(dir == BWD) {
      // move reverse
      Serial.println("BWD");
      digitalWrite(mot1, LOW);
      digitalWrite(mot2, HIGH);
    }
}

void publish_right() {
  char right_e[8];
  itoa(right_counter, right_e, 10);
  mqttClient.publish("/swa/encoder/right", right_e);
}

void publish_left() {
  char left_e[8];
  itoa(left_counter, left_e, 10);
  mqttClient.publish("/swa/encoder/left", left_e);
}

ICACHE_RAM_ATTR void right_update() {
    right_aState = digitalRead(ENC_R1); // Reads the "current" state of the A
   // If the previous and the current state of the A are different, that means a Pulse has occured
   if (right_aState != right_aLastState){     
     // If the outputB state is different to the A state, that means the encoder is rotating clockwise
     if (digitalRead(ENC_R2) != right_aState) { 
       right_counter ++;
     } else {
       right_counter --;
     }
   } 
   right_aLastState = right_aState;
   publish_right();
 }

ICACHE_RAM_ATTR void left_update() {
    left_aState = digitalRead(ENC_L1); // Reads the "current" state of the A
   // If the previous and the current state of the A are different, that means a Pulse has occured
   if (left_aState != left_aLastState){     
     // If the outputB state is different to the A state, that means the encoder is rotating clockwise
     if (digitalRead(ENC_L2) != left_aState) { 
       left_counter ++;
     } else {
       left_counter --;
     }
   } 
   left_aLastState = left_aState;
   publish_left();
 }
