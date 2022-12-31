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

## example output captured from my other project 
```
t[001730]l[1040]f[operator()] Requested: /reset
ets Jun  8 2016 00:22:57

rst:0xc (SW_CPU_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:2
load:0x3fff0030,len:1184
load:0x40078000,len:13132
load:0x40080400,len:3036
entry 0x400805e4
t[000000]l[0035]f[begin] Error: Failed to initialize SD card
t[000004]l[0048]f[begin] SPIFFS OK
t[000004]l[0248]f[LoadStructs] Loading system from SPIFFS
t[000004]l[0080]f[Load] Loading /SysState.bin	successfully
t[000004]l[0082]f[Load] 36 out of 36 Bytes read. filesize Match.
t[000004]l[0080]f[Load] Loading /Pressure.bin	successfully
t[000004]l[0082]f[Load] 24 out of 24 Bytes read. filesize Match.
t[000004]l[0080]f[Load] Loading /Flow.bin	successfully
t[000004]l[0082]f[Load] 40 out of 40 Bytes read. filesize Match.
t[000004]l[0080]f[Load] Loading /Barrels.bin	successfully
t[000004]l[0082]f[Load] 216 out of 216 Bytes read. filesize Match.
t[000006]l[0031]f[begin] ESSID: *hidden* IP: 192.168.1.25
t[000009]l[0191]f[operator()] Requested: /manual
```