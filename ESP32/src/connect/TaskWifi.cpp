#include "TaskWifi.h"

void startSTA()
{
    if (WIFI_SSID.isEmpty())
    {
        vTaskDelete(NULL);
    }

    WiFi.mode(WIFI_STA);

    if (WIFI_PASS.isEmpty())
    {
        WiFi.begin(WIFI_SSID.c_str());
    }
    else
    {
        WiFi.begin(WIFI_SSID.c_str(), WIFI_PASS.c_str());
    }

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
    }

    Device_ID = String(WiFi.macAddress());
    DynamicJsonDocument doc(512);
    doc["Device_ID"] = Device_ID;

    File configFile = LittleFS.open("/info.dat", "a");
    if (configFile)
    {
        serializeJson(doc, configFile);
    }
    configFile.close();
}

bool Wifi_reconnect()
{
    const wl_status_t status = WiFi.status();
    if (status == WL_CONNECTED)
    {
        return true;
    }
    startSTA();
    return false;
}
