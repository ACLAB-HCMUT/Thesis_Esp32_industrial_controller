#include "gui.h"

lv_obj_t *temperature_label;
lv_obj_t *humidity_label;
lv_obj_t *latitude_label;
lv_obj_t *longitude_label;

void lv_example_esp32_web_server(void)
{
    /* Tạo thanh nav */
    lv_obj_t *nav_bar = lv_obj_create(lv_scr_act());
    lv_obj_set_size(nav_bar, 500, 40);
    lv_obj_align(nav_bar, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_bg_color(nav_bar, lv_color_hex(0x143642), 0);
    lv_obj_set_style_bg_opa(nav_bar, LV_OPA_COVER, 0);

    /* Tiêu đề trong thanh nav */
    lv_obj_t *title = lv_label_create(nav_bar);
    lv_label_set_text(title, "ESP WebSocket Server");
    lv_obj_align(title, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(title, lv_color_hex(0xFFFFFF), 0);

    /* Thẻ hiển thị thời gian */
    lv_obj_t *current_time_card = lv_obj_create(lv_scr_act());
    lv_obj_set_size(current_time_card, 200, 40);
    lv_obj_align(current_time_card, LV_ALIGN_TOP_MID, 0, 50);

    lv_obj_t *current_time_label = lv_label_create(current_time_card);
    lv_label_set_text(current_time_label, "00:00");
    lv_obj_align(current_time_label, LV_ALIGN_CENTER, 0, 0);

    /* Thẻ hiển thị nhiệt độ và độ ẩm */
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
    lv_obj_t *relay_card_1 = lv_obj_create(lv_scr_act());
    lv_obj_set_size(relay_card_1, 80, 35);
    lv_obj_align(relay_card_1, LV_ALIGN_TOP_LEFT, 32, 190);

    lv_obj_t *relay_label_1 = lv_label_create(relay_card_1);
    lv_label_set_text(relay_label_1, "Relay 1");
    lv_obj_align(relay_label_1, LV_ALIGN_CENTER, 0, 0);

    /* Relay 2 */
    lv_obj_t *relay_card_2 = lv_obj_create(lv_scr_act());
    lv_obj_set_size(relay_card_2, 80, 35);
    lv_obj_align(relay_card_2, LV_ALIGN_TOP_LEFT, 144, 190);

    lv_obj_t *relay_label_2 = lv_label_create(relay_card_2);
    lv_label_set_text(relay_label_2, "Relay 2");
    lv_obj_align(relay_label_2, LV_ALIGN_CENTER, 0, 0);

    /* Relay 3 */
    lv_obj_t *relay_card_3 = lv_obj_create(lv_scr_act());
    lv_obj_set_size(relay_card_3, 80, 35);
    lv_obj_align(relay_card_3, LV_ALIGN_TOP_LEFT, 256, 190);

    lv_obj_t *relay_label_3 = lv_label_create(relay_card_3);
    lv_label_set_text(relay_label_3, "Relay 3");
    lv_obj_align(relay_label_3, LV_ALIGN_CENTER, 0, 0);

    /* Relay 4 */
    lv_obj_t *relay_card_4 = lv_obj_create(lv_scr_act());
    lv_obj_set_size(relay_card_4, 80, 35);
    lv_obj_align(relay_card_4, LV_ALIGN_TOP_LEFT, 368, 190);

    lv_obj_t *relay_label_4 = lv_label_create(relay_card_4);
    lv_label_set_text(relay_label_4, "Relay 4");
    lv_obj_align(relay_label_4, LV_ALIGN_CENTER, 0, 0);

    /* Relay 5 */
    lv_obj_t *relay_card_5 = lv_obj_create(lv_scr_act());
    lv_obj_set_size(relay_card_5, 80, 35);
    lv_obj_align(relay_card_5, LV_ALIGN_TOP_MID, -110, 230);

    lv_obj_t *relay_label_5 = lv_label_create(relay_card_5);
    lv_label_set_text(relay_label_5, "Relay 5");
    lv_obj_align(relay_label_5, LV_ALIGN_CENTER, 0, 0);

    /* Relay 6 */
    lv_obj_t *relay_card_6 = lv_obj_create(lv_scr_act());
    lv_obj_set_size(relay_card_6, 80, 35);
    lv_obj_align(relay_card_6, LV_ALIGN_TOP_MID, 110, 230);

    lv_obj_t *relay_label_6 = lv_label_create(relay_card_6);
    lv_label_set_text(relay_label_6, "Relay 6");
    lv_obj_align(relay_label_6, LV_ALIGN_CENTER, 0, 0);
}

/* Function to update GUI */
void update_gui(float temperature, float humidity, float latitude, float longitude)
{
    lv_label_set_text_fmt(temperature_label, "Temperature: %.2f °C", temperature);
    lv_label_set_text_fmt(humidity_label, "Humidity: %.2f %%", humidity);
    lv_label_set_text_fmt(latitude_label, "Coordinate X: %.2f", latitude);
    lv_label_set_text_fmt(longitude_label, "Coordinate Y: %.2f", longitude);
}
