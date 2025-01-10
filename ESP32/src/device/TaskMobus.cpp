#include "TaskMobus.h"

const int relay_pins[] = {
    GPIO_PIN_CH1, GPIO_PIN_CH2, GPIO_PIN_CH3, GPIO_PIN_CH4,
    GPIO_PIN_CH5, GPIO_PIN_CH6};

void sendModbusCommand(const uint8_t command[], size_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        Serial2.write(command[i]);
    }
    delay(delay_connect);
}

void sendValue(int index, String state)
{
    if (index >= 1 && index <= 32)
    {
        int relay_id = index - 1;

        if (relay_id < 0 || relay_id >= sizeof(relay_pins) / sizeof(relay_pins[0]))
        {
            return;
        }

        int pin = relay_pins[relay_id];

        if (state == "ON")
        {
            digitalWrite(pin, HIGH);
            sendModbusCommand(relay_ON[relay_id], sizeof(relay_ON[0]));
        }
        else
        {
            digitalWrite(pin, LOW);
            sendModbusCommand(relay_OFF[relay_id], sizeof(relay_OFF[0]));
        }

        String response = "{\"index\":" + String(index) + ",\"state\":\"" + state + "\"}";
        Serial.println(String(index) + '-' + state);
        if (client.connected())
        {
            String relayStr = String(index) + "-" + state;
            String data = "{\"email\":\"" + String(EMAIL) + "\",\"data\":\"" + relayStr + "\"}";
            publishData("relay", data);
        }
        if (ws.count() > 0)
        {
            ws.textAll(response);
        }
    }
}