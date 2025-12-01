#include "TaskTime.h"
#include "WiFi.h"
#include "NTPClient.h"
#include "esp_timer.h"

WiFiUDP ntpUDP;

// ❗ KHÔNG đặt offset trong NTPClient
NTPClient timeClient(ntpUDP, "pool.ntp.org");

unsigned long baseTime = 0;
unsigned long baseMillis = 0;

String current = "";
String check_time = "";
String date = "";
bool check_different_time = false;

String getDayOfWeek(unsigned long epochTime)
{
    time_t rawTime = epochTime;
    struct tm *timeInfo = localtime(&rawTime);

    String days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    return days[timeInfo->tm_wday];
}

void syncTimeOnceWithNTP()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        timeClient.begin();

        if (timeClient.update())
        {
            baseTime = timeClient.getEpochTime(); // Lấy epoch UTC
            baseMillis = millis();

            Serial.println("NTP synced epoch: " + String(baseTime));
        }
        else
        {
            Serial.println("Failed to update NTP!");
        }

        timeClient.end();
    }
    else
    {
        Serial.println("WiFi not connected, cannot sync NTP");
    }
}

unsigned long getCurrentTime()
{
    unsigned long elapsed = millis() - baseMillis;
    return baseTime + (elapsed / 1000);
}

String formatTime(unsigned long epochTime)
{
    time_t rawTime = epochTime;
    struct tm *timeInfo = localtime(&rawTime);

    char buffer[6];
    sprintf(buffer, "%02d:%02d", timeInfo->tm_hour, timeInfo->tm_min);
    return String(buffer);
}

String formatDateTime(unsigned long epochTime)
{
    time_t rawTime = epochTime;
    struct tm *timeInfo = localtime(&rawTime);

    char buffer[20];
    sprintf(buffer, "%02d:%02d %02d-%02d-%04d",
            timeInfo->tm_hour,
            timeInfo->tm_min,
            timeInfo->tm_mday,
            timeInfo->tm_mon + 1,
            timeInfo->tm_year + 1900);

    return String(buffer);
}

void TaskTime(void *pvParameters)
{
    // ❗ SET MÚI GIỜ CHUẨN CHO VIỆT NAM (GMT+7)
    setenv("TZ", "UTC-7", 1);
    tzset();

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("Waiting WiFi...");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    syncTimeOnceWithNTP();

    while (true)
    {
        unsigned long currentEpoch = getCurrentTime();

        String timeStr = formatTime(currentEpoch);
        String dayStr = getDayOfWeek(currentEpoch);

        date = formatDateTime(currentEpoch);
        current = dayStr + " " + timeStr;

        check_different_time = (check_time != timeStr);
        check_time = timeStr;

        String data = "{\"current\":\"" + current + "\"}";

        if (ws.count() > 0)
        {
            ws.textAll(data);
        }

        vTaskDelay(delay_time / portTICK_PERIOD_MS);
    }
}
