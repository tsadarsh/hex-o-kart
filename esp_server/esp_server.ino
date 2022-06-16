#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#define IN1 12
#define IN2 13
#define right_enc_A 21
#define right_enc_B 19
#define left_enc_A 34
#define left_enc_B 35

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
const char *SSID = "oneplus_tsa";
const char *PWD = "password0707";
const char *FWD = "10";
const char *BWD = "01";

// MQTT client
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient); 
char *mqttServer = "broker.hivemq.com";
int mqttPort = 1883;

void setup() {
  Serial.begin(9600);
  connectToWiFi();
  setupMQTT();
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  pinMode (right_enc_A,INPUT);
  pinMode (right_enc_B,INPUT);
  pinMode (left_enc_A,INPUT);
  pinMode (left_enc_B,INPUT);
  right_aLastState = digitalRead(right_enc_A);
  left_aLastState = digitalRead(left_enc_A);   
  attachInterrupt(digitalPinToInterrupt(right_enc_A), right_update, CHANGE);
  attachInterrupt(digitalPinToInterrupt(left_enc_A), left_update, CHANGE);
}

void loop() {
  if (!mqttClient.connected())
    reconnect();
  mqttClient.loop();
  long now = millis();
  if (now - last_time > msg_time_interval) {
    char left_e[8];
    char right_e[8];
    itoa(left_counter, left_e, 10);
    itoa(right_counter, right_e, 10);
      mqttClient.publish("/swa/encoder/left", left_e);
      mqttClient.publish("/swa/encoder/right", right_e);
    last_time = now;
  }
}

 void right_update() {
    right_aState = digitalRead(right_enc_A); // Reads the "current" state of the A
   // If the previous and the current state of the A are different, that means a Pulse has occured
   if (right_aState != right_aLastState){     
     // If the outputB state is different to the A state, that means the encoder is rotating clockwise
     if (digitalRead(right_enc_B) != right_aState) { 
       right_counter ++;
     } else {
       right_counter --;
     }
   } 
   right_aLastState = right_aState;
 }

  void left_update() {
    left_aState = digitalRead(left_enc_A); // Reads the "current" state of the A
   // If the previous and the current state of the A are different, that means a Pulse has occured
   if (left_aState != left_aLastState){     
     // If the outputB state is different to the A state, that means the encoder is rotating clockwise
     if (digitalRead(left_enc_B) != left_aState) { 
       left_counter ++;
     } else {
       left_counter --;
     }
   } 
   left_aLastState = left_aState;
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
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
    }
    else if(!strcmp(chars, BWD)) {
      Serial.println("Reverse");
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
    }
    else {
      Serial.println("Stopping");
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
    }
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
