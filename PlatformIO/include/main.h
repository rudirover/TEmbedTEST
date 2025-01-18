#include <Arduino.h>
#include <TFT_eSPI.h>
#include <lvgl.h>

#define POWER_ON 46

void setBackLightLevel(byte level);
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p );
