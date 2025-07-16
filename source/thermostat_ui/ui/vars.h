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
    FLOW_GLOBAL_VARIABLE_TEMPERATURE_FMT = 0,
    FLOW_GLOBAL_VARIABLE_SETPOINT_FMT = 1,
    FLOW_GLOBAL_VARIABLE_ENABLE_REG = 2,
    FLOW_GLOBAL_VARIABLE_SETPOINT_MIN = 3,
    FLOW_GLOBAL_VARIABLE_SETPOINT_MAX = 4,
    FLOW_GLOBAL_VARIABLE_THRESHOLD = 5,
    FLOW_GLOBAL_VARIABLE_HUMIDITY_FMT = 6,
    FLOW_GLOBAL_VARIABLE_SETPOINT = 7,
    FLOW_GLOBAL_VARIABLE_OPEN_VALVE_STATE = 8,
    FLOW_GLOBAL_VARIABLE_CLOSE_VALVE_STATE = 9,
    FLOW_GLOBAL_VARIABLE_UI_RED_LED_OFF = 10,
    FLOW_GLOBAL_VARIABLE_UI_GREEN_LED_OFF = 11
};

// Native global variables

extern const char *get_var_temperature_fmt();
extern void set_var_temperature_fmt(const char *value);
extern const char *get_var_setpoint_fmt();
extern void set_var_setpoint_fmt(const char *value);
extern bool get_var_enable_reg();
extern void set_var_enable_reg(bool value);
extern float get_var_setpoint_min();
extern void set_var_setpoint_min(float value);
extern float get_var_setpoint_max();
extern void set_var_setpoint_max(float value);
extern float get_var_threshold();
extern void set_var_threshold(float value);
extern const char *get_var_humidity_fmt();
extern void set_var_humidity_fmt(const char *value);
extern float get_var_setpoint();
extern void set_var_setpoint(float value);
extern bool get_var_open_valve_state();
extern void set_var_open_valve_state(bool value);
extern bool get_var_close_valve_state();
extern void set_var_close_valve_state(bool value);
extern bool get_var_ui_red_led_off();
extern void set_var_ui_red_led_off(bool value);
extern bool get_var_ui_green_led_off();
extern void set_var_ui_green_led_off(bool value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/