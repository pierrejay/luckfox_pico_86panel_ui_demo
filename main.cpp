#include "Thermostat.hpp"
#include "source/thermostat_ui/ui/ui.h"
#include "lvgl/lvgl.h"
#include "lv_drivers/display/fbdev.h"
#include "lv_drivers/indev/evdev.h"
#include <memory>
#include <chrono>
#include <thread>
#include <iostream>
#include <cstdint>
#include <sys/time.h>
#include <unistd.h>

// Display configuration
#define DISP_BUF_SIZE (720*720)

// Global thermostat instance (accessible from C bridge)
std::unique_ptr<Thermostat> g_thermostat;

// C interface for UI bridge
extern "C" {
    Thermostat* getThermostatInstance() {
        return g_thermostat.get();
    }
    
    // LVGL tick function
    uint32_t custom_tick_get(void) {
        static uint64_t start_ms = 0;
        if(start_ms == 0) {
            struct timeval tv_start;
            gettimeofday(&tv_start, NULL);
            start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
        }

        struct timeval tv_now;
        gettimeofday(&tv_now, NULL);
        uint64_t now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

        return static_cast<uint32_t>(now_ms - start_ms);
    }
}

int main() {
    std::cout << "=== LVGL Thermostat POC - C++ Version ===\n";
    
    try {
        // Initialize LVGL
        std::cout << "Initializing LVGL...\n";
        lv_init();

        // Linux framebuffer device init
        fbdev_init();

        // Buffer for LVGL to draw screen content
        static lv_color_t buf[DISP_BUF_SIZE];

        // Initialize buffer descriptor
        static lv_disp_draw_buf_t disp_buf;
        lv_disp_draw_buf_init(&disp_buf, buf, NULL, DISP_BUF_SIZE);

        // Initialize and register display driver
        static lv_disp_drv_t disp_drv;
        lv_disp_drv_init(&disp_drv);
        disp_drv.draw_buf = &disp_buf;
        disp_drv.flush_cb = fbdev_flush;
        disp_drv.hor_res = 720;
        disp_drv.ver_res = 720;
        lv_disp_drv_register(&disp_drv);

        // Initialize touch input
        evdev_init();
        static lv_indev_drv_t indev_drv;
        lv_indev_drv_init(&indev_drv);
        indev_drv.type = LV_INDEV_TYPE_POINTER;
        indev_drv.read_cb = evdev_read;
        lv_indev_drv_register(&indev_drv);

        std::cout << "✓ LVGL initialized (720x720 display)\n";

        // Initialize EEZ Studio UI
        std::cout << "Initializing EEZ UI...\n";
        ui_init();
        std::cout << "✓ EEZ UI initialized\n";

        // Create and start thermostat instance (C++ style)
        std::cout << "Creating thermostat instance...\n";
        g_thermostat = std::make_unique<Thermostat>();
        
        std::cout << "Starting thermostat...\n";
        g_thermostat->begin();
        
        std::cout << "✓ Thermostat started successfully\n";
        std::cout << "Status: " << g_thermostat->getStatusString() << "\n";
        std::cout << "\n=== Entering main loop ===\n";

        // Main LVGL event loop
        auto lastStatusPrint = std::chrono::steady_clock::now();
        constexpr auto STATUS_INTERVAL = std::chrono::seconds(30);
        
        while (true) {
            // Handle LVGL events
            lv_timer_handler();
            
            // Handle EEZ UI updates
            ui_tick();
            
            // Print status periodically
            auto now = std::chrono::steady_clock::now();
            if (now - lastStatusPrint >= STATUS_INTERVAL) {
                g_thermostat->printStatus();
                lastStatusPrint = now;
            }
            
            // Small delay to prevent CPU hogging
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }

    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        
        // Cleanup on error
        if (g_thermostat) {
            std::cout << "Stopping thermostat due to error...\n";
            g_thermostat->end();
            g_thermostat.reset();
        }
        
        return 1;
    }

    // Normal cleanup (unreachable in current design)
    if (g_thermostat) {
        std::cout << "Stopping thermostat...\n";
        g_thermostat->end();
        g_thermostat.reset();
    }

    std::cout << "Thermostat application terminated\n";
    return 0;
}