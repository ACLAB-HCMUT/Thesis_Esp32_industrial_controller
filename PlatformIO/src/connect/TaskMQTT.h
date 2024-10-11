#ifndef INC_TASKMQTT_H_
#define INC_TASKMQTT_H_

#include "globals.h"

extern PubSubClient client;

#ifdef __cplusplus
extern "C"
{
#endif

    void TaskMQTT(void *pvParameters);

#ifdef __cplusplus
}
#endif

void reconnect();
void publishData(String feed, String data);

#endif /* INC_TASKMQTT_H_ */