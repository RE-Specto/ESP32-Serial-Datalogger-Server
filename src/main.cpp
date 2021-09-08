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
#define FILE_LOG "/serial.log"
#define ONBOARD_LED 1 // pin 2 according to google, pin 1 in my board

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
    digitalWrite(ONBOARD_LED,LOW); // onboard LED
    delay(500);
    digitalWrite(ONBOARD_LED,HIGH);
    while (!digitalRead(0)); // wait here untill button is released
  }
}

// return to initial settings
void HardReset(){
  SPIFFS.format();
  // add wifi reset here
}

void setupServer()
{
    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->redirect("/getfile"); //untill implemented
    });

    server.on("/getfile", HTTP_GET, [](AsyncWebServerRequest *request) {
        if(!disk -> exists(FILE_LOG)){
            request->send(200, "text/html", "<html><body><center><h1>check SD Card please</h1></center></body></html>");
            }
        request->send(*disk, FILE_LOG, String(), false);
    });

    server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(404);
    });

    server.on("/reset", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->redirect("/");
        vTaskDelay(100 / portTICK_PERIOD_MS); // to prevent reset before redirect
        ESP.restart();
    });

    // Start server
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
    server.begin();
}

void setup() {
  pinMode(ONBOARD_LED,OUTPUT);
  digitalWrite(ONBOARD_LED,HIGH); // in my case the LED was inverted
  AsyncWiFiManager wifiManager(&server, &dns);
  wifiManager.setDebugOutput(false);
  wifiManager.setConfigPortalTimeout(180);  // 3 minutes
  wifiManager.autoConnect("AutoConnectAP"); // will stop here if no wifi connected
  Serial2.begin(SERIAL_BAUD, SERIAL_8N1);
  Serial2.setRxBufferSize(SERIAL_SIZE_RX);
  SPIFFS.begin();
  file = SPIFFS.open(FILE_LOG, "a+");
  setupServer();
}

void loop() {
  CheckAvail();
  CheckSave();
}