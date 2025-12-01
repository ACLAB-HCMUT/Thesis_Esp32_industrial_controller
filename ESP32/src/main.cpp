
#include "globals.h"

void setup()
{
  Serial.begin(115200);
  Serial2.begin(BAUD_RATE_2, SERIAL_8N1, TXD_RELAY, RXD_RELAY);

  // FreeRTOS tasks
  if (check_info_File(0))
  {
    device_intit();
    task_intit();
  }
}

void loop()
{

  if (ss.available() > 0)
    gps.encode(ss.read());
  if (check_info_File(1))
  {
    if (!Wifi_reconnect())
    {
      Webserver_stop();
    }
    else
    {
      MQTT_reconnect();
    }
    Webserver_reconnect();
  }
}