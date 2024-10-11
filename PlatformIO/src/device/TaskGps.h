#ifndef INC_TASKGPS_H_
#define INC_TASKGPS_H_

#include "globals.h"

#ifdef __cplusplus
extern "C"
{
#endif

    void TaskGps(void *pvParameters);

#ifdef __cplusplus
}
#endif

extern TinyGPSPlus gps;
extern SoftwareSerial ss;

#endif /* INC_TASKGPS_H_ */