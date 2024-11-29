#ifndef HAL_USB_H
#define HAL_USB_H

#include <stdint.h>
#include <stdbool.h>

typedef void (*USB_RxDataCallback)(uint8_t* data, uint32_t dataSize);

void USB_init(void);
void USB_deinit(void);
void USB_run(void);
void USB_test(void);
void USB_setRxDataCallback(USB_RxDataCallback callback);
bool USB_write(uint8_t* data, uint32_t dataSize);
bool USB_isDataAvailable(void);
uint8_t USB_readSingleByte(void);
bool USB_readMultiBytes(uint8_t* data, uint32_t dataSize, uint32_t* readSize);

#endif // HAL_USB_H