// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 8.3.11
// Project name: ui

#ifndef _UI_UI_H
#define _UI_UI_H

#ifdef __cplusplus
extern "C" {
#endif

    #include "lvgl.h"

#include "ui_helpers.h"
#include "ui_events.h"

// SCREEN: ui_Screen1
void ui_Screen1_screen_init(void);
extern lv_obj_t *ui_Screen1;
extern lv_obj_t *ui_Panel1;
extern lv_obj_t *ui_Panel3;
extern lv_obj_t *ui_Label1;
extern lv_obj_t *ui_Panel4;
extern lv_obj_t *ui_Label2;
extern lv_obj_t *ui_ImgButton2;
void ui_event_Panel5( lv_event_t * e);
extern lv_obj_t *ui_Panel5;
extern lv_obj_t *ui_Label3;
void ui_event_ImgButton3( lv_event_t * e);
extern lv_obj_t *ui_ImgButton3;
void ui_event_Panel6( lv_event_t * e);
extern lv_obj_t *ui_Panel6;
extern lv_obj_t *ui_Label4;
void ui_event_ImgButton4( lv_event_t * e);
extern lv_obj_t *ui_ImgButton4;
extern lv_obj_t *ui_Panel2;
extern lv_obj_t *ui_Panel25;
extern lv_obj_t *ui_Panel27;
extern lv_obj_t *ui_Image1;
extern lv_obj_t *ui_Label19;
extern lv_obj_t *ui_Panel28;
extern lv_obj_t *ui_Image2;
extern lv_obj_t *ui_Label20;
extern lv_obj_t *ui_Panel26;
extern lv_obj_t *ui_Panel29;
extern lv_obj_t *ui_Label21;
extern lv_obj_t *ui_Panel30;
extern lv_obj_t *ui_Label22;
extern lv_obj_t *ui_Panel31;
extern lv_obj_t *ui_Label24;
extern lv_obj_t *ui_Panel32;
extern lv_obj_t *ui_Label25;
extern lv_obj_t *ui_Panel33;
extern lv_obj_t *ui_Label26;
extern lv_obj_t *ui_Panel34;
extern lv_obj_t *ui_Label27;
// CUSTOM VARIABLES

// SCREEN: ui_Screen2
void ui_Screen2_screen_init(void);
extern lv_obj_t *ui_Screen2;
extern lv_obj_t *ui_Panel7;
extern lv_obj_t *ui_Panel8;
extern lv_obj_t *ui_Label5;
void ui_event_Panel9( lv_event_t * e);
extern lv_obj_t *ui_Panel9;
extern lv_obj_t *ui_Label6;
void ui_event_ImgButton1( lv_event_t * e);
extern lv_obj_t *ui_ImgButton1;
extern lv_obj_t *ui_Panel10;
extern lv_obj_t *ui_Label7;
extern lv_obj_t *ui_ImgButton5;
void ui_event_Panel11( lv_event_t * e);
extern lv_obj_t *ui_Panel11;
extern lv_obj_t *ui_Label8;
void ui_event_ImgButton6( lv_event_t * e);
extern lv_obj_t *ui_ImgButton6;
extern lv_obj_t *ui_Panel12;
extern lv_obj_t *ui_Panel19;
extern lv_obj_t *ui_Label13;
void ui_event_Switch1( lv_event_t * e);
extern lv_obj_t *ui_Switch1;
extern lv_obj_t *ui_Panel20;
extern lv_obj_t *ui_Label14;
void ui_event_Switch2( lv_event_t * e);
extern lv_obj_t *ui_Switch2;
extern lv_obj_t *ui_Panel21;
extern lv_obj_t *ui_Label15;
void ui_event_Switch3( lv_event_t * e);
extern lv_obj_t *ui_Switch3;
extern lv_obj_t *ui_Panel22;
extern lv_obj_t *ui_Label16;
void ui_event_Switch4( lv_event_t * e);
extern lv_obj_t *ui_Switch4;
extern lv_obj_t *ui_Panel23;
extern lv_obj_t *ui_Label17;
void ui_event_Switch5( lv_event_t * e);
extern lv_obj_t *ui_Switch5;
extern lv_obj_t *ui_Panel24;
extern lv_obj_t *ui_Label18;
void ui_event_Switch6( lv_event_t * e);
extern lv_obj_t *ui_Switch6;
// CUSTOM VARIABLES

// SCREEN: ui_Screen3
void ui_Screen3_screen_init(void);
extern lv_obj_t *ui_Screen3;
extern lv_obj_t *ui_Panel13;
extern lv_obj_t *ui_Panel14;
extern lv_obj_t *ui_Label9;
void ui_event_Panel15( lv_event_t * e);
extern lv_obj_t *ui_Panel15;
extern lv_obj_t *ui_Label10;
void ui_event_ImgButton7( lv_event_t * e);
extern lv_obj_t *ui_ImgButton7;
void ui_event_Panel16( lv_event_t * e);
extern lv_obj_t *ui_Panel16;
extern lv_obj_t *ui_Label11;
void ui_event_ImgButton8( lv_event_t * e);
extern lv_obj_t *ui_ImgButton8;
extern lv_obj_t *ui_Panel17;
extern lv_obj_t *ui_Label12;
extern lv_obj_t *ui_ImgButton9;
extern lv_obj_t *ui_Panel18;
// CUSTOM VARIABLES

// EVENTS
extern lv_obj_t *ui____initial_actions0;

// IMAGES AND IMAGE SETS
LV_IMG_DECLARE( ui_img_home_png);   // assets/home.png
LV_IMG_DECLARE( ui_img_toggle_png);   // assets/toggle.png
LV_IMG_DECLARE( ui_img_schedule_png);   // assets/schedule.png
LV_IMG_DECLARE( ui_img_gauge_png);   // assets/gauge.png

// UI INIT
void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
