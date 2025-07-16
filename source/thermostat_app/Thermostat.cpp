/* @file Thermostat.cpp
 * @brief "Thermostat" main class implementation
 * @brief Implements the thermostat system
 */

#include "Thermostat.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <errno.h>

extern "C" {
    #include <modbus/modbus.h>
    #include <lvgl/lvgl.h>
}

// Forward declarations for UI bridge
extern "C" {
    void set_var_ui_red_led_off(bool off);
    void set_var_ui_green_led_off(bool off);
}

Thermostat::Thermostat() {
    std::cout << "[Thermostat] Constructor called\n";
}

Thermostat::~Thermostat() {
    std::cout << "[Thermostat] Destructor called\n";
    end();
}

/* @brief Initialize the thermostat system
 */
void Thermostat::begin() {
    std::cout << "[Thermostat] Starting thermostat system...\n";
    
    if (running) {
        std::cout << "[Thermostat] Already running, ignoring begin()\n";
        return;
    }
    
    // Initialize Modbus
    if (!initializeModbus()) {
        throw std::runtime_error("Failed to initialize Modbus connection");
    }
    
    // Start sensor task
    running = true;
    sensorThread = std::make_unique<std::thread>(&Thermostat::sensorTask, this);
    
    std::cout << "[Thermostat] ✓ System started successfully\n";
}

/* @brief Stop the thermostat system & cleanup resources
 */
void Thermostat::end() {
    if (!running) return;
    
    std::cout << "[Thermostat] Stopping thermostat system...\n";
    
    // Stop regulation first
    setRegulationState(false);
    
    // Stop sensor task
    running = false;
    if (sensorThread && sensorThread->joinable()) {
        sensorThread->join();
    }
    sensorThread.reset();
    
    // Cleanup Modbus
    cleanupModbus();
    
    std::cout << "[Thermostat] ✓ System stopped\n";
}

/* @brief Get the current setpoint
 * @return The current setpoint in °C
 */
float Thermostat::getSetpoint() const noexcept {
    return setpoint;
}

/* @brief Set the current setpoint
 * @param value The new setpoint in °C
 * @return True if the setpoint was updated successfully, false otherwise
 */
bool Thermostat::setSetpoint(float value) noexcept {
    if (value < SETPOINT_MIN || value > SETPOINT_MAX) {
        std::cout << "[Thermostat] Invalid setpoint: " << value 
                  << " (limits: " << SETPOINT_MIN << "-" << SETPOINT_MAX << ")\n";
        return false;
    }
    
    setpoint = value;
    std::cout << "[Thermostat] Setpoint updated: " << value << "°C\n";
    
    // Wake up regulation thread for immediate response
    // (disabled to let a steady 1 sec per regulation cycle)
    // regulationCV.notify_all();
    
    return true;
}

/* @brief Set the current valve state
 * @param open True to open the valve, false to close it
 * @return True if the valve state was updated successfully, false otherwise
 */
bool Thermostat::setValveState(bool open) noexcept {
    std::cout << "[Thermostat] Valve control: " << (open ? "OPEN" : "CLOSE") << "\n";
    
    if (open == valveOpen) return true;  // No change needed
    
    bool success = false;
    if (open) {
        // Open valve: disable close relay first, then enable open relay
        success = closeValveRelay.disable() && openValveRelay.enable();
    } else {
        // Close valve: disable open relay first, then enable close relay  
        success = openValveRelay.disable() && closeValveRelay.enable();
    }
    
    if (success) {
        valveOpen = open;
    }
    
    return success;
}

/* @brief Show the heartbeat with the green LED
 */
void Thermostat::modbusHeartbeat() noexcept {
    static int heartbeatCount = 0;
    heartbeatCount++;
    std::cout << "[Thermostat] Modbus heartbeat #" << heartbeatCount << "\n";
    
    // Show heartbeat with green LED blink
    redLED.setOff();
    greenLED.blink(250);
}

/* @brief Show the error with the red LED
 */
void Thermostat::modbusError() noexcept {
    std::cout << "[Thermostat] Modbus error\n";
    
    // Show error with red LED on
    greenLED.setOff();
    redLED.setOn();
}

/* @brief Set the regulation state
 * @param enabled True to enable regulation, false to disable it
 */
void Thermostat::setRegulationState(bool enabled) noexcept {
    if (enabled == regulationEnabled) return;
    
    regulationEnabled = enabled;
    
    if (enabled) {
        if (!regulationRunning) {
            std::cout << "[Thermostat] Starting regulation task...\n";
            regulationRunning = true;
            regulationThread = std::make_unique<std::thread>(&Thermostat::regulationTask, this);
        }
    } else {
        if (regulationRunning) {
            std::cout << "[Thermostat] Stopping regulation task...\n";
            regulationRunning = false;
            regulationCV.notify_all();  // Wake up regulation thread immediately
            if (regulationThread && regulationThread->joinable()) {
                regulationThread->join();
            }
            regulationThread.reset();
        }
    }
}

/* @brief Apply the control output to the valve
 * @param co The control output (0 = no change, -1 = close, +1 = open)
 */
void Thermostat::applyControlOutput(float co) noexcept {
    if (co > 0.5f) {
        // Cooling needed - open valve
        if (!valveOpen) {
            std::cout << "[Thermostat] CO=" << co << " -> COOLING (open valve)\n";
            setValveState(true);
        }
    } else if (co < -0.5f) {
        // Heating needed - close valve  
        if (valveOpen) {
            std::cout << "[Thermostat] CO=" << co << " -> HEATING (close valve)\n";
            setValveState(false);
        }
    }
    // else: hysteresis zone, no change
}

