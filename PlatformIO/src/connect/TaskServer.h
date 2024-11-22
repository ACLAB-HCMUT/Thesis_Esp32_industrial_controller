#ifndef INC_TASKSERVER_H_
#define INC_TASKSERVER_H_

#include "globals.h"

extern AsyncWebServer server;
extern AsyncWebSocket ws;

#ifdef __cplusplus
extern "C"
{
#endif

    void TaskServer(void *pvParameters);

#ifdef __cplusplus
}
#endif

void connnectWSV();

#endif /* INC_TASKSERVER_H_ */