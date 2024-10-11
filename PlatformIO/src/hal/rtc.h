/**
 * @file rtc.h
 * @author Xuan Tho Do (tho.dok17@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-03-02
 *
 * @copyright Copyright (c) 2024 Kinis AI
 *
 */

#ifndef HAL_RTC_H
#define HAL_RTC_H

#include <utils/customTime.h>

typedef enum
{
	RTC_DATE_TIME,
	RTC_TIMESTAMP
} RTC_TypeSupported;

void RTC_init(void);
TIME_DateTime RTC_getDateTime(void);
TIME_Timestamp RTC_getTimeStamp(void);
RTC_TypeSupported RTC_getTypeSupported(void);
void RTC_setDateTime(TIME_DateTime* time);
void RTC_setTimeStamp(TIME_Timestamp* time);
void RTC_test(void);

#endif // HAL_RTC_H