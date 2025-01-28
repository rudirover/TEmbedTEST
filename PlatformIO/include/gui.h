#ifndef UI_H
#define UI_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <lvgl.h>
#include <RotaryEncoder.h>
#include <OneButton.h>
#include "ui.h"
#include "task.h"
#include "actions.h"

#define POWER_ON 46
#define PIN_ENCODE_A          2
#define PIN_ENCODE_B          1
#define PIN_ENCODE_BTN        0

#define SCREENWIDTH 170
#define SCREENHEIGHT 320
#define DISP_BUF_SIZE SCREENWIDTH*SCREENHEIGHT

enum guiState{
    NONE_STATE,
    INFOPAGE_STATE,
    TEMPPAGE_STATE,
    WIFIPAGE_STATE,
    WIFISSIDFOCUS_STATE,
    WIFIPASSFOCUS_STATE};

void guiTask(void *param);

void buttonClicked();
void buttonLongPressed();
void readEncoder(RotaryEncoder::Direction direction);
void setBackLightLevel(byte level);
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p );

#endif