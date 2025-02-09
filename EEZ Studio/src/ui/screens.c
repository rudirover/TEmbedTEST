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
            // ledContainer
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.led_container = obj;
            lv_obj_set_pos(obj, 300, 0);
            lv_obj_set_size(obj, 20, 170);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // led1
                    lv_obj_t *obj = lv_led_create(parent_obj);
                    objects.led1 = obj;
                    lv_obj_set_pos(obj, 6, 36);
                    lv_obj_set_size(obj, 8, 8);
                    lv_led_set_color(obj, lv_color_hex(0xff0000ff));
                    lv_led_set_brightness(obj, 255);
                }
                {
                    // led2
                    lv_obj_t *obj = lv_led_create(parent_obj);
                    objects.led2 = obj;
                    lv_obj_set_pos(obj, 6, 66);
                    lv_obj_set_size(obj, 8, 8);
                    lv_led_set_color(obj, lv_color_hex(0xffc0c0c0));
                    lv_led_set_brightness(obj, 255);
                }
                {
                    // led3
                    lv_obj_t *obj = lv_led_create(parent_obj);
                    objects.led3 = obj;
                    lv_obj_set_pos(obj, 6, 96);
                    lv_obj_set_size(obj, 8, 8);
                    lv_led_set_color(obj, lv_color_hex(0xffc0c0c0));
                    lv_led_set_brightness(obj, 255);
                }
                {
                    // led4
                    lv_obj_t *obj = lv_led_create(parent_obj);
                    objects.led4 = obj;
                    lv_obj_set_pos(obj, 6, 126);
                    lv_obj_set_size(obj, 8, 8);
                    lv_led_set_color(obj, lv_color_hex(0xffc0c0c0));
                    lv_led_set_brightness(obj, 255);
                }
            }
        }
        {
            // restContainer
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.rest_container = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 300, 170);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xffe0e0e0), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // infoPageLabel
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.info_page_label = obj;
                    lv_obj_set_pos(obj, 58, 8);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_label_set_text(obj, "INFORMATON PAGE");
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
    }
}

void tick_screen_info_page() {
}


void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_info_page();
}

typedef void (*tick_screen_func_t)();

tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_info_page,
};

void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
