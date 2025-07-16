/* @file thermostat_handler.c
 * @brief "Thermostat" handler for EEZ/LVGL
 * @brief Handles the thermostat UI events
 */

#include "ui/actions.h"
#include "ui/vars.h"
#include <stdio.h>

// Forward declarations for simplified C++ bridge
extern float thermostat_get_setpoint();
extern int thermostat_set_setpoint(float value);
extern void thermostat_set_regulation_state(int enabled);
extern int thermostat_set_valve_state(int open);

// ========================================
// EEZ ACTIONS BRIDGE - UI Events to Thermostat C++
// ========================================
//
// This file contains the EEZ/LVGL event callbacks.
// It bridges the user interactions and the Thermostat C++ class.
// NO business logic here, only delegations to the class.

// Instance access now handled directly in bridge functions - no getInstance() calls needed

// ===== SETPOINT CONTROLS =====

void action_setpoint_up(lv_event_t * e) {
    float current_setpoint = thermostat_get_setpoint();
    float new_setpoint = current_setpoint + 0.1f;
    
    printf("[UI] Button UP : %.1f°C -> %.1f°C\n", current_setpoint, new_setpoint);
    
    if (!thermostat_set_setpoint(new_setpoint)) {
        printf("[UI] Setpoint UP refused by application\n");
    }
}

void action_setpoint_down(lv_event_t * e) {
    float current_setpoint = thermostat_get_setpoint();
    float new_setpoint = current_setpoint - 0.1f;
    
    printf("[UI] Button DOWN : %.1f°C -> %.1f°C\n", current_setpoint, new_setpoint);
    
    if (!thermostat_set_setpoint(new_setpoint)) {
        printf("[UI] Setpoint DOWN refused by application\n");
    }
}

void action_setpoint_update(lv_event_t * e) {
    float current_setpoint = thermostat_get_setpoint();
    
    printf("[UI] Slider setpoint modified : %.1f°C\n", current_setpoint);
    
    // Note : The setpoint has already been updated via set_var_setpoint() 
    // called by the EEZ event handler, so no need to do it here.
    // This action can be used for additional actions (logs, etc.)
}

// ===== REGULATION CONTROLS =====

void action_start_reg(lv_event_t * e) {
    printf("[UI] Regulation ACTIVATED\n");
    
    thermostat_set_regulation_state(1);
}

void action_stop_reg(lv_event_t * e) {
    printf("[UI] Regulation DEACTIVATED\n");
    
    thermostat_set_regulation_state(0);
}

// ===== VALVE CONTROLS =====

void action_open_valve_on(lv_event_t * e) {
    printf("[UI] Valve opening ACTIVATED\n");
    
    if (!thermostat_set_valve_state(1)) {
        printf("[UI] Error activating valve opening\n");
    }
}

void action_open_valve_off(lv_event_t * e) {
    printf("[UI] Valve opening DEACTIVATED\n");
    
    if (!thermostat_set_valve_state(0)) {
        printf("[UI] Error deactivating valve opening\n");
    }
}

void action_close_valve_on(lv_event_t * e) {
    printf("[UI] Valve closing ACTIVATED\n");
    
    if (!thermostat_set_valve_state(0)) {  // close = set valve to false
        printf("[UI] Error activating valve closing\n");
    }
}

void action_close_valve_off(lv_event_t * e) {
    printf("[UI] Valve closing DEACTIVATED\n");
    
    if (!thermostat_set_valve_state(1)) {  // !close = set valve to true
        printf("[UI] Error deactivating valve closing\n");
    }
}

// ===== SYSTEM INITIALIZATION =====
// Thermostat initialization is now handled in main.cpp via C++ constructor
// No additional initialization needed here