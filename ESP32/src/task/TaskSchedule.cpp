#include "TaskSchedule.h"

DLinkedList schedules;

String scheduleToJson(const Schedule &schedule)
{
    JsonDocument doc;
    doc["id"] = schedule.id;
    doc["state"] = schedule.state;
    doc["lastTriggered"] = "";
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

    if (schedules.empty())
    {
        JsonArray scheduleArray = doc.createNestedArray("schedule");
    }
    else
    {
        JsonArray scheduleArray = doc.createNestedArray("schedule");
        for (int i = 0; i < schedules.size(); i++)
        {
            Schedule *schedule = schedules.getAt(i);
            String scheduleJson = scheduleToJson(*schedule);

            DynamicJsonDocument scheduleDoc(1024);
            deserializeJson(scheduleDoc, scheduleJson);
            scheduleArray.add(scheduleDoc.as<JsonObject>());
        }
    }

    String result;
    serializeJson(doc, result);
    ws.textAll(result);
}

void saveSchedulesToFile()
{
    File file = LittleFS.open("/schedules.dat", "w");
    if (!file)
    {
        Serial.println("Không thể mở file để ghi");
        return;
    }

    DynamicJsonDocument doc(2048);
    JsonArray scheduleArray = doc.createNestedArray("schedules");
    for (int i = 0; i < schedules.size(); i++)
    {
        Schedule *schedule = schedules.getAt(i);
        JsonObject scheduleObj = scheduleArray.createNestedObject();

        scheduleObj["id"] = schedule->id;
        scheduleObj["state"] = schedule->state;
        scheduleObj["time"] = schedule->time;

        JsonArray daysArray = scheduleObj.createNestedArray("days");
        for (int d = 0; d < MAX_DAYS; d++)
        {
            if (!schedule->days[d].isEmpty())
            {
                daysArray.add(schedule->days[d]);
            }
        }

        JsonArray actionsArray = scheduleObj.createNestedArray("actions");
        for (int a = 0; a < schedule->actionCount; a++)
        {
            JsonObject actionObj = actionsArray.createNestedObject();
            actionObj["relayId"] = schedule->actions[a].relayId;
            actionObj["action"] = schedule->actions[a].action;
        }
    }

    if (serializeJson(doc, file) == 0)
    {
        Serial.println("Không thể ghi JSON vào file");
    }

    file.close();
    Serial.println("Lịch trình đã được lưu thành công");
}

void deleteScheduleById(int id)
{
    for (int i = 0; i < schedules.size(); i++)
    {
        Schedule *schedule = schedules.getAt(i);
        if (schedule->id == id)
        {
            schedules.removeAt(i);
            saveSchedulesToFile();
            Serial.printf("Schedule with ID %d deleted.\n", id);
            return;
        }
    }
    Serial.printf("Schedule with ID %d not found.\n", id);
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

    for (int i = 0; i < schedules.size(); i++)
    {
        Schedule *schedule = schedules.getAt(i);

        if (!schedule->state)
        {
            continue;
        }

        bool dayMatch = false;
        for (int d = 0; d < MAX_DAYS; d++)
        {
            if (schedule->days[d] == currentDay)
            {
                dayMatch = true;
                break;
            }
        }

        if (dayMatch && (schedule->time == currentTime))
        {
            if (schedule->lastTriggered != currentTime)
            {
                for (int a = 0; a < schedule->actionCount; a++)
                {
                    sendValue(schedule->actions[a].relayId, schedule->actions[a].action);
                }
                schedule->lastTriggered = currentTime;
            }
        }
    }
}

void TaskSchedule(void *pvParameters)
{
    while (true)
    {
        checkSchedules();
        vTaskDelay(delay_time / portTICK_PERIOD_MS);
    }
}