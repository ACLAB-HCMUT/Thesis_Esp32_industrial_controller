#include "device_intit.h"

void device_intit()
{
    xTaskCreate(TaskGps, "TaskGps", 2048, NULL, 1, NULL);
    xTaskCreate(TaskLed, "TaskLed", 2048, NULL, 2, NULL);
    xTaskCreate(TaskTemperatureHumidity, "TaskTemperatureHumidity", 4096, NULL, 1, NULL);
}