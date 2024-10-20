#ifndef INC_TASKGPS_H_
#define INC_TASKGPS_H_

#include "globals.h"

void GPS_init();

extern TinyGPSPlus gps;
extern SoftwareSerial ss;

#endif /* INC_TASKGPS_H_ */