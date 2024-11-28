#include "globals.h"
#include "./ui/ui.h"

void setup()
{
  String title = "Hello ACLAB";

  Serial.begin(115200);
  Serial.println(title + " start");

  Serial.println("Initialize panel device");
  ESP_Panel *panel = new ESP_Panel();
  panel->init();
#if LVGL_PORT_AVOID_TEAR
  // When avoid tearing function is enabled, configure the RGB bus according to the LVGL configuration
  ESP_PanelBus_RGB *rgb_bus = static_cast<ESP_PanelBus_RGB *>(panel->getLcd()->getBus());
  rgb_bus->configRgbFrameBufferNumber(LVGL_PORT_DISP_BUFFER_NUM);
  rgb_bus->configRgbBounceBufferSize(LVGL_PORT_RGB_BOUNCE_BUFFER_SIZE);
#endif
  panel->begin();

  Serial.println("Initialize LVGL");
  lvgl_port_init(panel->getLcd(), panel->getTouch());

  Serial.println("Create UI");
  lvgl_port_lock(-1);
  lv_obj_t *label = lv_label_create(lv_scr_act());
  lv_label_set_text(label, title.c_str());
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
  lvgl_port_unlock();
  ui_init();
  Serial.println(title + " end");
}

void loop()
{
}
