#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations



// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_SETPOINT_TEMPERATURE = 0,
    FLOW_GLOBAL_VARIABLE_ACTUAL_TEMPERATURE = 1,
    FLOW_GLOBAL_VARIABLE_WIFI_SSID_SELECTED = 2,
    FLOW_GLOBAL_VARIABLE_WIFI_SSID_LIST = 3,
    FLOW_GLOBAL_VARIABLE_WIFI_PASS_INPUT = 4,
    FLOW_GLOBAL_VARIABLE_WIFI_PASS_INPUT_HIDDEN = 5
};

// Native global variables

extern const char *get_var_setpoint_temperature();
extern void set_var_setpoint_temperature(const char *value);
extern const char *get_var_actual_temperature();
extern void set_var_actual_temperature(const char *value);
extern int32_t get_var_wifi_ssid_selected();
extern void set_var_wifi_ssid_selected(int32_t value);
extern const char *get_var_wifi_ssid_list();
extern void set_var_wifi_ssid_list(const char *value);
extern const char *get_var_wifi_pass_input();
extern void set_var_wifi_pass_input(const char *value);
extern bool get_var_wifi_pass_input_hidden();
extern void set_var_wifi_pass_input_hidden(bool value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/