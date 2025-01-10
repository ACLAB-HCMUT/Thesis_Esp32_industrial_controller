#include "TaskBLE.h"

class OtaCallbacks : public NimBLECharacteristicCallbacks
{
    void onWrite(NimBLECharacteristic *pCharacteristic)
    {
        std::string data = pCharacteristic->getValue();
        if (data.empty())
        {
            Serial.println("No data received!");
            return;
        }
        if (data.rfind("start", 0) == 0)
        {
            size_t spaceIndex = data.find(' ');
            if (spaceIndex != std::string::npos)
            {
                std::string fileSizeStr = data.substr(spaceIndex + 1);
                long fileSize = std::stol(fileSizeStr);
                if (fileSize > 0)
                {
                    if (!Update.begin(fileSize))
                    {
                        Serial.printf("Update begin failed. Error: %s\n", Update.errorString());
                    }
                    else
                    {
                        Serial.println("Started firmware update.");
                    }
                }
                else
                {
                    Serial.println("Invalid file size.");
                }
            }
            else
            {
                Serial.println("No file size provided.");
            }
        }
        else if (data == "end")
        {
            if (!Update.end())
            {
                Serial.printf("Update end failed. Error: %s\n", Update.errorString());
            }
            else
            {
                Serial.println("Update successful. Rebooting...");
                delay(2000);
                ESP.restart();
            }
        }
        else if (data == "hello")
        {
            NimBLECharacteristic *responseCharacteristic = pCharacteristic->getService()->getCharacteristic(OTA_CHARACTERISTIC_UUID);
            if (responseCharacteristic)
            {
                responseCharacteristic->setValue("you too");
                responseCharacteristic->notify();
                Serial.println("Sent 'you too' to Flutter.");
            }
            else
            {
                Serial.println("Failed to find response characteristic.");
            }
        }

        else if (Update.isRunning())
        {
            if (data != "start" && data != "end")
            {
                size_t written = Update.write((uint8_t *)data.data(), data.size());
                if (written != data.size())
                {
                    Serial.printf("Failed to write data. Written: %d, Expected: %d\n", written, data.size());
                }
                else
                {
                    Serial.printf("Writen data: %s\n", data.c_str());
                }
            }
        }
        else
        {
            Serial.println("Unknown command received");
        }
    }
};

void TaskBLE(void *pvParameters)
{
    while (NAME_DEVICE.isEmpty())
    {
        vTaskDelay(delay_connect / portTICK_PERIOD_MS);
        continue;
    }
    NimBLEDevice::init(NAME_DEVICE.c_str());

    NimBLEServer *pServer = NimBLEDevice::createServer();
    NimBLEService *pService = pServer->createService(OTA_SERVICE_UUID);

    NimBLECharacteristic *pOtaCharacteristic = pService->createCharacteristic(
        OTA_CHARACTERISTIC_UUID,
        NIMBLE_PROPERTY::WRITE);

    pOtaCharacteristic->setCallbacks(new OtaCallbacks());

    pService->start();
    NimBLEAdvertising *pAdvertising = NimBLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(OTA_SERVICE_UUID);
    pAdvertising->start();
    vTaskDelete(NULL);
}

void ble_init()
{
    xTaskCreate(TaskBLE, "TaskBLE", 4096, NULL, 1, NULL);
}