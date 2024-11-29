/**
 * @file uart.h
 * @author Xuan Tho Do (tho.dok17@gmail.com)
 * @brief UART interface
 * @version 0.1
 * @date 2024-02-04
 *
 * @copyright Copyright (c) 2024 Kinis AI
 *
 */

#ifndef HAL_UART_H
#define HAL_UART_H

#include <stdint.h>
#include <stdbool.h>

#if defined(NUVOTON)
	#include <NuMicro.h>
#elif defined(NRF)
	#include <nrf.h>
#endif

#include <utils_buffer.h>

#define UART_RX_FIFO_BUFFER_SIZE 512

typedef enum
{
	UART_ID_0 = 0,
	UART_ID_4,
	UART_ID_MAX
} UART_Id;

typedef struct
{
#if defined(NUVOTON)
	UART_T* instance;
#endif
	uint32_t baudrate;
	uint32_t dataWidth;
	uint32_t parity;
	uint32_t stopBit;
	uint32_t interruptEnable;
	uint32_t interruptFlag;
	void (*rxCallback)(uint8_t* data, uint32_t dataSize);
	bool error;
#if defined(NUVOTON)
	IRQn_Type irqType;
#endif
	uint8_t rxBuffer[UART_RX_FIFO_BUFFER_SIZE];
	uint32_t rxBufferSize;
} UART_Handle;

void UART_init(void);
bool UART_send(UART_Id id, uint8_t* dataPtr, uint32_t dataSize, uint32_t timeout);
bool UART_attachRxCallback(UART_Id id, void (*callback)(uint8_t* data, uint32_t dataSize));
bool UART_isError(UART_Id id);
void UART_clearError(UART_Id id);
void UART_deinit(void);
void UART_test(void);

#endif // HAL_UART_H