#include "TaskFirmware.h"

void TaskFirmware(void *pvParameters)
{
    while (true)
    {
        if (WiFi.status() != WL_CONNECTED || !client.connected())
        {
            vTaskDelay(100 / portTICK_PERIOD_MS);
            continue;
        }
        String data = "{\"email\":\"" + String(EMAIL) + "\",\"data\":\"" + String(MY_BOARD) + "\",\"mode\":\"" + String(MY_VERSION) + "\"}";
        publishData("firmware", data);
        vTaskDelay(delay_30_min / portTICK_PERIOD_MS);
    }
}