#include <stdio.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "esp_event.h"
#include "esp_websocket_client.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"

#include "lvgl.h"
#include "board.h"

#include "cJSON.h"

#include "config.h"
#include "gui.h"

float temperature = 0, humidity = 0, latitude = 0, longitude = 0;
int relay = 0;
bool state = false;

static const char *TAG = "WEBSOCKET";

static void websocket_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    esp_websocket_event_data_t *data = (esp_websocket_event_data_t *)event_data;
    switch (event_id)
    {
    case WEBSOCKET_EVENT_CONNECTED:
        ESP_LOGI(TAG, "WEBSOCKET_EVENT_CONNECTED");
        char ip_str[16];
        strcpy(ip_str, websever_url);
        update_ip(ip_str);
        break;
    case WEBSOCKET_EVENT_DATA:
        ESP_LOGW(TAG, "Received=%.*s\n", data->data_len, (char *)data->data_ptr);
        if (data->data_len > 0)
        {
            cJSON *json = cJSON_Parse((char *)data->data_ptr);
            if (json != NULL)
            {
                cJSON *timeItem = cJSON_GetObjectItem(json, "current");
                cJSON *tempItem = cJSON_GetObjectItem(json, "temperature");
                cJSON *humidItem = cJSON_GetObjectItem(json, "humidity");
                cJSON *latItem = cJSON_GetObjectItem(json, "latitude");
                cJSON *longItem = cJSON_GetObjectItem(json, "longitude");
                cJSON *relayItem = cJSON_GetObjectItem(json, "index");
                cJSON *stateItem = cJSON_GetObjectItem(json, "state");

                if (timeItem != NULL)
                {
                    char time_str[30];
                    strcpy(time_str, timeItem->valuestring);
                    update_time(time_str);
                }

                if (tempItem != NULL && humidItem != NULL)
                {
                    temperature = tempItem->valuedouble;
                    humidity = humidItem->valuedouble;
                    update_gui(temperature, humidity, latitude, longitude);
                }

                if (latItem != NULL && longItem != NULL)
                {
                    latitude = latItem->valuedouble;
                    longitude = longItem->valuedouble;
                    update_gui(temperature, humidity, latitude, longitude);
                }

                if (stateItem != NULL && relayItem != NULL)
                {
                    relay = relayItem->valueint;
                    if (cJSON_IsString(stateItem) && strcmp(stateItem->valuestring, "ON") == 0)
                    {
                        state = true;
                    }
                    else
                    {
                        state = false;
                    }
                    update_relay(relay, state);
                }
            }
        }
        break;
    }
}

static void websocket_app_start(void)
{
    esp_websocket_client_config_t websocket_cfg = {};
    char websocket_uri[50];
    sprintf(websocket_uri, "ws://%s/ws", websever_url);
    websocket_cfg.uri = websocket_uri;
    ESP_LOGI(TAG, "Connecting to %s ...", websocket_cfg.uri);

    esp_websocket_client_handle_t client = esp_websocket_client_init(&websocket_cfg);
    esp_websocket_register_events(client, WEBSOCKET_EVENT_ANY, websocket_event_handler, (void *)client);

    esp_websocket_client_start(client);

    while (true)
    {
        if (!esp_websocket_client_is_connected(client))
        {
            ESP_LOGI(TAG, "WebSocket not connected, waiting...");
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    esp_websocket_client_stop(client);
    ESP_LOGI(TAG, "Websocket Stopped");
    esp_websocket_client_destroy(client);
}

static void wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    switch (event_id)
    {
    case WIFI_EVENT_STA_START:
        printf("WiFi connecting ... \n");
        break;
    case WIFI_EVENT_STA_CONNECTED:
        printf("WiFi connected ... \n");
        break;
    case WIFI_EVENT_STA_DISCONNECTED:
        printf("WiFi lost connection ... \n");
        break;
    case IP_EVENT_STA_GOT_IP:
        websocket_app_start();
        break;
    default:
        break;
    }
}

void wifi_connection()
{
    nvs_flash_init();
    esp_netif_init();
    esp_event_loop_create_default();
    esp_netif_create_default_wifi_sta();
    wifi_init_config_t wifi_initiation = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&wifi_initiation);
    esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, wifi_event_handler, NULL);
    esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, wifi_event_handler, NULL);
    wifi_config_t wifi_configuration = {
        .sta = {
            .ssid = SSID,
            .password = PASS}};
    esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_configuration);
    esp_wifi_start();
    esp_wifi_connect();
}

static void increase_lvgl_tick(void *arg)
{
    lv_tick_inc(portTICK_PERIOD_MS);
}

extern void screen_init(void);

void lvgl_task(void *arg)
{
    screen_init();

    const esp_timer_create_args_t periodic_timer_args = {
        .callback = increase_lvgl_tick,
        .name = "periodic_gui"};
    esp_timer_handle_t periodic_timer;
    esp_timer_create(&periodic_timer_args, &periodic_timer);
    esp_timer_start_periodic(periodic_timer, portTICK_PERIOD_MS * 1000);

    extern void lv_example_esp32_web_server(void);
    lv_example_esp32_web_server();

    for (;;)
    {
        lv_task_handler();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void app_main(void)
{
    wifi_connection();
    xTaskCreatePinnedToCore(lvgl_task, NULL, 8 * 1024, NULL, 5, NULL, 1);
}