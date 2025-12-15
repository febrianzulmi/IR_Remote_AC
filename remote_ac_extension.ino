#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <ir_Daikin.h>

#define LED_PIN 2
#define IR_SEND_PIN 4
#define IR_INDICATOR_PIN 5

IRDaikinESP ac(IR_SEND_PIN);
bool isAcOn = false;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  pinMode(IR_INDICATOR_PIN, OUTPUT);
  digitalWrite(IR_INDICATOR_PIN, LOW);
  delay(1000);
  while (Serial.available() > 0) {
    Serial.read();
  }
  ac.begin();
}

void loop() {
  if (Serial.available() == 0) {
    return;
  }
  
  String command = Serial.readStringUntil('\n');
  command.trim();
  command.toUpperCase();
  
  if (command.length() == 0) {
    return;
  }
  
  if (command == "AC_ON") {
    digitalWrite(LED_PIN, LOW);
    turnACOn();
    delay(100);
    digitalWrite(LED_PIN, HIGH);
    isAcOn = true;
    return;
  }
  
  if (command == "AC_OFF") {
    digitalWrite(LED_PIN, LOW);
    turnACOff();
    delay(100);
    digitalWrite(LED_PIN, HIGH);
    isAcOn = false;
    return;
  }
  
  if (command == "SWING_ON") {
    digitalWrite(LED_PIN, LOW);
    enableSwing();
    delay(100);
    digitalWrite(LED_PIN, HIGH);
    return;
  }
  
  if (command == "SWING_OFF") {
    digitalWrite(LED_PIN, LOW);
    disableSwing();
    delay(100);
    digitalWrite(LED_PIN, HIGH);
    return;
  }
  
  if (command.startsWith("TEMP_")) {
    String tempStr = command.substring(5);
    int temp = tempStr.toInt();
    digitalWrite(LED_PIN, LOW);
    setTemperature(temp);
    delay(100);
    digitalWrite(LED_PIN, HIGH);
    return;
  }
}