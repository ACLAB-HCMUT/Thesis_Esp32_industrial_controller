#ifndef GLOBALS_H
#define GLOBALS_H

// include libraries
#include <Wire.h>
#include <WiFi.h>
#include <DHT20.h>
#include "LittleFS.h"
#include "SPIFFS.h"
#include <AsyncTCP.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <ESPAsyncWebServer.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <Adafruit_NeoPixel.h>
#include <HardwareSerial.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// include common files
#include "../src/common/defines.h"
#include "../src/common/RelayStatus.h"

// include connect
#include "../src/connect/connect_init.h"

// include task
#include "../src/task/task_init.h"

// include device
#include "../src/device/device_intit.h"

// include utils
#include "./utils/utility_functions.h"

#endif