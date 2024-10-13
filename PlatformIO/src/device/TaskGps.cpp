#include "TaskGps.h"

TinyGPSPlus gps;
SoftwareSerial ss(RXD_GPS, TXD_GPS);

float X = 0;
float Y = 0;

void saveGpsToFile()
{
    File file = LittleFS.open("/gps.dat", "a");
    if (!file)
    {
        Serial.println("Failed to open file for appending");
        return;
    }

    DynamicJsonDocument doc(1024);

    doc["mode"] = "GPS";
    doc["time"] = current;
    doc["CoordinateX"] = X;
    doc["CoordinateY"] = Y;

    if (file.size() > 0)
    {
        file.print(",\n");
    }

    if (serializeJson(doc, file) == 0)
    {
        Serial.println("Failed to write to file");
    }

    file.close();
}

void GPS_sensor()
{
    if (gps.location.isUpdated())
    {
        X = gps.location.lat();
        Y = gps.location.lng();
    }
}

void TaskGps(void *pvParameters)
{
    ss.begin(9600);
    while (true)
    {
        GPS_sensor();
        if (WiFi.status() == WL_CONNECTED)
        {
            if (client.connected())
            {
                publishData("location", (String(gps.location.lat(), 7) + "-" + String(gps.location.lng(), 7)));
            }
            String data = "{\"latitude\":" + String(gps.location.lat(), 7) + ",\"longitude\":" + String(gps.location.lng(), 7) + "}";

            if (ws.count() > 0)
            {
                ws.textAll(data);
            }
            vTaskDelay(delay_gps / portTICK_PERIOD_MS);
        }

        else if (WiFi.status() != WL_CONNECTED)
        {
            saveGpsToFile();
            vTaskDelay(delay_reconnect / portTICK_PERIOD_MS);
        }
    }
}