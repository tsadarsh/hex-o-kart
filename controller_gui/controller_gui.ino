#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#define IN1 12
#define IN2 13

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
}

void loop() {
  if (!mqttClient.connected())
    reconnect();
  mqttClient.loop();
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
//  Serial.print("Callback - ");
//  Serial.print("Message:");
//  for (int i = 0; i < length; i++) {
//    Serial.print((char)payload[i]);
//  }
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
