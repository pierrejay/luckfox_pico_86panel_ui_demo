/* @file LED.hpp
 * @brief "UI LED" class definition
 * @brief Controls a LED in the LVGL UI (allows for on/off or blinking)
 */

#pragma once
#include <mutex>
#include <iostream>

// Use LVGL headers directly
extern "C" {
    #include <lvgl/lvgl.h>
}

class LED {
public:
    using UIUpdateFunction = void(*)(bool isOff);
    
    LED(UIUpdateFunction uiUpdate) : uiUpdateFunc_(uiUpdate), state_(false), blinkTimer_(nullptr) {}
    
    /* @brief Set the LED to ON
     */
    void setOn() {
        bool change;
        {   // scope of the lock
            std::lock_guard<std::mutex> lock(mutex_);
            change = state_;          // true if OFF → it must be set ON
            state_ = false;           // false = LED ON
        }
        
        // Cancel any running blink timer when setting ON manually
        if (blinkTimer_) {
            lv_timer_del(blinkTimer_);
            blinkTimer_ = nullptr;
        }
        
        if (change) updateUI();       // out of lock
    }

    /* @brief Set the LED to OFF
     */
    void setOff() {
        bool change;
        {
            std::lock_guard<std::mutex> lock(mutex_);
            change = !state_;         // false if already OFF
            state_ = true;            // true = LED OFF
        }
        
        // Cancel any running blink timer when setting OFF
        if (blinkTimer_) {
            lv_timer_del(blinkTimer_);
            blinkTimer_ = nullptr;
        }
        
        if (change) updateUI();       // out of lock
    }

    /* @brief Blink the LED
     * @param durationMs The duration of the blink in milliseconds
     */
    void blink(int durationMs = 250) {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            state_ = false;
        }   // the mutex is released here

        updateUI(); 

        if (blinkTimer_) lv_timer_del(blinkTimer_);

        blinkTimer_ = lv_timer_create(
            [](lv_timer_t* t){
                auto* led = static_cast<LED*>(t->user_data);
                led->setOff();                // will call updateUI()
                led->blinkTimer_ = nullptr;
            },
            durationMs, this);
    }

    /* @brief Check if the LED is OFF
     * @return True if the LED is OFF, false otherwise
     */
    bool isOff() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return state_;
    }

private:
    /* @brief Update the UI to force LED state
     */
    void updateUI() {
        if (uiUpdateFunc_) {
            // Direct call - NO ASYNC to avoid infinite loops
            uiUpdateFunc_(state_);
        }
    }
    
    UIUpdateFunction uiUpdateFunc_;
    mutable std::mutex mutex_;
    bool state_;        // true = OFF, false = ON (inverted logic)
    lv_timer_t* blinkTimer_;
};