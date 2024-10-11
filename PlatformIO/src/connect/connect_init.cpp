#include "connect_init.h"

void connect_intit()
{
    xTaskCreate(TaskMQTT, "TaskMQTT", 4096, NULL, 1, NULL);
    xTaskCreate(TaskWifi, "TaskWifi", 4096, NULL, 1, NULL);
}