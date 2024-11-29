#include "TaskMQTT.h"

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char *topic, byte *payload, unsigned int length)
{
    String message;
    for (unsigned int i = 0; i < length; i++)
    {
        message += (char)payload[i];
    }
    if (strcmp(topic, (String(IO_USERNAME) + "/feeds/relay").c_str()) == 0)
    {
        parseJson(message, false);
    }
    else if (strcmp(topic, (String(IO_USERNAME) + "/feeds/schedule").c_str()) == 0)
    {
        parseJson(message, false);
    }
}

void publishData(String feed, String data)
{
    String topic = String(IO_USERNAME) + "/feeds/" + feed;
    if (client.connected())
    {
        client.publish(topic.c_str(), data.c_str());
    }
}

void reconnectMQTT()
{
    while (!client.connected())
    {
        Serial.println("Connecting to MQTT...");
        String clientId = "ESP32Client" + String(random(0, 1000));
        if (client.connect(clientId.c_str(), IO_USERNAME.c_str(), IO_KEY.c_str()))
        {
            Serial.println("MQTT Connected");

            client.subscribe((String(IO_USERNAME) + "/feeds/relay").c_str());
            client.subscribe((String(IO_USERNAME) + "/feeds/schedule").c_str());

            String data = "{\"email\":\"" + String(EMAIL) + "\",\"data\":\"" + WiFi.localIP().toString() + "\"}";
            publishData("ip", data);
            Serial.println("Start");
        }
        else
        {
            Serial.print("MQTT connection failed, rc=");
            Serial.println(client.state());
            vTaskDelay(5000 / portTICK_PERIOD_MS);
        }
    }
}

void TaskMQTT(void *pvParameters)
{
    while (WiFi.status() != WL_CONNECTED)
    {
        vTaskDelay(delay_connect / portTICK_PERIOD_MS);
    }

    client.setServer(MQTT_SERVER, MQTT_PORT);
    client.setCallback(callback);

    while (true)
    {
        if (!client.connected())
        {
            reconnectMQTT();
        }

        client.loop();
        vTaskDelay(delay_mqtt / portTICK_PERIOD_MS);
    }
}

void mqtt_init()
{
    xTaskCreate(TaskMQTT, "TaskMQTT", 4096, NULL, 1, NULL);
}