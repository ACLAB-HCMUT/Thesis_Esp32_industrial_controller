idf_component_get_property(LVGL_DIR lvgl COMPONENT_DIR)

idf_component_register(
    SRC_DIRS ${DIRS} ${LVGL_EXAMPLES} "."
    INCLUDE_DIRS "." ${LVGL_EXAMPLES} ${DIRS}
    REQUIRES esp_lcd driver lvgl esp_timer mqtt esp_wifi nvs_flash json
)

target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")
