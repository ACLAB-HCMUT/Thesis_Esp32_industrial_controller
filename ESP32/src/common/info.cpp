#include "globals.h"

AsyncWebServer server_1(80);

String NAME_DEVICE;
String WIFI_SSID;
String WIFI_PASS;
String IO_USERNAME;
String IO_KEY;
String EMAIL;
String username_ota;
String password_ota;

void loadInfoFromFile()
{
    File file = LittleFS.open("/info.dat", "r");
    if (!file)
    {
        Serial.println("Không thể mở file để đọc");
        return;
    }
    DynamicJsonDocument doc(512);
    DeserializationError error = deserializeJson(doc, file);
    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
    }
    else
    {
        NAME_DEVICE = strdup(doc["NAME_DEVICE"]);
        WIFI_SSID = strdup(doc["WIFI_SSID"]);
        WIFI_PASS = strdup(doc["WIFI_PASS"]);
        IO_USERNAME = strdup(doc["IO_USERNAME"]);
        IO_KEY = strdup(doc["IO_KEY"]);
        EMAIL = strdup(doc["EMAIL"]);
        username_ota = strdup(doc["username_ota"]);
        password_ota = strdup(doc["password_ota"]);
    }
    file.close();
}

void deleteInfoFile()
{
    if (LittleFS.exists("/info.dat"))
    {
        LittleFS.remove("/info.dat");
    }
}

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 Configuration</title>
    <style>
        body { font-family: Arial, sans-serif; background-color: #f2f2f2; margin: 0; padding: 20px; display: flex; justify-content: center; align-items: center; height: 100vh; }
        .container { background-color: white; padding: 20px; border-radius: 8px; box-shadow: 0 0 10px rgba(0, 0, 0, 0.1); width: 300px; }
        h2 { text-align: center; color: #333; }
        label { margin-top: 10px; display: block; color: #666; }
        input[type="text"], input[type="password"], input[type="email"], select { width: 100%; padding: 10px; margin-top: 5px; border: 1px solid #ccc; border-radius: 4px; box-sizing: border-box; }
        input[type="submit"] { background-color: #4CAF50; color: white; border: none; padding: 10px; border-radius: 4px; cursor: pointer; width: 100%; margin-top: 15px; }
        input[type="submit"]:hover { background-color: #45a049; }
        .ota-title { margin-top: 20px; font-size: 18px; text-align: center; color: #333; }
    </style>
</head>
<body>
    <div class="container">
        <h2>ESP32 Configuration</h2>
        <form action="/save" method="post">
            <label for="ssid">Name Device :</label>
            <input type="text" name="name_device" id="name_device" required>

            <label for="ssid">WiFi SSID:</label>
            <input type="text" name="ssid" id="ssid" required>
            
            <label for="pass">WiFi Password:</label>
            <input type="password" name="pass" id="pass" required>

            <label for="mqtt_user">MQTT Username:</label>
            <input type="text" name="mqtt_user" id="mqtt_user" required>
            
            <label for="mqtt_key">MQTT Key:</label>
            <input type="text" name="mqtt_key" id="mqtt_key" required>

            <label for="email">Email:</label>
            <input type="email" name="email" id="email" required>

            <div class="ota-title">OTA Information</div>
            <label for="username">Username:</label>
            <input type="text" name="username" id="username" required>

            <label for="password">Password:</label>
            <input type="password" name="password" id="password" required>

            <input type="submit" value="Save">
        </form>
    </div>
</body>
</html>
)rawliteral";

void startAccessPoint()
{
    LED_ACP();
    WiFi.softAP(SSID_AP);
    Serial.println("Access Point Started");
    Serial.print("AP IP address: ");
    Serial.println(WiFi.softAPIP());

#ifdef M5_CORE2
    M5.Display.setCursor(0, 20);
    M5.Display.println("Please connect to:");
    int screenWidth = M5.Lcd.width();
    int textWidth = M5.Display.textWidth(SSID_AP);
    M5.Display.setTextColor(CYAN);
    M5.Display.setCursor((screenWidth - textWidth) / 2, 50);
    M5.Display.println(SSID_AP);
    M5.Display.setTextColor(WHITE);
    M5.Display.setCursor(0, 80);
    M5.Display.println("Then go to:");
    String ipAddress = WiFi.softAPIP().toString();
    textWidth = M5.Display.textWidth(ipAddress);
    M5.Display.setTextColor(YELLOW);
    M5.Display.setCursor((screenWidth - textWidth) / 2, 120);
    M5.Display.println(ipAddress);
#endif

    server_1.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
                { request->send_P(200, "text/html", index_html); });

    server_1.on("/save", HTTP_POST, [](AsyncWebServerRequest *request)
                {
        NAME_DEVICE = request->getParam("name_device", true)->value();
        WIFI_SSID = request->getParam("ssid", true)->value();
        WIFI_PASS = request->getParam("pass", true)->value();
        IO_USERNAME = request->getParam("mqtt_user", true)->value();
        IO_KEY = request->getParam("mqtt_key", true)->value();
        EMAIL = request->getParam("email", true)->value();
        username_ota = request->getParam("username", true)->value();
        password_ota = request->getParam("password", true)->value();

        DynamicJsonDocument doc(512);
        doc["NAME_DEVICE"] = NAME_DEVICE;
        doc["WIFI_SSID"] = WIFI_SSID;
        doc["WIFI_PASS"] = WIFI_PASS;
        doc["IO_USERNAME"] = IO_USERNAME;
        doc["IO_KEY"] = IO_KEY;
        doc["EMAIL"] = EMAIL;
        doc["username_ota"] = username_ota;
        doc["password_ota"] = password_ota;

        File configFile = LittleFS.open("/info.dat", "w");
        if (configFile) {
            serializeJson(doc, configFile);
            configFile.close();
            request->send(200, "text/html", "Configuration has been saved. ESP32 will restart...");
            delay(1000);
            ESP.restart();
        } else {
            request->send(500, "text/html", "Unable to save the configuration.");
        } });

    server_1.begin();
}

void TaskResetDevice(void *pvParameters)
{
    unsigned long buttonPressStartTime = 0;
    while (true)
    {
        if (digitalRead(BOOT) == LOW)
        {
            if (buttonPressStartTime == 0)
            {
                buttonPressStartTime = millis();
            }
            else if (millis() - buttonPressStartTime > 5000)
            {
                deleteInfoFile();
                ESP.restart();
                vTaskDelete(NULL);
            }
        }
#ifdef M5_CORE2
        else if (M5.BtnB.wasPressed())
        {
            if (buttonPressStartTime == 0)
            {
                buttonPressStartTime = millis();
            }
            else if (millis() - buttonPressStartTime > 5000)
            {
                deleteInfoFile();
                ESP.restart();
                vTaskDelete(NULL);
            }
        }
#endif
        else
        {
            buttonPressStartTime = 0;
        }
        vTaskDelay(delay_connect / portTICK_PERIOD_MS);
    }
}

void reset_device()
{
    xTaskCreate(TaskResetDevice, "TaskResetDevice", 4096, NULL, 1, NULL);
}

bool check_info()
{

#ifdef IS_LEAF
    pinMode(BOOT, INPUT);
#endif
    loadInfoFromFile();
    reset_device();
    if (NAME_DEVICE.isEmpty() || WIFI_SSID.isEmpty() || WIFI_PASS.isEmpty() || IO_USERNAME.isEmpty() || IO_KEY.isEmpty() || EMAIL.isEmpty() || username_ota.isEmpty() || password_ota.isEmpty())
    {
        startAccessPoint();
        return false;
    }
    return true;
}
