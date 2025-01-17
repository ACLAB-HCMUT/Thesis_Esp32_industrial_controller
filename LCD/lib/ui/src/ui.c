// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 8.3.11
// Project name: ui

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////


// SCREEN: ui_Screen1
void ui_Screen1_screen_init(void);
lv_obj_t *ui_Screen1;
lv_obj_t *ui_Panel1;
lv_obj_t *ui_Panel3;
lv_obj_t *ui_Label1;
lv_obj_t *ui_Panel4;
lv_obj_t *ui_Label2;
lv_obj_t *ui_ImgButton2;
void ui_event_Panel5( lv_event_t * e);
lv_obj_t *ui_Panel5;
lv_obj_t *ui_Label3;
void ui_event_ImgButton3( lv_event_t * e);
lv_obj_t *ui_ImgButton3;
void ui_event_Panel6( lv_event_t * e);
lv_obj_t *ui_Panel6;
lv_obj_t *ui_Label4;
void ui_event_ImgButton4( lv_event_t * e);
lv_obj_t *ui_ImgButton4;
lv_obj_t *ui_Panel2;
lv_obj_t *ui_Panel25;
lv_obj_t *ui_Panel27;
lv_obj_t *ui_Image1;
lv_obj_t *ui_Label19;
lv_obj_t *ui_Panel28;
lv_obj_t *ui_Image2;
lv_obj_t *ui_Label20;
lv_obj_t *ui_Panel26;
lv_obj_t *ui_Panel29;
lv_obj_t *ui_Label21;
lv_obj_t *ui_Panel30;
lv_obj_t *ui_Label22;
lv_obj_t *ui_Panel31;
lv_obj_t *ui_Label24;
lv_obj_t *ui_Panel32;
lv_obj_t *ui_Label25;
lv_obj_t *ui_Panel33;
lv_obj_t *ui_Label26;
lv_obj_t *ui_Panel34;
lv_obj_t *ui_Label27;
// CUSTOM VARIABLES


// SCREEN: ui_Screen2
void ui_Screen2_screen_init(void);
lv_obj_t *ui_Screen2;
lv_obj_t *ui_Panel7;
lv_obj_t *ui_Panel8;
lv_obj_t *ui_Label5;
void ui_event_Panel9( lv_event_t * e);
lv_obj_t *ui_Panel9;
lv_obj_t *ui_Label6;
void ui_event_ImgButton1( lv_event_t * e);
lv_obj_t *ui_ImgButton1;
lv_obj_t *ui_Panel10;
lv_obj_t *ui_Label7;
lv_obj_t *ui_ImgButton5;
void ui_event_Panel11( lv_event_t * e);
lv_obj_t *ui_Panel11;
lv_obj_t *ui_Label8;
void ui_event_ImgButton6( lv_event_t * e);
lv_obj_t *ui_ImgButton6;
lv_obj_t *ui_Panel12;
lv_obj_t *ui_Panel19;
lv_obj_t *ui_Label13;
void ui_event_Switch1( lv_event_t * e);
lv_obj_t *ui_Switch1;
lv_obj_t *ui_Panel20;
lv_obj_t *ui_Label14;
void ui_event_Switch2( lv_event_t * e);
lv_obj_t *ui_Switch2;
lv_obj_t *ui_Panel21;
lv_obj_t *ui_Label15;
void ui_event_Switch3( lv_event_t * e);
lv_obj_t *ui_Switch3;
lv_obj_t *ui_Panel22;
lv_obj_t *ui_Label16;
void ui_event_Switch4( lv_event_t * e);
lv_obj_t *ui_Switch4;
lv_obj_t *ui_Panel23;
lv_obj_t *ui_Label17;
void ui_event_Switch5( lv_event_t * e);
lv_obj_t *ui_Switch5;
lv_obj_t *ui_Panel24;
lv_obj_t *ui_Label18;
void ui_event_Switch6( lv_event_t * e);
lv_obj_t *ui_Switch6;
// CUSTOM VARIABLES


