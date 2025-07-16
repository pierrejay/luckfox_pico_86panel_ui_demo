/* @file Regulation.hpp
 * @brief "Regulation" class definition
 * @brief Implements a simple bang-bang controller with hysteresis
 */

#pragma once
#include <mutex>

class Regulation {
public:
    /* @brief Set the process value
     * @param processValue The process value
     */
    void setPV(float processValue) {
        std::lock_guard<std::mutex> lock(mutex_);
        pv_ = processValue;
    }

    /* @brief Set the set point
     * @param setPoint The set point
     */
    void setSP(float setPoint) {
        std::lock_guard<std::mutex> lock(mutex_);
        sp_ = setPoint;
    }

    /* @brief Get the control output
     * @return The control output
     */
    float getCO() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return co_;
    }

    /* @brief Run the regulation
     */
    void run() {
        std::lock_guard<std::mutex> lock(mutex_);
        
        // Simple bang-bang controller with hysteresis
        float error = sp_ - pv_;  // Error = SP - PV
        
        if (error >= 1.0f) {
            // Need heating (close valve)
            co_ = -1.0f;
        } else if (error <= 0.0f) {
            // Need cooling (open valve)  
            co_ = 1.0f;
        } else {
            // Hysteresis zone - keep current state
            // co_ unchanged
        }
    }
    
private:
    mutable std::mutex mutex_;
    float pv_{20.0f};      // Process Value (current temperature)
    float sp_{22.0f};      // Set Point (target temperature)
    float co_{0.0f};       // Control Output (-1=heating, 0=off, +1=cooling)
};