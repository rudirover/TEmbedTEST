#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *info_page;
    lv_obj_t *led_container;
    lv_obj_t *led1;
    lv_obj_t *led2;
    lv_obj_t *led3;
    lv_obj_t *led4;
    lv_obj_t *rest_container;
    lv_obj_t *info_page_label;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_INFO_PAGE = 1,
};

void create_screen_info_page();
void tick_screen_info_page();

void create_screens();
void tick_screen(int screen_index);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/