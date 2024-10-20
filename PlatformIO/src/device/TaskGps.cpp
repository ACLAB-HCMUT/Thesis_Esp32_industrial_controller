#include "TaskGps.h"

TinyGPSPlus gps;
SoftwareSerial ss(RXD_GPS, TXD_GPS);

float X = 0;
float Y = 0;
int count_30_min_gps = 0;

void saveGpsToFile()
{
    File file = LittleFS.open("/gps.dat", "a");
    if (!file)
    {
        Serial.println("Failed to open file for appending");
        return;
    }

    DynamicJsonDocument doc(2048);
    doc["email"] = String(EMAIL);
    doc["mode"] = "location";
    doc["time"] = date;
    doc["data"] = String(X, 5) + "-" + String(Y, 5);

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

    while (WiFi.status() == WL_DISCONNECTED)
    {
        vTaskDelay(delay_connect / portTICK_PERIOD_MS);
        continue;
    }

    while (true)
    {
        GPS_sensor();
        if (WiFi.status() == WL_CONNECTED)
        {
            String XStr = String(X, 2);
            String YStr = String(Y, 2);

            if (client.connected() && count_30_min_gps == 0)
            {
                String locationStr = XStr + "-" + YStr;
                String data = "{\"email\":\"" + String(EMAIL) + "\",\"data\":\"" + locationStr + "\"}";
                publishData("location", data);
                count_30_min_gps = 12;
            }
            if (ws.count() > 0)
            {
                String data = "{\"latitude\":" + XStr + ",\"longitude\":" + YStr + "}";
                ws.textAll(data);
            }
            count_30_min_gps--;
        }
        else if (WiFi.status() == WL_DISCONNECTED)
        {
            if (X != 0 && Y != 0 && check_different_time)
            {
                saveGpsToFile();
                count_30_min_gps=0;
            }
        }
        vTaskDelay(delay_gps / portTICK_PERIOD_MS);
    }
}