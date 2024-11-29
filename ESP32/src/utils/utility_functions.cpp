#include "utility_functions.h"

void parseJson(String message, bool server)
{
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, message);
    if (error)
    {
        return;
    }

    if (!server)
    {
        if (doc["email"].as<String>() != EMAIL)
        {
            return;
        }
    }

    String mode = doc["mode"].as<String>();
    if (mode == "Manual")
    {
        int index = doc["index"];
        String state = doc["state"].as<String>();
        sendValue(index, state);
    }

    else if (mode == "Schedule")
    {
        int id = doc["id"];
        if (doc.containsKey("delete") && strcmp(doc["delete"], "true") == 0)
        {
            deleteScheduleById(id);
            return;
        }
        const char *state_str = doc["state"];
        bool state = false;
        if (strcmp(state_str, "true") == 0)
        {
            state = true;
        }
        else if (strcmp(state_str, "false") == 0)
        {
            state = false;
        }
        String time = doc["time"];
        JsonArray days = doc["days"];
        JsonArray actions = doc["actions"];

        bool found = false;
        for (int i = 0; i < scheduleCount; i++)
        {
            if (schedules[i].id == id)
            {
                schedules[i].state = state;
                schedules[i].time = time;

                String uniqueDays[MAX_DAYS];
                int dayIndex = 0;

                for (size_t j = 0; j < days.size(); j++)
                {
                    String day = days[j].as<String>();
                    bool isUnique = true;
                    for (int k = 0; k < dayIndex; k++)
                    {
                        if (uniqueDays[k] == day)
                        {
                            isUnique = false;
                            break;
                        }
                    }
                    if (isUnique)
                    {
                        if (dayIndex < MAX_DAYS)
                        {
                            uniqueDays[dayIndex++] = day;
                        }
                    }
                }

                for (int j = 0; j < dayIndex; j++)
                {
                    schedules[i].days[j] = uniqueDays[j];
                }

                for (int j = dayIndex; j < MAX_DAYS; j++)
                {
                    schedules[i].days[j] = "";
                }

                schedules[i].actionCount = actions.size();
                for (size_t j = 0; j < actions.size(); j++)
                {
                    schedules[i].actions[j].relayId = actions[j]["relayId"];
                    schedules[i].actions[j].action = actions[j]["action"].as<String>();
                }
                found = true;
                break;
            }
        }

        if (!found && scheduleCount < MAX_SCHEDULES)
        {

            schedules[scheduleCount].id = id;
            schedules[scheduleCount].state = state;
            schedules[scheduleCount].time = time;

            int dayIndex = 0;
            for (size_t j = 0; j < days.size(); j++)
            {
                String day = days[j].as<String>();
                bool isUnique = true;
                for (int k = 0; k < dayIndex; k++)
                {
                    if (schedules[scheduleCount].days[k] == day)
                    {
                        isUnique = false;
                        break;
                    }
                }
                if (isUnique)
                {
                    if (dayIndex < MAX_DAYS)
                    {
                        schedules[scheduleCount].days[dayIndex++] = day;
                    }
                }
            }

            for (int j = dayIndex; j < MAX_DAYS; j++)
            {
                schedules[scheduleCount].days[j] = "";
            }

            schedules[scheduleCount].actionCount = actions.size();
            for (size_t j = 0; j < actions.size(); j++)
            {
                schedules[scheduleCount].actions[j].relayId = actions[j]["relayId"];
                schedules[scheduleCount].actions[j].action = actions[j]["action"].as<String>();
            }
            scheduleCount++;
        }
        saveSchedulesToFile();
    }
}
