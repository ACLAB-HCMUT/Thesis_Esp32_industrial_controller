#ifndef INC_TASKSCHEDULE_H_
#define INC_TASKSCHEDULE_H_

#include "globals.h"
#include "../device/TaskMobus.h"
#include "TaskTime.h"

#ifdef __cplusplus
extern "C"
{
#endif

    void TaskSchedule(void *pvParameters);

#ifdef __cplusplus
}
#endif

extern DLinkedList schedules;

void deleteScheduleById(int id);
void saveSchedulesToFile();

#endif /* INC_TASKSCHEDULE_H_ */