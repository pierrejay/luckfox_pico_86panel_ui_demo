/* @file Thermostat.hpp
 * @brief "Thermostat" main class definition
 * @brief Defines the Thermostat class and its methods
 */

#pragma once
#include <memory>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <chrono>
#include <string>
#include <sstream>

// Abstractions
#include "RelayOutput.hpp"
#include "LED.hpp"
#include "Regulation.hpp"

// Forward declarations for UI bridge
extern "C" {
    void set_var_ui_red_led_off(bool off);
    void set_var_ui_green_led_off(bool off);
}

// Low-level classes are now in separate headers

class Thermostat {
public:
    // Constructor/Destructor
    Thermostat();
    ~Thermostat();
    
    // Non-copyable, movable
    Thermostat(const Thermostat&) = delete;
    Thermostat& operator=(const Thermostat&) = delete;
    Thermostat(Thermostat&&) = default;
    Thermostat& operator=(Thermostat&&) = default;
    
    // Lifecycle (Arduino-style)
    void begin();
    void end();
    bool isRunning() const noexcept { return running; }
    
    // Sensor readings (direct access)
    float getTemperature() const noexcept { return temperature; }
    float getHumidity() const noexcept { return humidity; }
    bool isTemperatureValid() const noexcept { return temperatureValid; }
    bool isHumidityValid() const noexcept { return humidityValid; }
    
    // Setpoint management (with validation in Thermostat)
    float getSetpoint() const noexcept;
    bool setSetpoint(float value) noexcept;
    float getSetpointMin() const noexcept { return SETPOINT_MIN; }
    float getSetpointMax() const noexcept { return SETPOINT_MAX; }
    
    // Regulation control
    bool getRegulationState() const noexcept { return regulationEnabled; }
    void setRegulationState(bool enabled) noexcept;
    
    // Valve control (high-level with error handling)
    bool getValveState() const noexcept { return valveOpen; }  // true = open, false = close
    bool setValveState(bool open) noexcept;
    
    // Status LEDs (thread-safe)
    void modbusHeartbeat() noexcept;
    void modbusError() noexcept;
    bool getRedLedOff() const noexcept { return redLED.isOff(); }
    bool getGreenLedOff() const noexcept { return greenLED.isOff(); }
    void setRedLedOff(bool off) noexcept { if (off) redLED.setOff(); else redLED.setOn(); }
    void setGreenLedOff(bool off) noexcept { if (off) greenLED.setOff(); else greenLED.setOn(); }
    
    // Status & diagnostics
    std::string getStatusString() const;
    void printStatus() const;
    
private:
    // Configuration constants
    static constexpr float SETPOINT_MIN = 10.0f;
    static constexpr float SETPOINT_MAX = 30.0f;
    static constexpr float REGULATION_HEATING_THRESHOLD = 0.0f;   // SP + 0°C
    static constexpr float REGULATION_COOLING_THRESHOLD = -1.0f;  // SP - 1°C
    static constexpr int SENSOR_POLL_INTERVAL_MS = 2000;          // 2 seconds
    static constexpr int GREEN_LED_BLINK_MS = 250;
    static constexpr int MAX_SENSOR_ERRORS = 3;
    
    // Thread management
    bool running{false};
    bool regulationRunning{false};
    std::unique_ptr<std::thread> sensorThread;
    std::unique_ptr<std::thread> regulationThread;
    std::condition_variable regulationCV;
    std::mutex regulationMutex;
    
    // Sensor data (high-level state)
    float temperature{20.0f};
    float humidity{50.0f};
    bool temperatureValid{false};
    bool humidityValid{false};
    int sensorErrorCount{0};
    
    // Setpoint (high-level state)
    float setpoint{22.0f};
    
    // Regulation (PV/SP/CO algorithm only)
    Regulation regulation;
    bool regulationEnabled{false};
    
    // Valve state (high-level)
    bool valveOpen{true};   // Default open
    
    // Low-level hardware abstractions
    RelayOutput openValveRelay{32};   // GPIO 32
    RelayOutput closeValveRelay{33};  // GPIO 33
    LED redLED{set_var_ui_red_led_off};
    LED greenLED{set_var_ui_green_led_off};
    
    // Modbus context (managed internally)
    void* modbusContext{nullptr};  // modbus_t* (void* to avoid C include)
    
    // Private methods
    void sensorTask() noexcept;
    void regulationTask() noexcept;
    bool initializeModbus() noexcept;
    void cleanupModbus() noexcept;
    bool readModbusSensors(float& temperature, float& humidity) noexcept;
    void updateSensorData(float temperature, float humidity, bool valid) noexcept;
    void applyControlOutput(float co) noexcept;  // Map CO to valve relays
};