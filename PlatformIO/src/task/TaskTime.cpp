#include "TaskTime.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, ntpServer, utcOffsetInSeconds);
String current;
String date;

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
            String data = "{\"current\":\"" + current + "\"}";
            if (ws.count() > 0)
            {
                ws.textAll(data);
            }
        }
        vTaskDelay(delay_minute / portTICK_PERIOD_MS);
    }
}
