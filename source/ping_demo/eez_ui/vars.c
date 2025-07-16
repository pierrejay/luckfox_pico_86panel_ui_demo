// vars.c - version corrigée
#include "vars.h"
#include <string.h>
#include <stdlib.h>

// Variables globales statiques (UNE SEULE FOIS !)
static char ping_status_value[64] = "Ready";
static int32_t ping_time_value = 0;
static bool is_idle_value = true;
static char ping_status_formatted_value[64] = "Status: Ready";  // ← Une seule fois
static char ping_time_formatted_value[64] = "Last: 0 ms";      // ← Une seule fois

// Getters originaux
const char *get_var_ping_status() {
    return ping_status_value;
}

int32_t get_var_ping_time() {
    return ping_time_value;
}

bool get_var_is_idle() {
    return is_idle_value;
}

// Setters originaux  
void set_var_ping_status(const char *value) {
    if (value != NULL) {
        strncpy(ping_status_value, value, sizeof(ping_status_value) - 1);
        ping_status_value[sizeof(ping_status_value) - 1] = '\0';
    }
}

void set_var_ping_time(int32_t value) {
    ping_time_value = value;
}

void set_var_is_idle(bool value) {
    is_idle_value = value;
}

// Getters/Setters formatés (NOUVEAUX)
const char *get_var_ping_status_formatted() {
    return ping_status_formatted_value;
}

const char *get_var_ping_time_formatted() {
    return ping_time_formatted_value;
}

void set_var_ping_status_formatted(const char *value) {
    if (value != NULL) {
        strncpy(ping_status_formatted_value, value, sizeof(ping_status_formatted_value) - 1);
        ping_status_formatted_value[sizeof(ping_status_formatted_value) - 1] = '\0';
    }
}

void set_var_ping_time_formatted(const char *value) {
    if (value != NULL) {
        strncpy(ping_time_formatted_value, value, sizeof(ping_time_formatted_value) - 1);
        ping_time_formatted_value[sizeof(ping_time_formatted_value) - 1] = '\0';
    }
}