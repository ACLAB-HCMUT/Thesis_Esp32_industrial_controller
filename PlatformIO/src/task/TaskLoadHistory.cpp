#include "TaskLoadHistory.h"

void loadSchedulesFromFile()
{
    File file = LittleFS.open("/schedules.dat", "r");
    if (!file)
    {
        Serial.println("Failed to open file for reading");
        return;
    }

    file.read((uint8_t *)schedules, sizeof(schedules));
    file.read((uint8_t *)&scheduleCount, sizeof(scheduleCount));

    file.close();
    LittleFS.remove("/schedules.dat");
}

void loadGpsFromFile()
{
    File file = LittleFS.open("/gps.dat", "r");
    if (!file)
    {
        Serial.println("Failed to open file for reading");
        return;
    }

    String fileContent = file.readString();
    file.close();

    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, "[" + fileContent + "]");

    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
    }
    for (JsonObject entry : doc.as<JsonArray>())
    {
        String output;
        serializeJson(entry, output);

        if (client.connected())
        {
            publishData("history", output.c_str());
        }

        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
    LittleFS.remove("/gps.dat");
}

void loadTemp_HumiFromFile()
{
    File file = LittleFS.open("/temp_humi.dat", "r");
    if (!file)
    {
        Serial.println("Failed to open file for reading");
        return;
    }

    String fileContent = file.readString();
    file.close();

    DynamicJsonDocument doc(2048);
    DeserializationError error = deserializeJson(doc, "[" + fileContent + "]");

    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
    }
    for (JsonObject entry : doc.as<JsonArray>())
    {
        String output;
        serializeJson(entry, output);

        if (client.connected())
        {
            publishData("history", output.c_str());
        }

        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
    LittleFS.remove("/temp_humi.dat");
}

void TaskLoadHistory(void *pvParameters)
{
    loadSchedulesFromFile();
    while (true)
    {
        if (WiFi.status() == WL_CONNECTED && client.connected())
        {
            loadGpsFromFile();
            loadTemp_HumiFromFile();
            break;
        }
    }
    vTaskDelete(NULL);
}