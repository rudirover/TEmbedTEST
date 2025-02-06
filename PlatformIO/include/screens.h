#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _groups_t {
    lv_group_t *wifiPageGroup;
} groups_t;

extern groups_t groups;

void ui_create_groups();

typedef struct _objects_t {
    lv_obj_t *wifi_page;
    lv_obj_t *info_page;
    lv_obj_t *temp_page;
    lv_obj_t *wifi_ssid_drop_down;
    lv_obj_t *wifi_pass_text;
    lv_obj_t *wifi_pass_keyb;
    lv_obj_t *wifi_pass_input;
    lv_obj_t *wifi_spinner;    
    lv_obj_t *obj0;
    lv_obj_t *obj1;
    lv_obj_t *obj2;
    lv_obj_t *wificonnection_label;
    lv_obj_t *wifi_ssid_label;
    lv_obj_t *wifi_pass_label;
    lv_obj_t *obj3;
    lv_obj_t *obj4;
    lv_obj_t *obj5;
    lv_obj_t *infopage_label;
    lv_obj_t *obj6;
    lv_obj_t *obj7;
    lv_obj_t *obj8;
    lv_obj_t *setpoint_temp_arc;
    lv_obj_t *setpoint_label;
    lv_obj_t *setpoint_temp_arc_1;
    lv_obj_t *actual_label;
    lv_obj_t *temperatures_label;
    lv_obj_t *setpoint_text;
    lv_obj_t *actual_text;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_WIFI_PAGE = 1,
    SCREEN_ID_INFO_PAGE = 2,
    SCREEN_ID_TEMP_PAGE = 3,
};

void create_screen_wifi_page();
void create_screen_info_page();
void create_screen_temp_page();
void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/