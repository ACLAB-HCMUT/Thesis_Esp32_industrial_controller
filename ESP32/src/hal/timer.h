/**
 * @file timer.h
 * @author Xuan Tho Do (tho.dok17@gmail.com)
 * @brief Timer interface
 * @version 0.1
 * @date 2024-02-04
 *
 * @copyright Copyright (c) 2024 Kinis AI
 *
 */

#ifndef HAL_TIMER_H
#define HAL_TIMER_H

#include <stdint.h>
#include <stdbool.h>

#if defined(NUVOTON)
	#include <NuMicro.h>
#elif defined(NRF)
	#include <nrf.h>
#endif

#define TIMER_CALLBACK_FN_MAX 10

typedef void (*TIMER_callback)(void);

typedef struct
{
#if defined(NUVOTON)
	TIMER_T* instance;
#endif
	uint32_t frequency;
	uint32_t period;
	uint32_t mode;
#if defined(NUVOTON)
	IRQn_Type irqType;
#endif
	uint32_t priority;
	TIMER_callback callback[TIMER_CALLBACK_FN_MAX];
	uint8_t callbackLen;
} TIMER_Handle;

void TIMER_init(void);
bool TIMER_start(void);
bool TIMER_stop(void);
bool TIMER_attachInterrupt1ms(void (*callback)(void));
void TIMER_test(void);
void TIMER_deinit(void);

#endif // HAL_TIMER_H