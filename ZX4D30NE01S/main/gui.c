#include "gui.h"

lv_obj_t *current_ip_label;
lv_obj_t *current_time_label;
lv_obj_t *temperature_label;
lv_obj_t *humidity_label;
lv_obj_t *latitude_label;
lv_obj_t *longitude_label;

lv_obj_t *relay_card_1;
lv_obj_t *relay_card_2;
lv_obj_t *relay_card_3;
lv_obj_t *relay_card_4;
lv_obj_t *relay_card_5;
lv_obj_t *relay_card_6;

void lv_example_esp32_web_server(void)
{
    /* Create nav bar */
    lv_obj_t *nav_bar = lv_obj_create(lv_scr_act());
    lv_obj_set_size(nav_bar, 500, 40);
    lv_obj_align(nav_bar, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_bg_color(nav_bar, lv_color_hex(0x143642), 0);
    lv_obj_set_style_bg_opa(nav_bar, LV_OPA_COVER, 0);

    /* Title in nav bar */
    lv_obj_t *title = lv_label_create(nav_bar);
    lv_label_set_text(title, "ESP WebSocket Server");
    lv_obj_align(title, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(title, lv_color_hex(0xFFFFFF), 0);

    /* Display card for time */
    lv_obj_t *current_time_card = lv_obj_create(lv_scr_act());
    lv_obj_set_size(current_time_card, 150, 40);
    lv_obj_align(current_time_card, LV_ALIGN_TOP_LEFT, 80, 50);

    current_time_label = lv_label_create(current_time_card);
    lv_label_set_text(current_time_label, "00:00");
    lv_obj_align(current_time_label, LV_ALIGN_CENTER, 0, 0);

    /* Display card for IP */
    lv_obj_t *current_ip_card = lv_obj_create(lv_scr_act());
    lv_obj_set_size(current_ip_card, 150, 40);
    lv_obj_align(current_ip_card, LV_ALIGN_TOP_RIGHT, -80, 50);

    current_ip_label = lv_label_create(current_ip_card);
    lv_label_set_text(current_ip_label, "0.0.0.0");
    lv_obj_align(current_ip_label, LV_ALIGN_CENTER, 0, 0);

    /* Card for temperature and humidity */
    lv_obj_t *temp_humi_card = lv_obj_create(lv_scr_act());
    lv_obj_set_size(temp_humi_card, 400, 80);
    lv_obj_align(temp_humi_card, LV_ALIGN_TOP_MID, 0, 100);

    temperature_label = lv_label_create(temp_humi_card);
    lv_label_set_text(temperature_label, "Temperature: 0.00 °C");
    lv_obj_align(temperature_label, LV_ALIGN_TOP_LEFT, 8, 4);

    humidity_label = lv_label_create(temp_humi_card);
    lv_label_set_text(humidity_label, "Humidity: 0.00 %");
    lv_obj_align(humidity_label, LV_ALIGN_TOP_LEFT, 200, 4);

    latitude_label = lv_label_create(temp_humi_card);
    lv_label_set_text(latitude_label, "Coordinate X: 0.00");
    lv_obj_align(latitude_label, LV_ALIGN_TOP_LEFT, 8, 32);

    longitude_label = lv_label_create(temp_humi_card);
    lv_label_set_text(longitude_label, "Coordinate Y: 0.00");
    lv_obj_align(longitude_label, LV_ALIGN_TOP_LEFT, 200, 32);

    /* Relay 1 */
    relay_card_1 = lv_obj_create(lv_scr_act());
    lv_obj_set_size(relay_card_1, 80, 35);
    lv_obj_align(relay_card_1, LV_ALIGN_TOP_LEFT, 32, 190);

    lv_obj_t *relay_label_1 = lv_label_create(relay_card_1);
    lv_label_set_text(relay_label_1, "Relay 1");
    lv_obj_align(relay_label_1, LV_ALIGN_CENTER, 0, 0);

    /* Relay 2 */
    relay_card_2 = lv_obj_create(lv_scr_act());
    lv_obj_set_size(relay_card_2, 80, 35);
    lv_obj_align(relay_card_2, LV_ALIGN_TOP_LEFT, 144, 190);

    lv_obj_t *relay_label_2 = lv_label_create(relay_card_2);
    lv_label_set_text(relay_label_2, "Relay 2");
    lv_obj_align(relay_label_2, LV_ALIGN_CENTER, 0, 0);

    /* Relay 3 */
    relay_card_3 = lv_obj_create(lv_scr_act());
    lv_obj_set_size(relay_card_3, 80, 35);
    lv_obj_align(relay_card_3, LV_ALIGN_TOP_LEFT, 256, 190);

    lv_obj_t *relay_label_3 = lv_label_create(relay_card_3);
    lv_label_set_text(relay_label_3, "Relay 3");
    lv_obj_align(relay_label_3, LV_ALIGN_CENTER, 0, 0);

    /* Relay 4 */
    relay_card_4 = lv_obj_create(lv_scr_act());
    lv_obj_set_size(relay_card_4, 80, 35);
    lv_obj_align(relay_card_4, LV_ALIGN_TOP_LEFT, 368, 190);

    lv_obj_t *relay_label_4 = lv_label_create(relay_card_4);
    lv_label_set_text(relay_label_4, "Relay 4");
    lv_obj_align(relay_label_4, LV_ALIGN_CENTER, 0, 0);

    /* Relay 5 */
    relay_card_5 = lv_obj_create(lv_scr_act());
    lv_obj_set_size(relay_card_5, 160, 35);
    lv_obj_align(relay_card_5, LV_ALIGN_TOP_LEFT, 50, 230);

    lv_obj_t *relay_label_5 = lv_label_create(relay_card_5);
    lv_label_set_text(relay_label_5, "Relay 5");
    lv_obj_align(relay_label_5, LV_ALIGN_CENTER, 0, 0);

    /* Relay 6 */
    relay_card_6 = lv_obj_create(lv_scr_act());
    lv_obj_set_size(relay_card_6, 160, 35);
    lv_obj_align(relay_card_6, LV_ALIGN_TOP_RIGHT, -50, 230);

    lv_obj_t *relay_label_6 = lv_label_create(relay_card_6);
    lv_label_set_text(relay_label_6, "Relay 6");
    lv_obj_align(relay_label_6, LV_ALIGN_CENTER, 0, 0);
}

/* Function to update GUI */

void update_time(char time_str[30])
{
    lv_label_set_text(current_time_label, time_str);
}

void update_ip(char ip_str[16])
{
    lv_label_set_text(current_ip_label, ip_str);
}

void update_gui(float temperature, float humidity, float latitude, float longitude)
{
    char buffer[50];

    sprintf(buffer, "Temperature: %.2f °C", temperature);
    lv_label_set_text(temperature_label, buffer);

    sprintf(buffer, "Humidity: %.2f %%", humidity);
    lv_label_set_text(humidity_label, buffer);

    sprintf(buffer, "Coordinate X: %.2f", latitude);
    lv_label_set_text(latitude_label, buffer);

    sprintf(buffer, "Coordinate Y: %.2f", longitude);
    lv_label_set_text(longitude_label, buffer);
}

void update_relay(int relay, bool state)
{
    lv_obj_t *relay_card;

    switch (relay)
    {
    case 1:
        relay_card = relay_card_1;
        break;
    case 2:
        relay_card = relay_card_2;
        break;
    case 3:
        relay_card = relay_card_3;
        break;
    case 4:
        relay_card = relay_card_4;
        break;
    case 5:
        relay_card = relay_card_5;
        break;
    case 6:
        relay_card = relay_card_6;
        break;
    default:
        printf("Invalid relay: %d\n", relay);
        return;
    }

    lv_obj_set_style_bg_color(relay_card, (state ? lv_color_hex(0x90EE90) : lv_color_hex(0xFFFFFF)), 0);
}
