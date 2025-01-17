#include "TaskMobus.h"

HardwareSerial RS485(1);

uint8_t relayOnCommands[6][8] = {
    {0x06, 0x05, 0x00, 0x01, 0x55, 0x00, 0xA2, 0xED}, // CH1 ON
    {0x06, 0x05, 0x00, 0x02, 0x55, 0x00, 0x52, 0xED}, // CH2 ON
    {0x06, 0x05, 0x00, 0x03, 0x55, 0x00, 0x03, 0x2D}, // CH3 ON
    {0x06, 0x05, 0x00, 0x04, 0x55, 0x00, 0xB2, 0xEC}, // CH4 ON
    {0x06, 0x05, 0x00, 0x05, 0x55, 0x00, 0xE3, 0x2C}, // CH5 ON
    {0x06, 0x05, 0x00, 0x06, 0x55, 0x00, 0x13, 0x2C}  // CH6 ON
};

// Lệnh tắt từng relay (giống lệnh bật)
uint8_t relayOffCommands[6][8] = {
    {0x06, 0x05, 0x00, 0x01, 0x55, 0x00, 0xA2, 0xED}, // CH1 OFF
    {0x06, 0x05, 0x00, 0x02, 0x55, 0x00, 0x52, 0xED}, // CH2 OFF
    {0x06, 0x05, 0x00, 0x03, 0x55, 0x00, 0x03, 0x2D}, // CH3 OFF
    {0x06, 0x05, 0x00, 0x04, 0x55, 0x00, 0xB2, 0xEC}, // CH4 OFF
    {0x06, 0x05, 0x00, 0x05, 0x55, 0x00, 0xE3, 0x2C}, // CH5 OFF
    {0x06, 0x05, 0x00, 0x06, 0x55, 0x00, 0x13, 0x2C}  // CH6 OFF
};

void stateRS485(int i, bool state)
{
    if (i >= 0 && i <= 5)
        RS485.write(state ? relayOnCommands[i] : relayOffCommands[i], 8);
}

void setupRS485()
{
    RS485.begin(115200, SERIAL_8N1, 15, 16);
}