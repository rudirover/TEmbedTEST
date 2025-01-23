#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;

void create_screen_info_page() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.info_page = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 170);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_led_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 120, 153);
            lv_obj_set_size(obj, 8, 8);
            lv_led_set_color(obj, lv_color_hex(0xff0000ff));
            lv_led_set_brightness(obj, 255);
        }
        {
            lv_obj_t *obj = lv_led_create(parent_obj);
            objects.obj1 = obj;
            lv_obj_set_pos(obj, 156, 153);
            lv_obj_set_size(obj, 8, 8);
            lv_led_set_color(obj, lv_color_hex(0xffc0c0c0));
            lv_led_set_brightness(obj, 255);
        }
        {
            lv_obj_t *obj = lv_led_create(parent_obj);
            objects.obj2 = obj;
            lv_obj_set_pos(obj, 196, 153);
            lv_obj_set_size(obj, 8, 8);
            lv_led_set_color(obj, lv_color_hex(0xffc0c0c0));
            lv_led_set_brightness(obj, 255);
        }
    }
}

void tick_screen_info_page() {
}

void create_screen_wifi_page() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.wifi_page = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 170);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_led_create(parent_obj);
            objects.obj3 = obj;
            lv_obj_set_pos(obj, 120, 153);
            lv_obj_set_size(obj, 8, 8);
            lv_led_set_color(obj, lv_color_hex(0xffc0c0c0));
            lv_led_set_brightness(obj, 255);
        }
        {
            lv_obj_t *obj = lv_led_create(parent_obj);
            objects.obj4 = obj;
            lv_obj_set_pos(obj, 156, 153);
            lv_obj_set_size(obj, 8, 8);
            lv_led_set_color(obj, lv_color_hex(0xff0000ff));
            lv_led_set_brightness(obj, 255);
        }
        {
            lv_obj_t *obj = lv_led_create(parent_obj);
            objects.obj5 = obj;
            lv_obj_set_pos(obj, 196, 153);
            lv_obj_set_size(obj, 8, 8);
            lv_led_set_color(obj, lv_color_hex(0xffc0c0c0));
            lv_led_set_brightness(obj, 255);
        }
    }
}

void tick_screen_wifi_page() {
}


void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_info_page();
    create_screen_wifi_page();
}

typedef void (*tick_screen_func_t)();

tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_info_page,
    tick_screen_wifi_page,
};

void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
