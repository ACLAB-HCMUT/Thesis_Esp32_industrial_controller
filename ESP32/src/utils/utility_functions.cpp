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
            deleteScheduleById(id); // Use the updated deleteScheduleById function
            return;
        }

        const char *state_str = doc["state"];
        bool state = (strcmp(state_str, "true") == 0); // Convert "true"/"false" to boolean
        String time = doc["time"];
        JsonArray days = doc["days"];
        JsonArray actions = doc["actions"];

        bool found = false;
        for (int i = 0; i < schedules.size(); i++)
        {
            Schedule *schedule = schedules.getAt(i);
            if (schedule->id == id)
            {
                schedule->state = state;
                schedule->time = time;
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
                    schedule->days[j] = uniqueDays[j];
                }

                for (int j = dayIndex; j < MAX_DAYS; j++)
                {
                    schedule->days[j] = "";
                }
                schedule->actionCount = actions.size();
                for (size_t j = 0; j < actions.size(); j++)
                {
                    schedule->actions[j].relayId = actions[j]["relayId"];
                    schedule->actions[j].action = actions[j]["action"].as<String>();
                }
                schedule->lastTriggered = "";
                found = true;
                break;
            }
        }

        if (!found)
        {
            // Add new schedule
            Schedule newSchedule;
            newSchedule.id = id;
            newSchedule.state = state;
            newSchedule.time = time;

            // Handle unique days
            int dayIndex = 0;
            for (size_t j = 0; j < days.size(); j++)
            {
                String day = days[j].as<String>();
                bool isUnique = true;
                for (int k = 0; k < dayIndex; k++)
                {
                    if (newSchedule.days[k] == day)
                    {
                        isUnique = false;
                        break;
                    }
                }
                if (isUnique)
                {
                    if (dayIndex < MAX_DAYS)
                    {
                        newSchedule.days[dayIndex++] = day;
                    }
                }
            }

            for (int j = dayIndex; j < MAX_DAYS; j++)
            {
                newSchedule.days[j] = "";
            }

            // Set actions
            newSchedule.actionCount = actions.size();
            for (size_t j = 0; j < actions.size(); j++)
            {
                newSchedule.actions[j].relayId = actions[j]["relayId"];
                newSchedule.actions[j].action = actions[j]["action"].as<String>();
            }

            newSchedule.lastTriggered = ""; // Initialize last triggered

            schedules.add(newSchedule); // Add the new schedule to the linked list
        }

        saveSchedulesToFile(); // Save changes
    }
}
