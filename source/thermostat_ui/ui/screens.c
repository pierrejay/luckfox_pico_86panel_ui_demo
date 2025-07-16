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
uint32_t active_theme_index = 0;

static void event_handler_cb_main_obj5(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_arc_get_value(ta);
            set_var_setpoint(value);
        }
    }
}

static void event_handler_checked_cb_main_obj0(lv_event_t *e) {
    lv_obj_t *ta = lv_event_get_target(e);
    if (lv_obj_has_state(ta, LV_STATE_CHECKED)) {
        action_start_reg(e);
    }
}

static void event_handler_unchecked_cb_main_obj0(lv_event_t *e) {
    lv_obj_t *ta = lv_event_get_target(e);
    if (!lv_obj_has_state(ta, LV_STATE_CHECKED)) {
        action_stop_reg(e);
    }
}

static void event_handler_cb_main_obj0(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            set_var_enable_reg(value);
        }
    }
}

static void event_handler_checked_cb_main_obj1(lv_event_t *e) {
    lv_obj_t *ta = lv_event_get_target(e);
    if (lv_obj_has_state(ta, LV_STATE_CHECKED)) {
        action_open_valve_on(e);
    }
}

static void event_handler_unchecked_cb_main_obj1(lv_event_t *e) {
    lv_obj_t *ta = lv_event_get_target(e);
    if (!lv_obj_has_state(ta, LV_STATE_CHECKED)) {
        action_open_valve_off(e);
    }
}

static void event_handler_cb_main_obj1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            set_var_open_valve_state(value);
        }
    }
}

static void event_handler_checked_cb_main_obj2(lv_event_t *e) {
    lv_obj_t *ta = lv_event_get_target(e);
    if (lv_obj_has_state(ta, LV_STATE_CHECKED)) {
        action_close_valve_on(e);
    }
}

static void event_handler_unchecked_cb_main_obj2(lv_event_t *e) {
    lv_obj_t *ta = lv_event_get_target(e);
    if (!lv_obj_has_state(ta, LV_STATE_CHECKED)) {
        action_close_valve_off(e);
    }
}

static void event_handler_cb_main_obj2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            set_var_close_valve_state(value);
        }
    }
}

static void event_handler_cb_main_obj3(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
}

