#include <string.h>
#include "screens.h"
#include "images.h"
#include "ui.h"

groups_t groups;
static bool groups_created = false;

objects_t objects;
//lv_obj_t *tick_value_change_obj;


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
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 120, 153);
            lv_obj_set_size(obj, 8, 8);
            lv_led_set_color(obj, lv_color_hex(0xffc0c0c0));
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
            lv_led_set_color(obj, lv_color_hex(0xff0000ff));
            lv_led_set_brightness(obj, 255);
        }
        {
            // wificonnectionLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.wificonnection_label = obj;
            lv_obj_set_pos(obj, 93, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "WIFI CONNECTION");
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // wifiSSIDLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.wifi_ssid_label = obj;
            lv_obj_set_pos(obj, 16, 49);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "WIFI SSID:");
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // wifiSSIDDropDown
            lv_obj_t *obj = lv_dropdown_create(parent_obj);
            objects.wifi_ssid_drop_down = obj;
            lv_obj_set_pos(obj, 108, 40);
            lv_obj_set_size(obj, 200, 24);
            lv_dropdown_set_options(obj, "");
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0xff0000ff), LV_PART_MAIN | LV_STATE_FOCUSED);
            lv_obj_set_style_outline_width(obj, 5, LV_PART_MAIN | LV_STATE_FOCUSED);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0xff0000ff), LV_PART_SELECTED | LV_STATE_FOCUSED);
            lv_obj_set_style_outline_width(obj, 5, LV_PART_SELECTED | LV_STATE_FOCUSED);
        }
        {
            // wifiPASSLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.wifi_pass_label = obj;
            lv_obj_set_pos(obj, 16, 92);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "WIFI PASS:");
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // wifiPASSText
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            objects.wifi_pass_text = obj;
            lv_obj_set_pos(obj, 109, 83);
            lv_obj_set_size(obj, 200, 24);
            lv_textarea_set_max_length(obj, 128);
            lv_textarea_set_text(obj, "PassWord");
            lv_textarea_set_placeholder_text(obj, "******************");
            lv_textarea_set_one_line(obj, true);
            lv_textarea_set_password_mode(obj, true); 
            lv_obj_clear_state(obj, LV_STATE_FOCUSED);                     
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_width(obj, 5, LV_PART_MAIN | LV_STATE_FOCUSED);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0xff0000ff), LV_PART_MAIN | LV_STATE_FOCUSED);
            lv_obj_set_style_outline_width(obj, 5, LV_PART_SELECTED | LV_STATE_FOCUSED);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0xff0000ff), LV_PART_SELECTED | LV_STATE_FOCUSED);
        }
        {
            // wifiPASSKeyb
            lv_obj_t *obj = lv_keyboard_create(parent_obj);
            objects.wifi_pass_keyb = obj;
            lv_obj_set_pos(obj, 0, 40);
            lv_obj_set_size(obj, 320, 129);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);            
        }
        {
            // wifiPASSInput
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            objects.wifi_pass_input = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 32);
            lv_textarea_set_max_length(obj, 128);
            lv_textarea_set_one_line(obj, true);
            lv_textarea_set_password_mode(obj, false);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_state(obj, LV_STATE_FOCUSED);            
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff0000ff), LV_PART_SELECTED | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff0000ff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff0000ff), LV_PART_CURSOR | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_spinner_create(parent_obj, 1000, 60);
            objects.wifi_spinner = obj;            
            lv_obj_set_pos(obj, 120, 45);
            lv_obj_set_size(obj, 80, 80);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
        }        
    }
    lv_keyboard_set_textarea(objects.wifi_pass_keyb, objects.wifi_pass_input);
}

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
            objects.obj3 = obj;
            lv_obj_set_pos(obj, 120, 153);
            lv_obj_set_size(obj, 8, 8);
            lv_led_set_color(obj, lv_color_hex(0xff0000ff));
            lv_led_set_brightness(obj, 255);
        }
        {
            lv_obj_t *obj = lv_led_create(parent_obj);
            objects.obj4 = obj;
            lv_obj_set_pos(obj, 156, 153);
            lv_obj_set_size(obj, 8, 8);
            lv_led_set_color(obj, lv_color_hex(0xffc0c0c0));
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
        {
            // infopageLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.infopage_label = obj;
            lv_obj_set_pos(obj, 86, 9);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "INFORMATION PAGE");
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
}

void create_screen_temp_page() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.temp_page = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 170);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_led_create(parent_obj);
            objects.obj6 = obj;
            lv_obj_set_pos(obj, 120, 153);
            lv_obj_set_size(obj, 8, 8);
            lv_led_set_color(obj, lv_color_hex(0xffc0c0c0));
            lv_led_set_brightness(obj, 255);
        }
        {
            lv_obj_t *obj = lv_led_create(parent_obj);
            objects.obj7 = obj;
            lv_obj_set_pos(obj, 156, 153);
            lv_obj_set_size(obj, 8, 8);
            lv_led_set_color(obj, lv_color_hex(0xff0000ff));
            lv_led_set_brightness(obj, 255);
        }
        {
            lv_obj_t *obj = lv_led_create(parent_obj);
            objects.obj8 = obj;
            lv_obj_set_pos(obj, 196, 153);
            lv_obj_set_size(obj, 8, 8);
            lv_led_set_color(obj, lv_color_hex(0xffc0c0c0));
            lv_led_set_brightness(obj, 255);
        }
        {
            // setpointTempArc
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.setpoint_temp_arc = obj;
            lv_obj_set_pos(obj, 32, 32);
            lv_obj_set_size(obj, 92, 92);
            lv_arc_set_range(obj, 5, 40);
            lv_arc_set_value(obj, 21);
            lv_arc_set_bg_end_angle(obj, 60);
            lv_obj_set_style_arc_width(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 8, LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            // setpointLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.setpoint_label = obj;
            lv_obj_set_pos(obj, 43, 124);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "SETPOINT");
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // setpointTempArc_1
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.setpoint_temp_arc_1 = obj;
            lv_obj_set_pos(obj, 200, 32);
            lv_obj_set_size(obj, 92, 92);
            lv_arc_set_range(obj, 5, 40);
            lv_arc_set_value(obj, 21);
            lv_arc_set_bg_end_angle(obj, 60);
            lv_obj_set_style_arc_width(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 8, LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            // actualLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.actual_label = obj;
            lv_obj_set_pos(obj, 218, 124);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "ACUTAL");
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // temperaturesLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.temperatures_label = obj;
            lv_obj_set_pos(obj, 102, 8);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "TEMPERATURES");
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // setpointTEXT
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.setpoint_text = obj;
            lv_obj_set_pos(obj, 43, 67);
            lv_obj_set_size(obj, 71, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
            lv_obj_set_style_text_color(obj, lv_color_hex(0xfffefefe), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // actualTEXT
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.actual_text = obj;
            lv_obj_set_pos(obj, 211, 67);
            lv_obj_set_size(obj, 71, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "");
            lv_obj_set_style_text_color(obj, lv_color_hex(0xfffefefe), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
}

void ui_create_groups() {
    if (!groups_created) {
        groups.wifiPageGroup = lv_group_create();
        groups_created = true;
    }
}

void create_screens() {
    ui_create_groups();
    
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_wifi_page();
    create_screen_info_page();
    create_screen_temp_page();
}

