/**
 * @file adc.h
 * @author Xuan Tho Do (tho.dok17@gmail.com)
 * @brief Analog-Digital Converter
 * @version 0.1
 * @date 2024-02-04
 *
 * @copyright Copyright (c) 2024 Kinis AI
 *
 */

#ifndef HAL_ADC_H
#define HAL_ADC_H

#include <stdint.h>

#if defined(NUVOTON)
	#include <NuMicro.h>
#elif defined(NRF)
	#include <nrf.h>
#endif

#define ADC_USING_SAADC 5 // 0,1,2,3, Vbat -- Temperature use TEMP peripheral
typedef enum
{
	ADC_ID_0 = 0,
	ADC_ID_1,
#if defined(NUVOTON)
	ADC_ID_2,
	ADC_ID_3,
	ADC_ID_4,
	ADC_ID_5,
	ADC_ID_6,
	ADC_ID_7,
	ADC_ID_BAT = 15,
	ADC_ID_TEMP = 17,
#elif defined(NRF)
	ADC_ID_4,
	ADC_ID_5,
	ADC_ID_7,
	ADC_ID_TEMP,
#endif
	ADC_ID_MAX
} ADC_Id;

void ADC_init(void);
void ADC_start(void);
void ADC_stop(void);
void ADC_test(void);
uint32_t ADC_getValue(ADC_Id id);
uint32_t ADC_getTemperatureValue(void);
uint32_t ADC_getMaxValue(void);
void ADC_deinit(void);

#endif // HAL_ADC_H