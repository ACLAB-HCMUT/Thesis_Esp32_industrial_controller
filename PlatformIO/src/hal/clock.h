/**
 * @file clock.h
 * @author Xuan Tho Do (tho.dok17@gmail.com)
 * @brief Clock
 * @version 0.1
 * @date 2024-02-04
 *
 * @copyright Copyright (c) 2024 Kinis AI
 *
 */

#ifndef HAL_CLOCK_H
#define HAL_CLOCK_H

#include <stdbool.h>
#include <stdint.h>

#if defined(NUVOTON)
	#include <NuMicro.h>
#elif defined(NRF)
	#include <nrf.h>
#endif

extern uint32_t SystemCoreClock;

void CLOCK_init(void);
bool CLOCK_enterLowSpeed(void);
bool CLOCK_enterHighSpeed(void);
uint32_t CLOCK_getTick(void);
uint32_t CLOCK_getTickFreq(void);
void CLOCK_delayMs(uint32_t delayMs);
void CLOCK_delayUs(uint32_t delayUs);
void CLOCK_deinit(void);
void CLOCK_enableWrapperSysTickHandler(void);
void __attribute__((weak)) WrapperSysTick_Handler(void);

#endif // HAL_CLOCK_H