#include "TaskSchedule.h"

Schedule schedules[MAX_SCHEDULES];
int scheduleCount = 0;

String scheduleToJson(const Schedule &schedule)
{
    JsonDocument doc;
    doc["id"] = schedule.id;
    doc["state"] = schedule.state;
    JsonArray daysArray = doc["days"].to<JsonArray>();
    for (int i = 0; i < MAX_DAYS; i++)
    {
        if (!schedule.days[i].isEmpty())
        {
            daysArray.add(schedule.days[i]);
        }
    }

    doc["time"] = schedule.time;
    JsonArray actionsArray = doc["actions"].to<JsonArray>();
    for (int i = 0; i < schedule.actionCount; i++)
    {
        JsonObject actionObj = actionsArray.createNestedObject();
        actionObj["relayId"] = schedule.actions[i].relayId;
        actionObj["action"] = schedule.actions[i].action;
    }
    String jsonString;
    serializeJson(doc, jsonString);
    return jsonString;
}

void sendSchedules()
{
    DynamicJsonDocument doc(2048);
    JsonArray scheduleArray = doc.createNestedArray("schedule");
    for (int i = 0; i < scheduleCount; i++)
    {
        String scheduleJson = scheduleToJson(schedules[i]);
        DynamicJsonDocument scheduleDoc(1024);
        deserializeJson(scheduleDoc, scheduleJson);
        scheduleArray.add(scheduleDoc.as<JsonObject>());
    }
    String result;
    if (scheduleCount <= 0)
    {
        result = "[]";
    }
    else
    {
        serializeJson(doc, result);
    }
    ws.textAll(result);
}

void saveSchedulesToFile()
{
    File file = LittleFS.open("/schedules.dat", "w");
    if (!file)
    {
        Serial.println("Failed to open file for writing");
        return;
    }

    file.write((uint8_t *)schedules, sizeof(schedules));
    file.write((uint8_t *)&scheduleCount, sizeof(scheduleCount));

    file.close();
}

void deleteScheduleById(int id)
{
    for (int i = 0; i < scheduleCount; i++)
    {
        if (schedules[i].id == id)
        {
            for (int j = i; j < scheduleCount - 1; j++)
            {
                schedules[j] = schedules[j + 1];
            }
            scheduleCount--;
            saveSchedulesToFile();
            break;
        }
    }
}

void checkSchedules()
{
    int spaceIndex = current.indexOf(' ');
    String currentDay = current.substring(0, spaceIndex);
    String currentTime = current.substring(spaceIndex + 1);

    if (ws.count() > 0)
    {
        sendSchedules();
    }
    for (int i = 0; i < scheduleCount; i++)
    {
        if (!schedules[i].state)
        {
            continue;
        }
        bool dayMatch = false;
        for (int d = 0; d < MAX_DAYS; d++)
        {
            if (schedules[i].days[d] == currentDay)
            {
                dayMatch = true;
                break;
            }
        }
        if (dayMatch && (schedules[i].time == currentTime))
        {
            for (int a = 0; a < schedules[i].actionCount; a++)
            {
                sendValue(schedules[i].actions[a].relayId, schedules[i].actions[a].action);
            }
        }
    }
}

void TaskSchedule(void *pvParameters)
{
    while (true)
    {
        if (WiFi.status() != WL_CONNECTED || !client.connected())
        {
            vTaskDelay(100 / portTICK_PERIOD_MS);
            continue;
        }
        checkSchedules();
        vTaskDelay(delay_time / portTICK_PERIOD_MS);
    }
}