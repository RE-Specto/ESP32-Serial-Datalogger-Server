# ESP32-Serial-Datalogger-Server
 - a simple device uses ESP32 to interract with a serial device (can be another MCU, a sensor or basically anything using serial communication) via webUI.
 - datalogging capabilities using built in flash (+sdcard support later).
 - ESP32 default UART2:    rx:GPIO16   tx:GPIO17   3.3V TTL Level
 - if using 3v3 boards (like the ESP32) to monitor a 5v sensor, a level shifter should be added   
  (though a simple voltage divider, while not the best solution, is sometimes sufficient)
 - proper WebUI will be imlemented soon. right now to view the newlines correctly, you can 'view source' on the address, so you can see the serial data as-is.
 - receive-only right now. sending data to the sensor will be implemented later.
 - hardcoded to 115200, change manually in the code to the desired data rate. 

## 2do:
- [x] save serial data to file
- [x] web server
- [x] wifi manager
- [ ] esp8266 support
- [x] Add OTA update
- [ ] persistent settings file
- [ ] webUI
- [ ] Server-Sent Events or WebSocket
- [ ] log filtering by severity
- [ ] bi-directional serial communication
- [ ] sd card support
- [ ] send syslog
- [ ] telnet

## useful links:
[websockets vs server-sent events](https://stackoverflow.com/questions/5195452/websockets-vs-server-sent-events-eventsource)

[Server-Sent Events](https://github.com/me-no-dev/ESPAsyncWebServer#async-event-source-plugin)

[syslog](https://github.com/arcao/Syslog)
