/**
 * @file qspi.h
 * @author Xuan Tho Do (tho.dok17@gmail.com)
 * @brief qspi interface
 * @version 0.1
 * @date 2024-02-04
 *
 * @copyright Copyright (c) 2024 Kinis AI
 *
 */

#ifndef HAL_QSPI_H
#define HAL_QSPI_H

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
	QSPI_T* instance;
#elif defined(NRF)
	NRF_QSPI_Type* instance;
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
} QSPI_Handle;

void QSPI_init(void);
bool QSPI_read(uint32_t address, uint8_t* dataPtr, uint32_t dataSize, uint32_t timeout);
bool QSPI_write(uint32_t address, uint8_t* dataPtr, uint32_t dataSize, uint32_t timeout);
bool QSPI_erase(uint32_t address, uint32_t size, uint32_t timeout);
bool QSPI_chipErase(uint32_t timeout);
bool QSPI_transmitAndReceive(uint8_t opCode, uint8_t* tx, uint8_t* rx, uint32_t dataSize,
							 uint32_t timeout);
void QSPI_deinit(void);

#endif // HAL_QSPI_H