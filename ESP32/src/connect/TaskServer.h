#ifndef INC_TASKSERVER_H_
#define INC_TASKSERVER_H_

#include "globals.h"

extern AsyncWebServer server;
extern AsyncWebSocket ws;

void Webserver_stop();
void Webserver_reconnect();
void Webserver_sendata(String data);

#endif /* INC_TASKSERVER_H_ */