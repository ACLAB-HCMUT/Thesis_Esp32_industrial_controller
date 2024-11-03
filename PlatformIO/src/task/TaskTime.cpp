#include "TaskTime.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, ntpServer, utcOffsetInSeconds);
String current;
String date = "";
bool check_different_time = false;

String getDayOfWeek(unsigned long epochTime)
{
    time_t rawTime = epochTime;
    struct tm *timeInfo = localtime(&rawTime);
    String days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    return days[timeInfo->tm_wday];
}

void syncTimeWithNTP()
{
    configTime(utcOffsetInSeconds, 0, ntpServer);
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Không thể lấy thời gian từ NTP");
        return;
    }
}

bool checkTimeChange(const String &date_old, const String &date_new)
{
    String time_old = date_old.substring(0, 5);
    String time_new = date_new.substring(0, 5);

    String hour_old = time_old.substring(0, 2);
    String hour_new = time_new.substring(0, 2);

    String day_old = date_old.substring(6);
    String day_new = date_new.substring(6);

    if (hour_old != hour_new || day_old != day_new)
    {
        return true;
    }

    return false;
}

void TaskTime(void *pvParameters)
{
    while (WiFi.status() != WL_CONNECTED)
    {
        vTaskDelay(delay_connect / portTICK_PERIOD_MS);
        continue;
    }

    syncTimeWithNTP();

    while (true)
    {
        if (WiFi.status() == WL_CONNECTED)
        {
            timeClient.update();
        }

        struct tm timeinfo;
        if (getLocalTime(&timeinfo))
        {
            char dateBuffer[11];
            strftime(dateBuffer, sizeof(dateBuffer), "%d:%m:%Y", &timeinfo);

            String currentDay = getDayOfWeek(mktime(&timeinfo));
            char currentTime[6];
            strftime(currentTime, sizeof(currentTime), "%H:%M", &timeinfo);
            current = currentDay + " " + String(currentTime);
            date = String(currentTime) + "-" + String(dateBuffer);
            String date_new = String(currentTime) + "-" + String(dateBuffer);
            check_different_time = checkTimeChange(date, date_new);
            date = date_new;
            String data = "{\"current\":\"" + current + "\"}";
            if (ws.count() > 0)
            {
                ws.textAll(data);
            }
        }
        vTaskDelay(delay_time / portTICK_PERIOD_MS);
    }
}
