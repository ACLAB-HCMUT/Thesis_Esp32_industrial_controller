#include "TaskTime.h"
#include "WiFi.h"
#include "NTPClient.h"
#include "esp_timer.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 7 * 3600);

unsigned long baseTime = 0;
unsigned long baseMicros = 0;

String current = "";
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
            baseTime = timeClient.getEpochTime();
            baseMicros = esp_timer_get_time() / 1000;
            Serial.println("Thời gian từ NTP: " + String(baseTime));
        }
        else
        {
            Serial.println("Không thể cập nhật NTP!");
        }
        timeClient.end();
    }
    else
    {
        Serial.println("Không có WiFi, không thể đồng bộ NTP.");
    }
}

unsigned long getCurrentTime()
{
    unsigned long elapsedMillis = (esp_timer_get_time() / 1000) - baseMicros;
    return baseTime + (elapsedMillis / 1000);
}

String formatTime(unsigned long epochTime)
{
    time_t rawTime = epochTime;
    struct tm *timeInfo = localtime(&rawTime);

    char buffer[6];
    sprintf(buffer, "%02d:%02d", timeInfo->tm_hour, timeInfo->tm_min);

    return String(buffer);
}

void TaskTime(void *pvParameters)
{
    while (WiFi.status() != WL_CONNECTED)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    syncTimeOnceWithNTP();

    while (true)
    {
        unsigned long currentTime = getCurrentTime();
        String currentDay = formatTime(currentTime);
        String dayOfWeek = getDayOfWeek(currentTime);

        current = dayOfWeek + " " + currentDay;

        String newDate = formatTime(currentTime);
        check_different_time = (date != newDate);
        date = newDate;

        String data = "{\"current\":\"" + current + "\"}";
        if (ws.count() > 0)
        {
            ws.textAll(data);
        }

        vTaskDelay(delay_time / portTICK_PERIOD_MS);
    }
}
