/**
 * @file spi.h
 * @author Xuan Tho Do (tho.dok17@gmail.com)
 * @brief SPI interface
 * @version 0.1
 * @date 2024-02-04
 *
 * @copyright Copyright (c) 2024 Kinis AI
 *
 */

#ifndef HAL_SPI_H
#define HAL_SPI_H

#include <stdint.h>
#include <stdbool.h>

#if defined(NUVOTON)
	#include <NuMicro.h>
#elif defined(NRF)
	#include <nrf.h>
#endif
typedef enum
{
	SPI_ID_0 = 0,
	SPI_ID_1,
	SPI_ID_MAX
} SPI_Id;

typedef struct
{
#if defined(NUVOTON)
	SPI_T* instance;
#elif defined(NRF)
	NRF_SPI_Type* instance;
#endif
	uint32_t frequency;
	uint32_t mode;
	uint32_t dataWidth;
	bool isMaster;
	bool autoSs;
	bool isMsb;
#if defined(NUVOTON)
	PDMA_T* dmaInstance;
#endif
	uint32_t dmaWidth;
	uint32_t dmaSize;
	uint32_t dmaTxChannel;
	uint32_t dmaTxSpiMapping;
	uint32_t dmaRxChannel;
	uint32_t dmaRxSpiMapping;
	uint32_t dmaBurseType;
	uint32_t dmaBurseSize;
	uint32_t timeoutCnt;
	bool timeoutFlag;

} SPI_Handle;

void SPI_init(void);
bool SPI_transmit(SPI_Id id, uint8_t* dataPtr, uint32_t dataSize, uint32_t timeout);
bool SPI_transmitAndReceive(SPI_Id id, uint8_t* tDataPtr, uint8_t* rDataPtr, uint32_t dataSize,
							uint32_t timeout);
void SPI_turnOffSs(void);
void SPI_turnOnSs(void);
void SPI_test(void);
void SPI_deinit(void);

#endif // HAL_SPI_H