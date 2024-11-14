
#include "globals.h"

void setup()
{
  Serial.begin(115200);
  Serial2.begin(BAUD_RATE_2, SERIAL_8N1, TXD_RELAY, RXD_RELAY);
  Serial.println("Starting...");

  if (!LittleFS.begin(true))
  {
    Serial.println("An Error has occurred while mounting LittleFS");
  }

  // FreeRTOS tasks
  if (check_info())
  {
    connect_intit();
    device_intit();
    task_intit();
  }
}

void loop()
{
  ElegantOTA.loop();
  if (ss.available() > 0)
    gps.encode(ss.read());
}