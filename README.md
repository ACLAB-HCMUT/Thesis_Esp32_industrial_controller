
<a href="https://github.com/ACLAB-HCMUT"><img src="https://raw.githubusercontent.com/ACLAB-HCMUT/Common/main/Assets/ACLAB_IMG_1.png" alt="ACLAB logo" title="ACLAB" align="right" height="100" /></a>

[![PlatformIO Registry](https://badges.registry.platformio.org/packages/luos/library/luos_engine.svg)](https://registry.platformio.org/libraries/luos/luos_engine)

<br>

# ESP32 6-Channel Relay Control
---
***The ESP32 6-Channel Relay Module*** is a control circuit that allows you to manage up to six relays using an `ESP32 microcontroller`. This device is ideal for automation, remote control, or *IoT* (Internet of Things) projects where multiple electrical devices need to be controlled.

[![](https://www.waveshare.com/media/catalog/product/cache/1/image/560x560/9df78eab33525d08d6e5fb8d27136e95/e/s/esp32-s3-relay-6ch-1.jpg)](https://www.waveshare.com/esp32-s3-relay-6ch.htm)

# Table of Contents
---
- [ESP32 6-Channel Relay Control](#esp32-6-channel-relay-control)
- [Table of Contents](#table-of-contents)
- [Manual](#manual)
  - [1. Device Description](#1-device-description)
  - [2. Hardware Connections](#2-hardware-connections)
  - [3. Programming Instructions](#3-programming-instructions)
    - [3.1. Library Setup](#31-library-setup)
    - [3.2. Setup Procedure](#32-setup-procedure)
  - [4. Usage Instructions](#4-usage-instructions)
- [Question?](#question)

---
# Manual
---
## 1. Device Description
---

:star2: **Key Features:**

:white_check_mark:  High quality `6-Ch relays`, supports *RS485* and *Bluetooth / WIFi* remote control

:white_check_mark: Contact rating of the onboard relay up to `10A 250VAC/30VDC`

:white_check_mark: Directly controlling `220VAC` home appliances, or devices below `30VDC`

:white_check_mark: Onboard isolated `RS485 interface`, for connecting to various RS485 Modbus industrial modules or sensors. 

:white_check_mark: Onboard 40PIN header compatible with some `Raspberry Pi Pico HAT`, for expanding more functions such as `RTC / CAN / RS232 / LoRa / sensor, etc`.
  
## 2. Hardware Connections
---
>**Parameter**

|Items|	Parameters|
|:--|:--|
|Supply Voltage|	7~36V (or 5V/1A Type-C Interface)|
|Relay channels	|6 CH|
|Contact form|	1NO 1NC|
|Interface|	Type-C|
|Communication Protocol|	USB Protocol|
|Dimensions	|88(H) x 122(V)mm|

>**Onboard Interface**

| GPIO Control|Function |Description | 
| :---:| :---:|:---: | 
|GP0	|BOOT Key|	BOOT Key Control Pin|
|GP21|	BUZZER|	Buzzer Control Pin|
|GP38|	RGB	|RGB LED Control Pin|
|GP1|	CH1|	Relay No.1 Control Pin|
|GP2	|CH2|	Relay No.2 Control Pin|
|GP41|	CH3|	Relay No.3 Control Pin|
|GP42|	CH4	|Relay No.4 Control Pin|
|GP45|	CH5	|Relay No.5 Control Pin|
|GP46|	CH6	|Relay No.6 Control Pin|
|GP17|	TXD	|UART TX pin, converted to RS485|
|GP18|	RXD| UART RX pin, converted to RS485|

>**RS485 Control**

*Connect the **RS485** device to ESP32-S3-Relay-6CH, send commands to ESP32-S3-Relay-6CH for each relay ON/OFF, and the baud rate is `115200` by default.*

|Command|Function|
|:--|:--|
|06 05 00 01 55 00 A2 ED	|Switch CH1 relay ON/OFF|
|06 05 00 02 55 00 52 ED	|Switch CH2 relay ON/OFF|
|06 05 00 03 55 00 03 2D	|Switch CH3 relay ON/OFF|
|06 05 00 04 55 00 B2 EC	|Switch CH4 relay ON/OFF|
|06 05 00 05 55 00 E3 2C	|Switch CH5 relay ON/OFF|
|06 05 00 06 55 00 13 2C	|Switch CH6 relay ON/OFF|
|06 05 00 FF FF 00 BD BD	|All relays ON|
|06 05 00 FF 00 00 FC 4D	|All relays OFF|

> :bangbang: ***Note***: Ensure that the relay is powered by `5V` while the ESP32 operates at `3.3V` for proper functionality.


## 3. Programming Instructions
---
Ensure the following libraries are installed in your development environment, such as PlatformIO.

### 3.1. Library Setup
    - https://github.com/me-no-dev/ESPAsyncWebServer.git
	- https://github.com/RobTillaart/DHT20
	- bblanchon/ArduinoJson@^7.1.0
	- https://github.com/adafruit/Adafruit_MQTT_Library
	- arduino-libraries/NTPClient@^3.2.1
	- AsyncTCP
	- mikalhart/TinyGPSPlus@^1.1.0
	- plerup/EspSoftwareSerial@^8.2.0
	- adafruit/Adafruit NeoPixel@^1.12.3
### 3.2. Setup Procedure
After installing the PlatformIO extension, clone the project repository from Git. Choose the appropriate board for your project, such as yolo uno, esp32s3relay, or any other compatible board, and select the corresponding port that connects your computer to the device.

- On the board:
    - Enter Bootloader mode by following these steps:
    - Hold the Boot button.
    - Press and hold the Reset button.
    - Release the Reset button.
    - Finally, release the Boot button.
- In the PlatformIO interface:

    - Upload the Filesystem Image using PlatformIO.
    - Flash the Firmware onto the device.
    - Exit Bootloader mode by pressing the Reset button.

## 4. Usage Instructions
---
> After successfully connecting, you can control the relays via a web interface. You can retrieve the `IP address` of the ESP32 from the ***Serial Monitor*** in your development environment.
> Access the ESP32 server using its `IP address`, and manage the relays.

# Congratulation !
---

:confetti_ball: You have finished reading the introduction and user manual of the **ESP32-S3 Relay 6CH**. In the future, we will continue to improve and upgrade to provide you with the best values.:confetti_ball: 

>Anything ***unclear*** or ***buggy*** in this tutorial? [Please report it!](https://www.facebook.com/groups/aclabhcmut?locale=vi_VN)

