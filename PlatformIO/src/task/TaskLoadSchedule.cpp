#include "TaskLoadSchedule.h"

void loadSchedulesFromFile()
{
    File file = LittleFS.open("/schedules.dat", "r");
    if (!file)
    {
        Serial.println("Failed to open file for reading");
        return;
    }

    file.read((uint8_t *)schedules, sizeof(schedules));
    file.read((uint8_t *)&scheduleCount, sizeof(scheduleCount));

    file.close();
}

void TaskLoadSchedule(void *pvParameters)
{
    loadSchedulesFromFile();
    vTaskDelete(NULL);
}