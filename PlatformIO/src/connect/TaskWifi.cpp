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

    String ipAddress = WiFi.localIP().toString();
    Serial.println("Connected to WiFi");
    Serial.println(ipAddress);

#ifdef M5_CORE2
    M5.Display.setCursor(0, 70);
    M5.Display.println("Your webserver :");
    int screenWidth = M5.Lcd.width();
    int textWidth = M5.Display.textWidth(ipAddress);
    M5.Display.setTextColor(YELLOW);
    M5.Display.setCursor((screenWidth - textWidth) / 2, 120);
    M5.Display.println(ipAddress);
#endif

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
