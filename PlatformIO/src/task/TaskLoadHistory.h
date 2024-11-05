#ifndef INC_TASKLOADHISTORY_H_
#define INC_TASKLOADHISTORY_H_

#include "globals.h"

#ifdef __cplusplus
extern "C"
{
#endif

    void TaskLoadHistory(void *pvParameters);

#ifdef __cplusplus
}
#endif

extern char *username;
extern char *password;

void loadInfoFromFile();

#endif /* INC_TASKLOADHISTORY_H_ */
