#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_setpoint_up(lv_event_t * e);
extern void action_setpoint_down(lv_event_t * e);
extern void action_setpoint_update(lv_event_t * e);
extern void action_start_reg(lv_event_t * e);
extern void action_stop_reg(lv_event_t * e);
extern void action_open_valve_on(lv_event_t * e);
extern void action_open_valve_off(lv_event_t * e);
extern void action_close_valve_on(lv_event_t * e);
extern void action_close_valve_off(lv_event_t * e);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/