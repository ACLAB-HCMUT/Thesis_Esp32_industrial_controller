#include "TaskTemperatureHumidity.h"

float temperature = 0, humidity = 0;
HardwareSerial RS485Serial(1);
DHT20 dht20;

void saveTemp_HumiToFile()
{
    File file = LittleFS.open("/temp_humi.dat", "a");
    if (!file)
    {
        Serial.println("Failed to open file for appending");
        return;
    }

    DynamicJsonDocument doc(2048);
    doc["email"] = String(EMAIL);
    doc["mode"] = "Temp_Humi";
    doc["time"] = date;
    doc["data"] = String(temperature, 2) + "-" + String(humidity, 2);

    if (file.size() > 0)
    {
        file.print(",\n");
    }

    if (serializeJson(doc, file) == 0)
    {
        Serial.println("Failed to write to file");
    }

    file.close();
}

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

void DHT20_sensor()
{
    if (dht20.read() == DHT20_OK)
    {
        temperature = dht20.getTemperature();
        humidity = dht20.getHumidity();
    }
}

void sendTemp_Humi(void *pvParameters)
{
    while (true)
    {
        if (WiFi.status() == WL_CONNECTED && client.connected() && temperature * humidity != 0)
        {
            String temperatureStr = String(temperature, 2);
            String humidityStr = String(humidity, 2);

            String data = "{\"email\":\"" + String(EMAIL) + "\",\"data\":" + temperatureStr + "}";
            publishData("temperature", data);
            data = "{\"email\":\"" + String(EMAIL) + "\",\"data\":" + humidityStr + "}";
            publishData("humidity", data);

            vTaskDelay(delay_30_min / portTICK_PERIOD_MS);
        }
        vTaskDelay(delay_gps / portTICK_PERIOD_MS);
    }
}

void TaskTemperatureHumidity(void *pvParameters)
{
    RS485Serial.begin(BAUD_RATE_2, SERIAL_8N1, RXD_RS485, TXD_RS485);
    Wire.begin(MY_SCL, MY_SDA);
    Wire.setClock(100000);
    dht20.begin();

    while (true)
    {
        ES35_sensor();
        DHT20_sensor();

        if (WiFi.status() == WL_CONNECTED)
        {
            if (ws.count() > 0)
            {
                String data = "{\"temperature\":" + String(temperature, 2) + ",\"humidity\":" + String(humidity, 2) + "}";
                ws.textAll(data);
            }
        }

        if (WiFi.status() != WL_CONNECTED)
        {
            if (temperature != 0 && humidity != 0 && check_different_time)
            {
                saveTemp_HumiToFile();
            }
        }
        vTaskDelay(delay_temp_humi / portTICK_PERIOD_MS);
    }
}

void Temp_Humi_init()
{
    xTaskCreate(TaskTemperatureHumidity, "TaskTemperatureHumidity", 8192, NULL, 1, NULL);
    xTaskCreate(sendTemp_Humi, "sendTemp_Humi", 4096, NULL, 2, NULL);
}
