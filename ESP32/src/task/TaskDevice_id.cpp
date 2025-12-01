#include "TaskDevice_id.h"

void TaskDevice_id(void *pvParameters)
{
    while (true)
    {
        if (WiFi.status() != WL_CONNECTED || !client.connected())
        {
            vTaskDelay(100 / portTICK_PERIOD_MS);
            continue;
        }
        String data = "{\"email\":\"" + String(EMAIL) + "\",\"device_id\":\"" + String(Device_ID) + "\"}";
        publishData("device_id", data);
        vTaskDelay(delay_15_second / portTICK_PERIOD_MS);
    }
}