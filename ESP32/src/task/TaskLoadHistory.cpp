#include "TaskLoadHistory.h"

void loadSchedulesFromFile()
{
    File file = LittleFS.open("/schedules.dat", "r");
    if (!file)
    {
        Serial.println("Failed to open file for reading");
        return;
    }

    DynamicJsonDocument doc(2048);

    DeserializationError error = deserializeJson(doc, file);
    if (error)
    {
        Serial.println("Failed to parse schedules JSON");
        file.close();
        return;
    }

    JsonArray scheduleArray = doc["schedules"];
    schedules = DLinkedList();

    for (JsonObject scheduleObj : scheduleArray)
    {
        Schedule schedule;
        schedule.id = scheduleObj["id"];
        schedule.state = scheduleObj["state"];
        schedule.time = scheduleObj["time"].as<String>();

        JsonArray daysArray = scheduleObj["days"];
        for (int i = 0; i < MAX_DAYS; i++)
        {
            if (i < daysArray.size())
            {
                schedule.days[i] = daysArray[i].as<String>();
            }
            else
            {
                schedule.days[i] = "";
            }
        }

        JsonArray actionsArray = scheduleObj["actions"];
        schedule.actionCount = actionsArray.size();
        for (int i = 0; i < actionsArray.size(); i++)
        {
            schedule.actions[i].relayId = actionsArray[i]["relayId"];
            schedule.actions[i].action = actionsArray[i]["action"].as<String>();
        }

        schedule.lastTriggered = scheduleObj["lastTriggered"].as<String>();

        schedules.add(schedule);
    }

    file.close();
    Serial.println("Schedules loaded successfully");
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

    String fileContent = file.readString(); // Đọc toàn bộ nội dung file thành chuỗi
    file.close();

    // Deserialize JSON thành một JsonArray
    DynamicJsonDocument doc(4096); // Tăng kích thước nếu file lớn hơn
    DeserializationError error = deserializeJson(doc, "[" + fileContent + "]");

    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
    }

    // Serialize toàn bộ JsonArray thành chuỗi JSON
    String output;
    serializeJson(doc.as<JsonArray>(), output);

    // Gửi toàn bộ chuỗi JSON qua MQTT hoặc WebSocket
    Serial.println(output);
    if (client.connected())
    {
        publishData("history", output.c_str());
    }

    // Xóa file sau khi gửi
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