/* @brief Get the status string
 * @return The status string
 */
std::string Thermostat::getStatusString() const {
    std::ostringstream oss;
    oss << "Temp=" << getTemperature() << "°C(" 
        << (isTemperatureValid() ? "OK" : "INVALID") << "), "
        << "Setpoint=" << getSetpoint() << "°C, "
        << "Enabled=" << (getRegulationState() ? "ON" : "OFF") << ", "
        << "Valve=" << (getValveState() ? "OPEN" : "CLOSE");
    return oss.str();
}

/* @brief Print the status
 */
void Thermostat::printStatus() const {
    std::cout << "[Thermostat] Status: " << getStatusString() << "\n";
}

// ===== PUBLIC GETTERS =====
// All getters are now inline in header, delegating to modular classes

// ===== PRIVATE METHODS =====

/* @brief Sensor task
 */
void Thermostat::sensorTask() noexcept {
    std::cout << "[Thermostat] Sensor task started (Modbus RTU)\n";
    
    while (running) {
        // Read sensors
        float temp, humidity;
        if (readModbusSensors(temp, humidity)) {
            updateSensorData(temp, humidity, true);
            sensorErrorCount = 0;
            modbusHeartbeat();
            std::cout << "[Thermostat] Modbus: " << temp << "°C, " << humidity << "%\n";
        } else {
            int errorCount = ++sensorErrorCount;
            std::cout << "[Thermostat] Sensor error " << errorCount << "/" << MAX_SENSOR_ERRORS << "\n";
            
            if (errorCount >= MAX_SENSOR_ERRORS) {
                updateSensorData(0.0f, 0.0f, false);
                modbusError();
                std::cout << "[Thermostat] Sensor unavailable\n";
            }
        }
        
        // Sleep until next reading
        std::this_thread::sleep_for(std::chrono::milliseconds(SENSOR_POLL_INTERVAL_MS));
    }
    
    std::cout << "[Thermostat] Sensor task stopped\n";
}

/* @brief Regulation task
 */
void Thermostat::regulationTask() noexcept {
    std::cout << "[Thermostat] Regulation task started\n";
    
    while (regulationRunning) {
        if (regulationEnabled && temperatureValid) {
            // Run regulation logic
            regulation.setPV(temperature);
            regulation.setSP(setpoint);
            regulation.run();
            
            // Get control output and apply it
            float co = regulation.getCO();
            applyControlOutput(co);
            
            std::cout << "[Regulation] PV=" << temperature << "°C, SP=" << setpoint << "°C, CO=" << co << "\n";
        }
        
        // Wait for 1 second OR until notified (immediate wake-up)
        // to be responsive to UI events (setpoint changes, on/off toggle)
        std::unique_lock<std::mutex> lock(regulationMutex);
        regulationCV.wait_for(lock, std::chrono::seconds(1));
    }
    
    std::cout << "[Thermostat] Regulation task stopped\n";
}

/* @brief Initialize the Modbus connection
 * @return True if the Modbus connection was initialized successfully, false otherwise
 */
bool Thermostat::initializeModbus() noexcept {
    std::cout << "[Thermostat] Initializing Modbus on /dev/ttyS4...\n";
    
    auto* ctx = modbus_new_rtu("/dev/ttyS4", 9600, 'N', 8, 1);
    if (!ctx) {
        std::cout << "[Thermostat] ❌ Failed to create Modbus context\n";
        return false;
    }
    
    if (modbus_set_slave(ctx, 1) == -1) {
        std::cout << "[Thermostat] ❌ Failed to set slave ID: " << strerror(errno) << "\n";
        modbus_free(ctx);
        return false;
    }
    
    if (modbus_connect(ctx) == -1) {
        std::cout << "[Thermostat] ❌ Failed to connect: " << strerror(errno) << "\n";
        modbus_free(ctx);
        return false;
    }
    
    modbusContext = ctx;
    std::cout << "[Thermostat] ✓ Modbus initialized successfully\n";
    return true;
}

/* @brief Cleanup the Modbus connection
 */
void Thermostat::cleanupModbus() noexcept {
    if (modbusContext) {
        auto* ctx = static_cast<modbus_t*>(modbusContext);
        modbus_close(ctx);
        modbus_free(ctx);
        modbusContext = nullptr;
    }
}

/* @brief Read the sensors from the Modbus connection
 * @param temperature The temperature in °C
 * @param humidity The humidity in %
 * @return True if the sensors were read successfully, false otherwise
 */
bool Thermostat::readModbusSensors(float& temperature, float& humidity) noexcept {
    if (!modbusContext) return false;
    
    auto* ctx = static_cast<modbus_t*>(modbusContext);
    uint16_t registers[2];
    int result = modbus_read_registers(ctx, 0, 2, registers);
    
    if (result == -1) {
        std::cout << "[Thermostat] Modbus read error: " << strerror(errno) << "\n";
        return false;
    }
    
    if (result < 2) {
        std::cout << "[Thermostat] Incomplete read: " << result << "/2 registers\n";
        return false;
    }
    
    // Convert values (assuming 0.1 resolution)
    temperature = registers[0] / 10.0f;
    humidity = registers[1] / 10.0f;
    return true;
}

/* @brief Update the sensor data
 * @param temp The temperature in °C
 * @param hum The humidity in %
 * @param valid True if the sensor data is valid, false otherwise
 */
void Thermostat::updateSensorData(float temp, float hum, bool valid) noexcept {
    temperature = temp;
    humidity = hum;
    temperatureValid = valid;
    humidityValid = valid;
}