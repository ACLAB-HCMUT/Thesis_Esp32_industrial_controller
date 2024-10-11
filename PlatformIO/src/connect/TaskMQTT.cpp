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
        parseJson(message);
    }
    else if (strcmp(topic, (String(IO_USERNAME) + "/feeds/schedule").c_str()) == 0)
    {
        parseJson(message);
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

void TaskMQTT(void *pvParameters)
{
    while (WiFi.status() != WL_CONNECTED)
    {
        vTaskDelay(delay_connect / portTICK_PERIOD_MS);
    }

    client.setServer(MQTT_SERVER, MQTT_PORT);
    client.setCallback(callback);
    while (!client.connected())
    {
        Serial.println("Connecting to MQTT...");
        String clientId = "ESP32Client" + String(random(0, 1000));
        if (client.connect(clientId.c_str(), IO_USERNAME, IO_KEY))
        {
            Serial.println("MQTT Connected");
            client.subscribe((String(IO_USERNAME) + "/feeds/relay").c_str());
            client.subscribe((String(IO_USERNAME) + "/feeds/schedule").c_str());
            String sendData = WiFi.localIP().toString();
            publishData("ip", sendData);
            Serial.println(sendData);
            Serial.println("Start");
            while (true)
            {
                client.loop();
                vTaskDelay(delay_connect / portTICK_PERIOD_MS);
            }
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            vTaskDelay(delay_temp / portTICK_PERIOD_MS);
        }
    }
}

void reconnect()
{
    xTaskCreate(TaskMQTT, "TaskMQTT", 4096, NULL, 1, NULL);
}

void mqtt_init()
{
    xTaskCreate(TaskMQTT, "TaskMQTT", 4096, NULL, 1, NULL);
}