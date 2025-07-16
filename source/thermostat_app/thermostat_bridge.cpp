/* @file thermostat_bridge.cpp
 * @brief "Thermostat" class bridge for C interface
 * @brief Provides a C interface to the Thermostat class
 */

#include "Thermostat.hpp"

// Forward declaration from main.cpp
extern "C" {
    Thermostat* getThermostatInstance(void);
}

// C bridge functions - simplified without instance parameter
extern "C" {

// Internal helper to get instance
static Thermostat* getInstance() {
    return getThermostatInstance();
}

// Simplified wrappers - no instance parameter needed
float thermostat_get_temperature() {
    auto* instance = getInstance();
    return instance ? instance->getTemperature() : 0.0f;
}

int thermostat_is_temperature_valid() {
    auto* instance = getInstance();
    return instance ? (instance->isTemperatureValid() ? 1 : 0) : 0;
}

float thermostat_get_humidity() {
    auto* instance = getInstance();
    return instance ? instance->getHumidity() : 0.0f;
}

int thermostat_is_humidity_valid() {
    auto* instance = getInstance();
    return instance ? (instance->isHumidityValid() ? 1 : 0) : 0;
}

float thermostat_get_setpoint() {
    auto* instance = getInstance();
    return instance ? instance->getSetpoint() : 22.0f;
}

int thermostat_set_setpoint(float value) {
    auto* instance = getInstance();
    return instance ? (instance->setSetpoint(value) ? 1 : 0) : 0;
}

int thermostat_get_regulation_state() {
    auto* instance = getInstance();
    return instance ? (instance->getRegulationState() ? 1 : 0) : 0;
}

void thermostat_set_regulation_state(int enabled) {
    auto* instance = getInstance();
    if (instance) {
        instance->setRegulationState(enabled != 0);
    }
}

int thermostat_get_valve_state() {
    auto* instance = getInstance();
    return instance ? (instance->getValveState() ? 1 : 0) : 0;  // 1 = open, 0 = close
}

int thermostat_set_valve_state(int open) {
    auto* instance = getInstance();
    return instance ? (instance->setValveState(open != 0) ? 1 : 0) : 0;
}

int thermostat_get_red_led_off() {
    auto* instance = getInstance();
    return instance ? (instance->getRedLedOff() ? 1 : 0) : 1;
}

int thermostat_get_green_led_off() {
    auto* instance = getInstance();
    return instance ? (instance->getGreenLedOff() ? 1 : 0) : 1;
}

void thermostat_set_red_led_off(int off) {
    auto* instance = getInstance();
    if (instance) {
        instance->setRedLedOff(off != 0);
    }
}

void thermostat_set_green_led_off(int off) {
    auto* instance = getInstance();
    if (instance) {
        instance->setGreenLedOff(off != 0);
    }
}

} // extern "C"