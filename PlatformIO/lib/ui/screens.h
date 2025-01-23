#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *info_page;
    lv_obj_t *wifi_page;
    lv_obj_t *obj0;
    lv_obj_t *obj1;
    lv_obj_t *obj2;
    lv_obj_t *obj3;
    lv_obj_t *obj4;
    lv_obj_t *obj5;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_INFO_PAGE = 1,
    SCREEN_ID_WIFI_PAGE = 2,
};

void create_screen_info_page();
void tick_screen_info_page();

void create_screen_wifi_page();
void tick_screen_wifi_page();

void create_screens();
void tick_screen(int screen_index);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/