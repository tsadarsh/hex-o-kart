#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define motA1 9
#define motA2 10
#define motB1 13
#define motB2 15
#define ENC_R1 5
#define ENC_R2 4
#define ENC_L1 14
#define ENC_L2 12

char *SSID = "RUDRA_2.4G";
char *PWD = "hackitifucan";
const char *FWD = "10";
const char *BWD = "01";

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
  pinMode(motA1, OUTPUT);
  pinMode(motA2, OUTPUT);
  pinMode(motB1, OUTPUT);
  pinMode(motB2, OUTPUT);

  // Encoders
  pinMode (ENC_R1,INPUT);
  pinMode (ENC_R2,INPUT);
  pinMode (ENC_L1,INPUT);
  pinMode (ENC_L2,INPUT);
}

void pulldown_motor_pins() {
  digitalWrite(motA1, LOW);
  digitalWrite(motA2, LOW);
  digitalWrite(motB1, LOW);
  digitalWrite(motB2, LOW);
}

void setup() {
  // Begin serial communication
  Serial.begin(9600);

  // Connect to Wifi and start MQTT
  connectToWiFi();
  setupMQTT();

  // Configure pins and INPUT or OUTPUT
  setup_pinMode();

  // Do not power the motors at start
  pulldown_motor_pins();

  // Read encoder value at start
  right_aLastState = digitalRead(ENC_R1);
  left_aLastState = digitalRead(ENC_L1);

  // Enable INTERRUPT in pins attached to encoder  
  attachInterrupt(digitalPinToInterrupt(ENC_R1), right_update, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_L1), left_update, CHANGE);
}

void loop() {
  if (!mqttClient.connected())
    reconnect();
  mqttClient.loop();
}

void reconnect() {
  Serial.println("Connecting to MQTT Broker...");
  while (!mqttClient.connected()) {
      Serial.println("Reconnecting to MQTT Broker..");
      String clientId = "ESP32Client-";
      clientId += String(random(0xffff), HEX);
      
      if (mqttClient.connect(clientId.c_str())) {
        Serial.println("Connected.");
        // subscribe to topic
        mqttClient.subscribe("/swa/commands");
      }
      
  }
}

void connectToWiFi() {
  Serial.print("Connectiog to ");
 
  WiFi.begin(SSID, PWD);
  Serial.println(SSID);
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
    //Serial.println(chars);
    if(!strcmp(chars, FWD)) {
      Serial.println("Forward");
      digitalWrite(motA1, HIGH);
      digitalWrite(motA2, LOW);
    }
    else if(!strcmp(chars, BWD)) {
      Serial.println("Reverse");
      digitalWrite(motA1, LOW);
      digitalWrite(motA2, HIGH);
    }
    else {
      Serial.println("Stopping");
      digitalWrite(motA1, LOW);
      digitalWrite(motA2, LOW);
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

 void right_update() {
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

  void left_update() {
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
