#include "TaskMobus.h"

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

        int pin;
        switch (relay_id)
        {
        case 0:
            pin = GPIO_PIN_CH1;
            break;
        case 1:
            pin = GPIO_PIN_CH2;
            break;
        case 2:
            pin = GPIO_PIN_CH3;
            break;
        case 3:
            pin = GPIO_PIN_CH4;
            break;
        case 4:
            pin = GPIO_PIN_CH5;
            break;
        case 5:
            pin = GPIO_PIN_CH6;
            break;
        default:
            return;
        }
        pinMode(pin, OUTPUT);

        if (state == "ON")
        {
            digitalWrite(pin, HIGH);
            sendModbusCommand(relay_ON[index], sizeof(relay_ON[0]));
        }
        else
        {
            digitalWrite(pin, LOW);
            sendModbusCommand(relay_OFF[index], sizeof(relay_OFF[0]));
        }
    }
    String response = "{\"index\":" + String(index) + ",\"state\":\"" + state + "\"}";
    String sendData = String(index) + '-' + state;
    Serial.println(sendData);
    if (client.connected())
    {
        publishData("relay", sendData);
    }
    else
    {
        Serial.println("Not connected to MQTT");
    }
    if (ws.count() > 0)
    {
        ws.textAll(response);
    }
}