#include "TaskWifi.h"

void TaskWifi(void *pvParameters)
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED)
    {
        vTaskDelay(delay_wifi / portTICK_PERIOD_MS);
        Serial.println("Connecting to WiFi");
    }
    vTaskDelete(NULL);
}

void wifi_init()
{
    xTaskCreate(TaskWifi, "TaskWifi", 4096, NULL, 1, NULL);
}