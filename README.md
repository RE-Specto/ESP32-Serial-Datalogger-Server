# ESP32-Serial-Datalogger-Server
## project in early development. 
 - a simple device uses ESP32 to interract with a serial device (another microsontroller, or a sensor) via webUI.
 - datalogging capabilities using built in flash (+sdcard support later).
 - ESP32 default UART2:    rx:GPIO16   tx:GPIO17   3.3V TTL Level

---
## 2do:
- [x] save serial data to file
- [x] web server
- [x] wifi manager
- [ ] esp8266 support
- [ ] Add OTA update
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