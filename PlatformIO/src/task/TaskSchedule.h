#ifndef INC_TASKSCHEDULE_H_
#define INC_TASKSCHEDULE_H_

#include "globals.h"
#include "../device/TaskMobus.h"

#ifdef __cplusplus
extern "C"
{
#endif

    void TaskSchedule(void *pvParameters);

#ifdef __cplusplus
}
#endif

typedef struct
{
    int id;
    bool state;
    String days[MAX_DAYS];
    String time;
    struct
    {
        int relayId;
        String action;
    } actions[MAX_ACTIONS];
    int actionCount;
} Schedule;

extern Schedule schedules[MAX_SCHEDULES];
extern int scheduleCount;

void deleteScheduleById(int id);
void saveSchedulesToFile();

#endif /* INC_TASKSCHEDULE_H_ */