#include "task_init.h"

void task_intit()
{
    xTaskCreate(TaskLoadHistory, "TaskLoadHistory", 4096, NULL, 1, NULL);
    xTaskCreate(TaskSchedule, "TaskSchedule", 4096, NULL, 1, NULL);
    xTaskCreate(TaskServer, "TaskServer", 8192, NULL, 1, NULL);
    xTaskCreate(TaskTime, "TaskTime", 2048, NULL, 1, NULL);
}