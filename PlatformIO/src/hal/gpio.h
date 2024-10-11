/**
 * @file gpio.h
 * @author Xuan Tho Do (tho.dok17@gmail.com)
 * @brief Generic Purpose IO
 * @version 0.1
 * @date 2024-02-02
 *
 * @copyright Copyright (c) 2024 Kinis AI
 *
 */

#ifndef _HAL_GPIO_H
#define _HAL_GPIO_H

#include <stdint.h>
#include <stdbool.h>

#if defined(NUVOTON)
	#include "NuMicro.h"
#elif defined(NRF)
	#include <nrf_gpio.h>
	#include <nrf_drv_gpiote.h>
	#define BIT0 (1 << 0)
	#define BIT1 (1 << 1)
	#define BIT2 (1 << 2)
	#define BIT3 (1 << 3)
	#define BIT4 (1 << 4)
	#define BIT5 (1 << 5)
	#define BIT6 (1 << 6)
	#define BIT7 (1 << 7)
	#define BIT8 (1 << 8)
	#define BIT9 (1 << 9)
	#define BIT10 (1 << 10)
	#define BIT11 (1 << 11)
	#define BIT12 (1 << 12)
	#define BIT13 (1 << 13)
	#define BIT14 (1 << 14)
	#define BIT15 (1 << 15)
	#define BIT16 (1 << 16)
	#define BIT17 (1 << 17)
	#define BIT18 (1 << 18)
	#define BIT19 (1 << 19)
	#define BIT20 (1 << 20)
	#define BIT21 (1 << 21)
	#define BIT22 (1 << 22)
	#define BIT23 (1 << 23)
	#define BIT24 (1 << 24)
	#define GPIO_MODE_OUTPUT NRF_GPIO_PIN_DIR_OUTPUT
	#define GPIO_MODE_INPUT NRF_GPIO_PIN_DIR_INPUT
	#define GPIO_PUSEL_DISABLE NRF_GPIO_PIN_NOPULL
	#define GPIO_PUSEL_PULL_UP NRF_GPIO_PIN_PULLUP
	#define GPIO_PUSEL_PULL_DOWN NRF_GPIO_PIN_PULLDOWN
	#define GPIO_SLEWCTL_NORMAL GPIO_PIN_CNF_DRIVE_S0S1
	#define GPIO_SLEWCTL_HIGH GPIO_PIN_CNF_DRIVE_S0S1
	#define GPIO_SLEWCTL_FAST GPIO_PIN_CNF_DRIVE_S0S1
	#define GPIO_INT_RISING NRF_GPIOTE_POLARITY_LOTOHI
	#define GPIO_INT_FALLING NRF_GPIOTE_POLARITY_HITOLO
	#define GPIO_INT_BOTH_EDGE NRF_GPIOTE_POLARITY_TOGGLE
#endif
typedef void (*GPIO_externalInterruptCallback)(void);

typedef struct
{
#if defined(NUVOTON)
	GPIO_T* instance;
#elif defined(NRF)
	uint32_t port;
#endif
	uint32_t pinMask;
	uint32_t pin;
	uint32_t mode;
	uint32_t pushPull;
	uint32_t speed;
	uint32_t debouncingTime;
	uint32_t interruptMode;
	GPIO_externalInterruptCallback callback;
} GPIO_Handle;

void GPIO_init();
void GPIO_initIo(GPIO_Handle* handle);
void GPIO_run10ms(void);
void GPIO_write(GPIO_Handle* handle, bool enable);
bool GPIO_read(GPIO_Handle* handle);
void GPIO_deinitIo(GPIO_Handle* handle);
void GPIO_deinit(GPIO_Handle* handle);
void GPIO_test(void);

#endif // _HAL_GPIO_H