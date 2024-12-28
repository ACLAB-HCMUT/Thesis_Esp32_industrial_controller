SET(SOURCES ui_Screen1.c
    ui_Screen2.c
    ui_Screen3.c
    ui.c
    ui_comp_hook.c
    ui_helpers.c
    ui_events.cpp
    ui_img_home_png.c
    ui_img_toggle_png.c
    ui_img_schedule_png.c
    ui_img_gauge_png.c)

add_library(ui ${SOURCES})