// SCREEN: ui_Screen3
void ui_Screen3_screen_init(void);
lv_obj_t *ui_Screen3;
lv_obj_t *ui_Panel13;
lv_obj_t *ui_Panel14;
lv_obj_t *ui_Label9;
void ui_event_Panel15( lv_event_t * e);
lv_obj_t *ui_Panel15;
lv_obj_t *ui_Label10;
void ui_event_ImgButton7( lv_event_t * e);
lv_obj_t *ui_ImgButton7;
void ui_event_Panel16( lv_event_t * e);
lv_obj_t *ui_Panel16;
lv_obj_t *ui_Label11;
void ui_event_ImgButton8( lv_event_t * e);
lv_obj_t *ui_ImgButton8;
lv_obj_t *ui_Panel17;
lv_obj_t *ui_Label12;
lv_obj_t *ui_ImgButton9;
lv_obj_t *ui_Panel18;
// CUSTOM VARIABLES

// EVENTS
lv_obj_t *ui____initial_actions0;

// IMAGES AND IMAGE SETS

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_Panel5( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);

if ( event_code == LV_EVENT_RELEASED) {
      _ui_screen_change( &ui_Screen2, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_Screen2_screen_init);
}
}

void ui_event_ImgButton3( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);

if ( event_code == LV_EVENT_RELEASED) {
      _ui_screen_change( &ui_Screen2, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_Screen2_screen_init);
}
}

void ui_event_Panel6( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);

if ( event_code == LV_EVENT_RELEASED) {
      _ui_screen_change( &ui_Screen3, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_Screen3_screen_init);
}
}

void ui_event_ImgButton4( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);

if ( event_code == LV_EVENT_RELEASED) {
      _ui_screen_change( &ui_Screen3, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_Screen3_screen_init);
}
}

void ui_event_Panel9( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);

if ( event_code == LV_EVENT_RELEASED) {
      _ui_screen_change( &ui_Screen1, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_Screen1_screen_init);
}
}

void ui_event_ImgButton1( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);

if ( event_code == LV_EVENT_RELEASED) {
      _ui_screen_change( &ui_Screen1, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_Screen1_screen_init);
}
}

void ui_event_Panel11( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);

if ( event_code == LV_EVENT_RELEASED) {
      _ui_screen_change( &ui_Screen3, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_Screen3_screen_init);
}
}

void ui_event_ImgButton6( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);

if ( event_code == LV_EVENT_RELEASED) {
      _ui_screen_change( &ui_Screen3, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_Screen3_screen_init);
}
}

void ui_event_Switch1( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);

if ( event_code == LV_EVENT_VALUE_CHANGED) {
      screen2relay1( e );
}
}

void ui_event_Switch2( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);

if ( event_code == LV_EVENT_VALUE_CHANGED) {
      screen2relay2( e );
}
}

void ui_event_Switch3( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);

if ( event_code == LV_EVENT_VALUE_CHANGED) {
      screen2relay3( e );
}
}

void ui_event_Switch4( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);

if ( event_code == LV_EVENT_VALUE_CHANGED) {
      screen2relay4( e );
}
}

void ui_event_Switch5( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);

if ( event_code == LV_EVENT_VALUE_CHANGED) {
      screen2relay5( e );
}
}

void ui_event_Switch6( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);

if ( event_code == LV_EVENT_VALUE_CHANGED) {
      screen2relay6( e );
}
}

void ui_event_Panel15( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);

if ( event_code == LV_EVENT_RELEASED) {
      _ui_screen_change( &ui_Screen1, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_Screen1_screen_init);
}
}

void ui_event_ImgButton7( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);

if ( event_code == LV_EVENT_RELEASED) {
      _ui_screen_change( &ui_Screen1, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_Screen1_screen_init);
}
}

void ui_event_Panel16( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);

if ( event_code == LV_EVENT_RELEASED) {
      _ui_screen_change( &ui_Screen2, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_Screen2_screen_init);
}
}

void ui_event_ImgButton8( lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);

if ( event_code == LV_EVENT_RELEASED) {
      _ui_screen_change( &ui_Screen2, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_Screen2_screen_init);
}
}

///////////////////// SCREENS ////////////////////

void ui_init( void )
{
lv_disp_t *dispp = lv_disp_get_default();
lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
lv_disp_set_theme(dispp, theme);
ui_Screen1_screen_init();
ui_Screen2_screen_init();
ui_Screen3_screen_init();
ui____initial_actions0 = lv_obj_create(NULL);
lv_disp_load_scr( ui_Screen1);
}
