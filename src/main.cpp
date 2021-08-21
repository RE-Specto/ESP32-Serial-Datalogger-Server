/*
Copyright 2021 Evgeni Vi
more info and license - soon

Web interface & Datalogger for Serial devices

ESP32 default UART2:    rx:GPIO16   tx:GPIO17   3.3V TTL Level
*/
#include <Arduino.h>
#include "SPIFFS.h"
#include <ESPAsyncWebServer.h>
#include <ESPAsyncWiFiManager.h>

#define SERIAL_BAUD 115200
#define SERIAL_SIZE_RX  16384
#define FILENAME "/serial.log"

// Globals
FS *disk = &SPIFFS; // default
File file;
AsyncWebServer server(80);
DNSServer dns;

// write one char to file buffer
// save changes every 4kB
void AppendToFile(char input) {
  file.write(input);
  if (!(file.size() % 4096)) // flush every 4kB
    file.flush();
}

// checks Serial2 for data
void CheckAvail(){
  while (Serial2.available()) {
    AppendToFile(char(Serial2.read()));
  }
}

// save file by hardware button press
void CheckSave(){
  if (!digitalRead(0)){ // pin 0 is "boot" button on esp32
    file.flush();
    digitalWrite(2,HIGH); // pin 2 is onboard LED
    delay(500);
    digitalWrite(2,LOW);
    while (!digitalRead(0)); // wait here untill button is released
  }
}

// return to initial settings
void HardReset(){
  SPIFFS.format();
  // add wifi reset here
}

void setup() {
  AsyncWiFiManager wifiManager(&server, &dns);
  wifiManager.setDebugOutput(false);
  wifiManager.setConfigPortalTimeout(180);  // 3 minutes
  wifiManager.autoConnect("AutoConnectAP"); // will stop here if no wifi connected
  Serial2.begin(SERIAL_BAUD, SERIAL_8N1);
  Serial2.setRxBufferSize(SERIAL_SIZE_RX);
  SPIFFS.begin();
  file = SPIFFS.open(FILENAME, "a+");
}

void loop() {
  CheckAvail();
  CheckSave();
}