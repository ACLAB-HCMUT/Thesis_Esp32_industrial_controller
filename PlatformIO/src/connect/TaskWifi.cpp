#include "TaskWifi.h"

void TaskWifi(void *pvParameters)
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID.c_str(), WIFI_PASS.c_str());

    while (WiFi.status() != WL_CONNECTED)
    {
        vTaskDelay(delay_wifi / portTICK_PERIOD_MS);
        Serial.println("Connecting to WiFi");
    }

    Serial.println("Connected to WiFi");

    while (true)
    {
        if (WiFi.status() != WL_CONNECTED)
        {
            WiFi.disconnect();
            WiFi.begin(WIFI_SSID.c_str(), WIFI_PASS.c_str());

            while (WiFi.status() != WL_CONNECTED)
            {
                vTaskDelay(delay_wifi / portTICK_PERIOD_MS);
                Serial.println("Reconnecting to WiFi...");
            }
            Serial.println("Reconnected to WiFi");
        }
        vTaskDelay(delay_wifi / portTICK_PERIOD_MS);
    }
}

void wifi_init()
{
    xTaskCreate(TaskWifi, "TaskWifi", 4096, NULL, 1, NULL);
}
