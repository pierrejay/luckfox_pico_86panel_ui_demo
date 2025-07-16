/* @file RelayOutput.hpp
 * @brief "RelayOutput" class definition
 * @brief Controls a relay output using GPIO (Linux sysfs interface)
 */

#pragma once
#include <mutex>
#include <iostream>
#include <cstdio>
#include <cstring>

class RelayOutput {
public:
    RelayOutput(int gpioPin) : gpioPin_(gpioPin), state_(false) {
        initGPIO();
    }
    
    bool enable() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (setGPIO(true)) {
            state_ = true;
            std::cout << "[GPIO" << gpioPin_ << "] Enabled\n";
            return true;
        }
        std::cout << "[GPIO" << gpioPin_ << "] ERROR: Failed to enable\n";
        return false;
    }
    
    bool disable() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (setGPIO(false)) {
            state_ = false;
            std::cout << "[GPIO" << gpioPin_ << "] Disabled\n";
            return true;
        }
        std::cout << "[GPIO" << gpioPin_ << "] ERROR: Failed to disable\n";
        return false;
    }
    
    bool getState() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return state_;
    }
    
private:
    void initGPIO() {
        char path[64];
        
        // Export GPIO
        FILE* exportFile = fopen("/sys/class/gpio/export", "w");
        if (exportFile) {
            fprintf(exportFile, "%d", gpioPin_);
            fclose(exportFile);
        }
        
        // Set direction
        snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/direction", gpioPin_);
        FILE* dirFile = fopen(path, "w");
        if (dirFile) {
            fprintf(dirFile, "out");
            fclose(dirFile);
        }
    }
    
    bool setGPIO(bool state) {
        char path[64];
        snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", gpioPin_);
        FILE* valueFile = fopen(path, "w");
        if (valueFile) {
            fprintf(valueFile, "%d", state ? 1 : 0);
            fclose(valueFile);
            return true;
        }
        return false;
    }
    
    mutable std::mutex mutex_;
    int gpioPin_;
    bool state_;
};