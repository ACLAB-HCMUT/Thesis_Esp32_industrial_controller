#include "TaskGps.h"

TinyGPSPlus gps;
SoftwareSerial ss(RXD_GPS, TXD_GPS);

float X = 0;
float Y = 0;

void TaskGps(void *pvParameters)
{
    ss.begin(9600);
    while (true)
    {
        if (WiFi.status() != WL_CONNECTED || !client.connected())
        {
            vTaskDelay(delay_connect / portTICK_PERIOD_MS);
            continue;
        }
        if (gps.location.isUpdated())
        {
            X = gps.location.lat();
            Y = gps.location.lng();
        }
        String data = "{\"latitude\":" + String(gps.location.lat(), 7) + ",\"longitude\":" + String(gps.location.lng(), 7) + "}";
        publishData("location", (String(gps.location.lat(), 7) + "-" + String(gps.location.lng(), 7)));
        if (ws.count() > 0)
        {
            ws.textAll(data);
        }
        vTaskDelay(delay_gps / portTICK_PERIOD_MS);
    }
}