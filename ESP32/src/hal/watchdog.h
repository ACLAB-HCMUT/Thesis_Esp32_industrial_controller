/**
 * @file watchdog.h
 * @author Xuan Tho Do (tho.dok17@gmail.com)
 * @brief Watch Dog Timer
 * @version 0.1
 * @date 2024-08-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef HAL_WATCHDOG_H
#define HAL_WATCHDOG_H

void WATCHDOG_init(void);
void WATCHDOG_deinit(void);
void WATCHDOG_refresh(void);

#endif // HAL_WATCHDOG_H