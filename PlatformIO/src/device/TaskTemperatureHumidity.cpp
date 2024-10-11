#include "TaskTemperatureHumidity.h"

#include "TaskTemperatureHumidity.h"

float temperature = 0, humidity = 0;
HardwareSerial RS485Serial(1);
// DHT20 dht20; User for DHT20

void sendRS485Command(byte *command, int commandSize, byte *response, int responseSize)
{
    RS485Serial.write(command, commandSize);
    RS485Serial.flush();
    delay(100);
    if (RS485Serial.available() >= responseSize)
    {
        RS485Serial.readBytes(response, responseSize);
    }
}

void ES35_sensor()
{
    byte temperatureRequest[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x01, 0x84, 0x0A};
    byte humidityRequest[] = {0x01, 0x03, 0x00, 0x01, 0x00, 0x01, 0xD5, 0xCA};
    byte response[7];
    sendRS485Command(temperatureRequest, sizeof(temperatureRequest), response, sizeof(response));
    if (response[1] == 0x03)
    {
        temperature = (response[3] << 8) | response[4];
        temperature /= 10.0;
    }

    delay(delay_connect);
    memset(response, 0, sizeof(response));
    sendRS485Command(humidityRequest, sizeof(humidityRequest), response, sizeof(response));
    if (response[1] == 0x03)
    {
        humidity = (response[3] << 8) | response[4];
        humidity /= 10.0;
    }
}

void TaskTemperatureHumidity(void *pvParameters)
{
    RS485Serial.begin(BAUD_RATE_2, SERIAL_8N1, SDA, SCL);
    while (true)
    {
        if (WiFi.status() == WL_CONNECTED && client.connected())
        {
            ES35_sensor();
            publishData("temperature", String(temperature));
            publishData("humidity", String(humidity));
            if (ws.count() > 0)
            {
                String data = "{\"temperature\":" + String(temperature) + ",\"humidity\":" + String(humidity) + "}";
                ws.textAll(data);
            }

            vTaskDelay(delay_temp / portTICK_PERIOD_MS);
        }
    }
}

/// User for DHT20
/*void TaskTemperatureHumidity(void *pvParameters)
{
    Wire.begin(SDA, SCL);
    Wire.setClock(100000);
    dht20.begin();

    while (1)
    {
        if (WiFi.status() != WL_CONNECTED || !client.connected())
        {
            vTaskDelay(delay_connect / portTICK_PERIOD_MS);
            continue;
        }
        dht20.read();
        float temperature = dht20.getTemperature();
        float humidity = dht20.getHumidity();
        String temperatureStr = String(temperature, 2);
        String humidityStr = String(humidity, 2);
        publishData("temperature", temperatureStr);
        publishData("humidity", humidityStr);
        if (ws.count() > 0)
        {
            String data = "{\"temperature\":" + temperatureStr + ",\"humidity\":" + humidityStr + "}";
            ws.textAll(data);
        }
        vTaskDelay(delay_temp / portTICK_PERIOD_MS);
    }
}
*/
