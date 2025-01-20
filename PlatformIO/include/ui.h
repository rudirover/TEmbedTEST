#ifndef UI_H
#define UI_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <lvgl.h>
#include <RotaryEncoder.h>
#include <OneButton.h>

#define POWER_ON 46
#define PIN_ENCODE_A          2
#define PIN_ENCODE_B          1
#define PIN_ENCODE_BTN        0

#define SCREENWIDTH 170;
#define SCREENHEIGHT 320;

extern const uint16_t screenWidth;
extern const uint16_t screenHeight;
extern lv_disp_draw_buf_t draw_buf;
extern lv_color_t buf[];  
extern lv_disp_drv_t disp_drv;
extern lv_indev_drv_t indev_drv;
extern lv_indev_t *indev;
extern lv_group_t *group;

extern TFT_eSPI Tft; // TFT instance 
extern RotaryEncoder encoder;
extern OneButton button;

void uiSetup();
void uiLoop();

void readEncoder(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
void temperatureBtnClicked(lv_event_t *event);
void setBackLightLevel(byte level);
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p );

#endif