// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 8.3.11
// Project name: ui

#include "ui.h"

void ui_Screen2_screen_init(void)
{
ui_Screen2 = lv_obj_create(NULL);
lv_obj_clear_flag( ui_Screen2, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_flex_flow(ui_Screen2,LV_FLEX_FLOW_COLUMN_WRAP);
lv_obj_set_flex_align(ui_Screen2, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

ui_Panel7 = lv_obj_create(ui_Screen2);
lv_obj_set_width( ui_Panel7, lv_pct(18));
lv_obj_set_height( ui_Panel7, lv_pct(100));
lv_obj_set_x( ui_Panel7, -294 );
lv_obj_set_y( ui_Panel7, 13 );
lv_obj_set_align( ui_Panel7, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_Panel7,LV_FLEX_FLOW_ROW_WRAP);
lv_obj_set_flex_align(ui_Panel7, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
lv_obj_clear_flag( ui_Panel7, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_Panel7, lv_color_hex(0x81C27E), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Panel7, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Panel8 = lv_obj_create(ui_Panel7);
lv_obj_set_width( ui_Panel8, lv_pct(120));
lv_obj_set_height( ui_Panel8, lv_pct(10));
lv_obj_set_x( ui_Panel8, -412 );
lv_obj_set_y( ui_Panel8, -182 );
lv_obj_set_align( ui_Panel8, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_Panel8, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Label5 = lv_label_create(ui_Panel8);
lv_obj_set_width( ui_Label5, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label5, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label5, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label5,"MENU");
lv_obj_set_style_text_font(ui_Label5, &lv_font_montserrat_16, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Panel9 = lv_obj_create(ui_Panel7);
lv_obj_set_width( ui_Panel9, lv_pct(120));
lv_obj_set_height( ui_Panel9, lv_pct(30));
lv_obj_set_x( ui_Panel9, -337 );
lv_obj_set_y( ui_Panel9, -75 );
lv_obj_set_align( ui_Panel9, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_Panel9,LV_FLEX_FLOW_ROW_WRAP);
lv_obj_set_flex_align(ui_Panel9, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
lv_obj_clear_flag( ui_Panel9, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Label6 = lv_label_create(ui_Panel9);
lv_obj_set_width( ui_Label6, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label6, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Label6, -328 );
lv_obj_set_y( ui_Label6, -135 );
lv_obj_set_align( ui_Label6, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label6,"HOME");

ui_ImgButton1 = lv_imgbtn_create(ui_Panel9);
lv_imgbtn_set_src(ui_ImgButton1, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_home_png, NULL);
lv_obj_set_height( ui_ImgButton1, 64);
lv_obj_set_width( ui_ImgButton1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_align( ui_ImgButton1, LV_ALIGN_CENTER );

ui_Panel10 = lv_obj_create(ui_Panel7);
lv_obj_set_width( ui_Panel10, lv_pct(120));
lv_obj_set_height( ui_Panel10, lv_pct(30));
lv_obj_set_align( ui_Panel10, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_Panel10,LV_FLEX_FLOW_ROW_WRAP);
lv_obj_set_flex_align(ui_Panel10, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
lv_obj_clear_flag( ui_Panel10, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Label7 = lv_label_create(ui_Panel10);
lv_obj_set_width( ui_Label7, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label7, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label7, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_Label7,"RELAY");

ui_ImgButton5 = lv_imgbtn_create(ui_Panel10);
lv_imgbtn_set_src(ui_ImgButton5, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_toggle_png, NULL);
lv_obj_set_height( ui_ImgButton5, 64);
lv_obj_set_width( ui_ImgButton5, LV_SIZE_CONTENT);  /// 1
lv_obj_set_align( ui_ImgButton5, LV_ALIGN_CENTER );

ui_Panel11 = lv_obj_create(ui_Panel7);
lv_obj_set_width( ui_Panel11, lv_pct(120));
lv_obj_set_height( ui_Panel11, lv_pct(30));
lv_obj_set_align( ui_Panel11, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_Panel11,LV_FLEX_FLOW_ROW_WRAP);
lv_obj_set_flex_align(ui_Panel11, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
lv_obj_clear_flag( ui_Panel11, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Label8 = lv_label_create(ui_Panel11);
lv_obj_set_width( ui_Label8, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label8, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label8, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label8,"SCHEDULE");

ui_ImgButton6 = lv_imgbtn_create(ui_Panel11);
lv_imgbtn_set_src(ui_ImgButton6, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_schedule_png, NULL);
lv_obj_set_height( ui_ImgButton6, lv_pct(80));
lv_obj_set_width( ui_ImgButton6, LV_SIZE_CONTENT);  /// 1
lv_obj_set_align( ui_ImgButton6, LV_ALIGN_CENTER );

ui_Panel12 = lv_obj_create(ui_Screen2);
lv_obj_set_width( ui_Panel12, lv_pct(80));
lv_obj_set_height( ui_Panel12, lv_pct(100));
lv_obj_set_x( ui_Panel12, -219 );
lv_obj_set_y( ui_Panel12, -75 );
lv_obj_set_align( ui_Panel12, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_Panel12,LV_FLEX_FLOW_ROW_WRAP);
lv_obj_set_flex_align(ui_Panel12, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
lv_obj_clear_flag( ui_Panel12, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_Panel12, lv_color_hex(0x81C27E), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Panel12, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_row(ui_Panel12, 20, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_column(ui_Panel12, 20, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Panel19 = lv_obj_create(ui_Panel12);
lv_obj_set_width( ui_Panel19, lv_pct(30));
lv_obj_set_height( ui_Panel19, lv_pct(30));
lv_obj_set_align( ui_Panel19, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_Panel19,LV_FLEX_FLOW_COLUMN_WRAP);
lv_obj_set_flex_align(ui_Panel19, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
lv_obj_clear_flag( ui_Panel19, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Label13 = lv_label_create(ui_Panel19);
lv_obj_set_width( ui_Label13, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label13, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label13, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label13,"RELAY 1\n");

ui_Switch1 = lv_switch_create(ui_Panel19);
lv_obj_set_width( ui_Switch1, lv_pct(60));
lv_obj_set_height( ui_Switch1, lv_pct(50));
lv_obj_set_align( ui_Switch1, LV_ALIGN_CENTER );


ui_Panel20 = lv_obj_create(ui_Panel12);
lv_obj_set_width( ui_Panel20, lv_pct(30));
lv_obj_set_height( ui_Panel20, lv_pct(30));
lv_obj_set_align( ui_Panel20, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_Panel20,LV_FLEX_FLOW_COLUMN_WRAP);
lv_obj_set_flex_align(ui_Panel20, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
lv_obj_clear_flag( ui_Panel20, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Label14 = lv_label_create(ui_Panel20);
lv_obj_set_width( ui_Label14, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label14, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label14, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label14,"RELAY 2\n");

ui_Switch2 = lv_switch_create(ui_Panel20);
lv_obj_set_width( ui_Switch2, lv_pct(60));
lv_obj_set_height( ui_Switch2, lv_pct(50));
lv_obj_set_align( ui_Switch2, LV_ALIGN_CENTER );


ui_Panel21 = lv_obj_create(ui_Panel12);
lv_obj_set_width( ui_Panel21, lv_pct(30));
lv_obj_set_height( ui_Panel21, lv_pct(30));
lv_obj_set_align( ui_Panel21, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_Panel21,LV_FLEX_FLOW_COLUMN_WRAP);
lv_obj_set_flex_align(ui_Panel21, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
lv_obj_clear_flag( ui_Panel21, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Label15 = lv_label_create(ui_Panel21);
lv_obj_set_width( ui_Label15, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label15, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label15, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label15,"RELAY 3\n");

ui_Switch3 = lv_switch_create(ui_Panel21);
lv_obj_set_width( ui_Switch3, lv_pct(60));
lv_obj_set_height( ui_Switch3, lv_pct(50));
lv_obj_set_align( ui_Switch3, LV_ALIGN_CENTER );


ui_Panel22 = lv_obj_create(ui_Panel12);
lv_obj_set_width( ui_Panel22, lv_pct(30));
lv_obj_set_height( ui_Panel22, lv_pct(30));
lv_obj_set_align( ui_Panel22, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_Panel22,LV_FLEX_FLOW_COLUMN_WRAP);
lv_obj_set_flex_align(ui_Panel22, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
lv_obj_clear_flag( ui_Panel22, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Label16 = lv_label_create(ui_Panel22);
lv_obj_set_width( ui_Label16, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label16, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label16, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label16,"RELAY 4\n");

ui_Switch4 = lv_switch_create(ui_Panel22);
lv_obj_set_width( ui_Switch4, lv_pct(60));
lv_obj_set_height( ui_Switch4, lv_pct(50));
lv_obj_set_align( ui_Switch4, LV_ALIGN_CENTER );


ui_Panel23 = lv_obj_create(ui_Panel12);
lv_obj_set_width( ui_Panel23, lv_pct(30));
lv_obj_set_height( ui_Panel23, lv_pct(30));
lv_obj_set_align( ui_Panel23, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_Panel23,LV_FLEX_FLOW_COLUMN_WRAP);
lv_obj_set_flex_align(ui_Panel23, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
lv_obj_clear_flag( ui_Panel23, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Label17 = lv_label_create(ui_Panel23);
lv_obj_set_width( ui_Label17, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label17, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label17, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label17,"RELAY 5\n");

ui_Switch5 = lv_switch_create(ui_Panel23);
lv_obj_set_width( ui_Switch5, lv_pct(60));
lv_obj_set_height( ui_Switch5, lv_pct(50));
lv_obj_set_align( ui_Switch5, LV_ALIGN_CENTER );


ui_Panel24 = lv_obj_create(ui_Panel12);
lv_obj_set_width( ui_Panel24, lv_pct(30));
lv_obj_set_height( ui_Panel24, lv_pct(30));
lv_obj_set_align( ui_Panel24, LV_ALIGN_CENTER );
lv_obj_set_flex_flow(ui_Panel24,LV_FLEX_FLOW_COLUMN_WRAP);
lv_obj_set_flex_align(ui_Panel24, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
lv_obj_clear_flag( ui_Panel24, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_Label18 = lv_label_create(ui_Panel24);
lv_obj_set_width( ui_Label18, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Label18, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_Label18, LV_ALIGN_CENTER );
lv_label_set_text(ui_Label18,"RELAY 6\n");

ui_Switch6 = lv_switch_create(ui_Panel24);
lv_obj_set_width( ui_Switch6, lv_pct(60));
lv_obj_set_height( ui_Switch6, lv_pct(50));
lv_obj_set_align( ui_Switch6, LV_ALIGN_CENTER );


lv_obj_add_event_cb(ui_ImgButton1, ui_event_ImgButton1, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_Panel9, ui_event_Panel9, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_ImgButton6, ui_event_ImgButton6, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_Panel11, ui_event_Panel11, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_Switch1, ui_event_Switch1, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_Switch2, ui_event_Switch2, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_Switch3, ui_event_Switch3, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_Switch4, ui_event_Switch4, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_Switch5, ui_event_Switch5, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_Switch6, ui_event_Switch6, LV_EVENT_ALL, NULL);

}