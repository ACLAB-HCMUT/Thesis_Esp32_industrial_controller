#ifdef M5_CORE2
#include "M5_init.h"

void M5_init()
{
    auto cfg = M5.config();
    cfg.external_spk = true;
    M5.begin();
    M5.Lcd.fillScreen(BLACK);
    M5.Display.setTextSize(2.5);
    M5.Display.setColor(WHITE);
}
#endif