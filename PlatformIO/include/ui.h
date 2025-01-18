#ifndef UI_H
#define UI_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <lvgl.h>

#define POWER_ON 46

#define SCREENWIDTH 170;
#define SCREENHEIGHT 320;

extern const uint16_t screenWidth;
extern const uint16_t screenHeight;
extern lv_disp_draw_buf_t draw_buf;
extern lv_color_t buf[];  
extern TFT_eSPI Tft; // TFT instance 

void uiSetup();
void uiLoop();
void setBackLightLevel(byte level);
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p );

#endif