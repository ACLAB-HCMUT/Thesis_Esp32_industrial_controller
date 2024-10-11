#ifndef GUI_H
#define GUI_H

#include "lvgl/lvgl.h"

extern lv_obj_t *temperature_label;
extern lv_obj_t *humidity_label;
extern lv_obj_t *latitude_label;
extern lv_obj_t *longitude_label;

void update_gui(float temperature, float humidity, float latitude, float longitude);
#endif