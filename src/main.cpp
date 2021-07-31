/*
Copyright 2021 Evgeni Vi
more info and license - soon

Web interface & Datalogger for Serial devices

ESP32 default UART2:    rx:GPIO16   tx:GPIO17   3.3V TTL Level
*/
#include <Arduino.h>
#include "SPIFFS.h"

#define BAUD 115200
#define FILENAME "/serial.log"

// Globals
FS *disk = &SPIFFS; // default
File file;
//WiFiUDP UDP;
//AsyncWebServer server(80);

void AppendToFile(char input) {
  file.write(input);
  if (!(file.size() % 4096)) // flush every 4kB
    file.flush();
}

void CheckAvail(){
  while (Serial2.available()) {
    AppendToFile(char(Serial2.read()));
  }
}

void CheckSave(){
  if (!digitalRead(0)){ // pin 0 is "boot" button on esp32
    file.flush();
    digitalWrite(2,HIGH); // pin 2 is onboard LED
    delay(500);
    digitalWrite(2,LOW);
    while (!digitalRead(0)); // wait untill released
  }
}

void HardReset(){
  SPIFFS.format();
}

void setup() {
  Serial2.begin(BAUD, SERIAL_8N1);
  SPIFFS.begin();
  file = SPIFFS.open(FILENAME, "a+");
}

void loop() {
  CheckAvail();
  CheckSave();
}