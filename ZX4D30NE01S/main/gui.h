#ifndef GUI_H
#define GUI_H

#include "lvgl/lvgl.h"
#include "stdio.h"

void update_ip(char ip_str[16]);
void update_time(char time_str[30]);
void update_gui(float temperature, float humidity, float latitude, float longitude);
void update_relay(int relay, bool state);

#endif