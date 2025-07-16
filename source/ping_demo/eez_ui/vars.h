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
    FLOW_GLOBAL_VARIABLE_PING_STATUS = 0,
    FLOW_GLOBAL_VARIABLE_PING_TIME = 1,
    FLOW_GLOBAL_VARIABLE_IS_IDLE = 2
};

// Native global variables

extern const char *get_var_ping_status();
extern void set_var_ping_status(const char *value);
extern int32_t get_var_ping_time();
extern void set_var_ping_time(int32_t value);
extern bool get_var_is_idle();
extern void set_var_is_idle(bool value);

// vars.h - Declarations for formatted variables
extern const char *get_var_ping_status_formatted();
extern void set_var_ping_status_formatted(const char *value);
extern const char *get_var_ping_time_formatted();
extern void set_var_ping_time_formatted(const char *value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/