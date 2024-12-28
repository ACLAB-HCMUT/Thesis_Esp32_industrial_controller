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

void sendLocation(void *pvParameters)
{
    while (true)
    {
        if (WiFi.status() == WL_CONNECTED && client.connected() && X * Y != 0)
        {
            String locationStr = String(X, 7) + "-" + String(Y, 7);
            String data = "{\"email\":\"" + String(EMAIL) + "\",\"data\":\"" + locationStr + "\"}";
            publishData("location", data);
            vTaskDelay(delay_30_min / portTICK_PERIOD_MS);
        }
        vTaskDelay(delay_gps / portTICK_PERIOD_MS);
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
            if (ws.count() > 0)
            {
                String data = "{\"latitude\":" + String(X, 2) + ",\"longitude\":" + String(Y, 2) + "}";
                ws.textAll(data);
            }
        }
        else if (WiFi.status() != WL_CONNECTED)
        {
            if (X != 0 && Y != 0 && check_different_time)
            {
                saveGpsToFile();
            }
        }
        vTaskDelay(delay_gps / portTICK_PERIOD_MS);
    }
}

void GPS_init()
{
    xTaskCreate(TaskGps, "TaskGps", 4096, NULL, 1, NULL);
    xTaskCreate(sendLocation, "sendLocation", 4096, NULL, 2, NULL);
}