static void event_handler_cb_main_obj4(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
}

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 720, 720);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 225, 13);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "LVGL Thermostat POC");
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 247, 427);
            lv_obj_set_size(obj, 147, 141);
            lv_obj_add_event_cb(obj, action_setpoint_up, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_40, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "+");
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            lv_obj_set_pos(obj, 42, 427);
            lv_obj_set_size(obj, 147, 141);
            lv_obj_add_event_cb(obj, action_setpoint_down, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_40, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "-");
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 446, 131);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Temperature");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj6 = obj;
            lv_obj_set_pos(obj, 484, 173);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_40, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.obj5 = obj;
            lv_obj_set_pos(obj, 63, 100);
            lv_obj_set_size(obj, 360, 296);
            lv_arc_set_bg_end_angle(obj, 40);
            lv_obj_add_event_cb(obj, action_setpoint_update, LV_EVENT_RELEASED, (void *)0);
            lv_obj_add_event_cb(obj, event_handler_cb_main_obj5, LV_EVENT_ALL, 0);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 155, 202);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 180, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Setpoint");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj7 = obj;
            lv_obj_set_pos(obj, 155, 243);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_40, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 180, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_switch_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 500, 484);
            lv_obj_set_size(obj, 145, 71);
            lv_obj_add_event_cb(obj, event_handler_checked_cb_main_obj0, LV_EVENT_VALUE_CHANGED, (void *)0);
            lv_obj_add_event_cb(obj, event_handler_unchecked_cb_main_obj0, LV_EVENT_VALUE_CHANGED, (void *)0);
            lv_obj_add_event_cb(obj, event_handler_cb_main_obj0, LV_EVENT_ALL, 0);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 494, 432);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Regulation");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 475, 255);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Humidity");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.obj8 = obj;
            lv_obj_set_pos(obj, 461, 297);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_40, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_switch_create(parent_obj);
            objects.obj1 = obj;
            lv_obj_set_pos(obj, 208, 632);
            lv_obj_set_size(obj, 107, 54);
            lv_obj_add_event_cb(obj, event_handler_checked_cb_main_obj1, LV_EVENT_VALUE_CHANGED, (void *)0);
            lv_obj_add_event_cb(obj, event_handler_unchecked_cb_main_obj1, LV_EVENT_VALUE_CHANGED, (void *)0);
            lv_obj_add_event_cb(obj, event_handler_cb_main_obj1, LV_EVENT_ALL, 0);
        }
        {
            lv_obj_t *obj = lv_switch_create(parent_obj);
            objects.obj2 = obj;
            lv_obj_set_pos(obj, 547, 633);
            lv_obj_set_size(obj, 107, 54);
            lv_obj_add_event_cb(obj, event_handler_checked_cb_main_obj2, LV_EVENT_VALUE_CHANGED, (void *)0);
            lv_obj_add_event_cb(obj, event_handler_unchecked_cb_main_obj2, LV_EVENT_VALUE_CHANGED, (void *)0);
            lv_obj_add_event_cb(obj, event_handler_cb_main_obj2, LV_EVENT_ALL, 0);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 29, 644);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Open valve");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 374, 645);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_28, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Close valve");
        }
        {
            lv_obj_t *obj = lv_led_create(parent_obj);
            objects.obj3 = obj;
            lv_obj_set_pos(obj, 654, 27);
            lv_obj_set_size(obj, 32, 32);
            lv_led_set_color(obj, lv_color_hex(0xffff0000));
            lv_led_set_brightness(obj, 255);
            lv_obj_add_event_cb(obj, event_handler_cb_main_obj3, LV_EVENT_ALL, 0);
        }
        {
            lv_obj_t *obj = lv_led_create(parent_obj);
            objects.obj4 = obj;
            lv_obj_set_pos(obj, 654, 27);
            lv_obj_set_size(obj, 32, 32);
            lv_led_set_color(obj, lv_color_hex(0xff00e336));
            lv_led_set_brightness(obj, 255);
            lv_obj_add_event_cb(obj, event_handler_cb_main_obj4, LV_EVENT_ALL, 0);
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
    {
        const char *new_val = get_var_temperature_fmt();
        const char *cur_val = lv_label_get_text(objects.obj6);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj6;
            lv_label_set_text(objects.obj6, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_setpoint_min();
        int32_t cur_val = lv_arc_get_min_value(objects.obj5);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj5;
            int16_t min = new_val;
            int16_t max = lv_arc_get_max_value(objects.obj5);
            if (min < max) {
                lv_arc_set_range(objects.obj5, min, max);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_setpoint_max();
        int32_t cur_val = lv_arc_get_max_value(objects.obj5);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj5;
            int16_t min = lv_arc_get_min_value(objects.obj5);
            int16_t max = new_val;
            if (min < max) {
                lv_arc_set_range(objects.obj5, min, max);
            }
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_setpoint();
        int32_t cur_val = lv_arc_get_value(objects.obj5);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj5;
            lv_arc_set_value(objects.obj5, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_setpoint_fmt();
        const char *cur_val = lv_label_get_text(objects.obj7);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj7;
            lv_label_set_text(objects.obj7, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_enable_reg();
        bool cur_val = lv_obj_has_state(objects.obj0, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj0;
            if (new_val) lv_obj_add_state(objects.obj0, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj0, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_humidity_fmt();
        const char *cur_val = lv_label_get_text(objects.obj8);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.obj8;
            lv_label_set_text(objects.obj8, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_open_valve_state();
        bool cur_val = lv_obj_has_state(objects.obj1, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj1;
            if (new_val) lv_obj_add_state(objects.obj1, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj1, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_close_valve_state();
        bool cur_val = lv_obj_has_state(objects.obj2, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj2;
            if (new_val) lv_obj_add_state(objects.obj2, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj2, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool off = get_var_ui_red_led_off();
        bool cur_hidden = lv_obj_has_flag(objects.obj3, LV_OBJ_FLAG_HIDDEN);
        if (off != cur_hidden) {
            tick_value_change_obj = objects.obj3;
            if (off) lv_obj_add_flag(objects.obj3, LV_OBJ_FLAG_HIDDEN);
            else     lv_obj_clear_flag(objects.obj3, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool off = get_var_ui_green_led_off();
        bool cur_hidden = lv_obj_has_flag(objects.obj4, LV_OBJ_FLAG_HIDDEN);
        if (off != cur_hidden) {
            tick_value_change_obj = objects.obj4;
            if (off) lv_obj_add_flag(objects.obj4, LV_OBJ_FLAG_HIDDEN);
            else     lv_obj_clear_flag(objects.obj4, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
}



typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
}
