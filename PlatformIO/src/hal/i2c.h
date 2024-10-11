/**
 * @file i2c.h
 * @author Xuan Tho Do (tho.dok17@gmail.com)
 * @brief I2C interface
 * @version 0.1
 * @date 2024-02-04
 *
 * @copyright Copyright (c) 2024 Kinis AI
 *
 */

#ifndef HAL_I2C_H
#define HAL_I2C_H

#include <stdint.h>
#include <stdbool.h>

#if defined(NUVOTON)
	#include <NuMicro.h>
#elif defined(NRF)
	#include <nrf.h>
#endif

typedef struct
{
#if defined(NUVOTON)
	I2C_T* instance;
#elif defined(NRF)
	NRF_TWIM_Type* instance;
#endif
	uint32_t frequency;
} I2C_Handle;

void I2C_init(void);
void I2C_deinit(void);

bool I2C_read(uint8_t address, uint8_t* dataPtr, uint32_t dataSize, uint32_t timeout);
bool I2C_write(uint8_t address, uint8_t* dataPtr, uint32_t dataSize, uint32_t timeout);
bool I2C_memRead(uint8_t address, uint8_t registerAddr, uint8_t* data_p, uint32_t dataSize,
				 uint32_t timeout);
bool I2C_memWrite(uint8_t address, uint8_t registerAddr, uint8_t* dataPtr, uint32_t dataSize,
				  uint32_t timeout);
void I2C_test(void);

#endif // HAL_I2C_H