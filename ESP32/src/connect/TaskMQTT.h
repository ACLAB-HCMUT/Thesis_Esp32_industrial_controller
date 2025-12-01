#ifndef INC_TASKMQTT_H_
#define INC_TASKMQTT_H_

#include "globals.h"

extern PubSubClient client;

void MQTT_reconnect();
void publishData(String feed, String data);

#endif /* INC_TASKMQTT_H_ */