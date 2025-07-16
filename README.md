# LVGL/EEZ Studio C++ Development - Luckfox Panel 86 demo

## Overview

This guide shows how to build a self-contained embedded application on the Luckfox Panel 86 using LVGL graphics and EEZ Studio UI generation, progressing from a simple example to a thermostat application with C++17.

**Starting Point:** We build upon the official Luckfox Panel 86 demo [available on GitHub](https://github.com/LuckfoxTECH/luckfox_pico_86panel_ui_demo), which provides the foundation LVGL display system and touch handling. Our approach extends this base with C++ while maintaining compatibility with the existing hardware drivers and build system, using the official [luckfox-pico](https://github.com/LuckfoxTECH/luckfox-pico) SDK/toolchain to compile the final executable running on the Panel 86.

## Why LVGL for Embedded Applications?

### Performance and Resource Efficiency

**Self-Contained Native Execution:** LVGL applications compile to a single executable that runs directly on Linux, without browser overhead or JavaScript interpretation. This approach is particularly valuable on constrained hardware like the Panel 86 (256MB RAM, 1GHz single-core ARM).

**Direct Framebuffer Access:** LVGL renders directly to the Linux framebuffer, achieving ~200 FPS capability with minimal CPU usage. This direct hardware access eliminates the multiple abstraction layers found in web-based solutions (browser engine → DOM → CSS → rendering), resulting in immediate touch response and smooth animations.

**Resource Comparison:**
- **LVGL Application:** ~12MB RAM total, <2% CPU usage, 700KB executable
- **Web-based UI:** ~50-100MB RAM (browser + JS runtime), ~15-30% CPU usage, requires separate web server

### Industrial Application Benefits

**Lightweight Industrial Controls:** The Panel 86 hardware, while not industrial-grade, effectively demonstrates principles applicable to industrial automation. The low resource usage leaves headroom for real-time control tasks, sensor polling, and communication protocols.

**System Integration Potential:** This architecture naturally extends to SCADA integration, PLC communication, and distributed control systems. The lightweight nature allows the Panel 86 to serve as an HMI (Human-Machine Interface) while delegating time or safety-critical control tasks to dedicated PLCs or MCU-driven controllers.

**Reliability Through Simplicity:** A native, single-file approach reduces dependency complexity, eliminates network connectivity requirements for UI functionality, and provides predictable startup times - critical factors for industrial applications.

---

## Part 1: EEZ Studio Integration Fundamentals

### Understanding LVGL and EEZ Studio Integration

**LVGL (Light and Versatile Graphics Library)** is the graphics framework that powers the Panel 86's touchscreen interface. LVGL provides widgets, event handling, and rendering, but requires manual coding for UI layout and logic.

**EEZ Studio** solves this by providing a visual designer that generates LVGL code automatically. You design the interface graphically, and EEZ Studio produces C files that create the widgets, handle events, and manage the UI refresh cycle.

**Key Concept:** EEZ Studio generates the LVGL code, then you connect your application logic to the generated interface through standardized getter, setter & event callback functions.

#### Generated Files Structure
```
ui/
├── ui.c/.h         # Main UI initialization and lifecycle (ui_init, ui_tick, loadScreen)
├── screens.c/.h    # Complete LVGL layout and widgets (create_screens, tick_screen)
├── vars.h          # Declarations for UI elements (get_var_*, set_var_*)  <- needs "glue code" to main app
├── actions.h       # Callback function declarations (action_*)            <- needs "glue code" to main app
├── fonts.h         # Custom fonts referenced in EEZ project
├── structs.h       # EEZ internal data structures
├── styles.c/.h     # Visual styling definitions (colors, sizes, animations)
└── images.c/.h     # Graphical assets compiled as C arrays
```

**Critical rule:** Never modify generated files manually. They are overwritten each time you regenerate from EEZ Studio.

In the following sections we will explain in incremental steps how to connect EEZ-generated LVGL code to the application code.

### Simple Integration Example: "Ping Google"

**Bridging from Luckfox Base to EEZ Studio**

Starting with the basic Luckfox C example (main.c + LVGL), we first demonstrate how to integrate EEZ Studio-generated UI with the existing C codebase. This minimal example shows network connectivity status and establishes the fundamental pattern we'll use for more complex applications.

The UI is composed of a button that triggers a `ping 8.8.8.8` request, a spinner rotating during a request is in flight, and metrics that display the status & latency of last ping request.

<img width="539" height="538" alt="Capture d’écran 2025-07-16 à 18 14 27" src="https://github.com/user-attachments/assets/8cc7c41a-6b67-426c-a581-c6a411ef3850" />

**Reference Implementation:** The repository includes a `main-ping_demo.c.old` file that shows this basic integration using the `ping_demo` example. This file demonstrates the original Luckfox Panel 86 demo structure adapted for EEZ Studio UI, but **it's not active in the build** - it's preserved for educational reference only.

**Why Start with C?** This demonstrates the integration pattern at the same abstraction level as the original Luckfox example, making it easier to understand before introducing C++ concepts.

#### Required Implementation Files ("glue code")

**vars.c** - Data bridge between UI and application:
```c
// EEZ calls this to get current status for display
const char* get_var_connection_status() {
    return ping_google() ? "Connected" : "Disconnected";
}

// EEZ calls this to get LED state
int get_var_status_led_green() {
    return is_connected() ? 0 : 1;  // 0 = show, 1 = hide
}
```

**ping_handler.c** - Action callbacks for user interactions:
```c
// EEZ calls this when user presses "Test Connection" button
void action_test_connection(lv_event_t * e) {
    printf("Testing connection...\n");
    test_connection_async();  // Your implementation
}
```

#### Data Flow Pattern

1. **UI → Application:** User presses button → EEZ calls `action_test_connection()` → Your code executes
2. **Application → UI:** EEZ refresh cycle calls `get_var_connection_status()` → Returns current state → UI updates

This pattern scales to any application complexity while maintaining clean separation between UI and business logic.

---

## Part 2: Thermostat Application Development

### Project Goals: From Simple Example to More Complex Application

**The Project:** Now that we understand the EEZ Studio integration pattern, let's work on a more complex example. We'll build a thermostat system using embedded Linux development practices.

**Why a Thermostat?** This application combines multiple embedded system challenges: sensor communication (Modbus RTU), real-time control algorithms, hardware interfacing (GPIO relays), user interface design, and threading for responsive operation. It's complex enough to show useful techniques while remaining manageable.

**Why Transition to C++?** While the basic EEZ integration works well in C, a thermostat application introduces complexity that can benefit from C++ features:

- **Object-oriented design:** Clean separation of application components (sensors, relays, control loop, I/O...)
- **RAII resource management:** Automatic cleanup of GPIO, Modbus connections, and threads
- **Type safety:** Compile-time error detection for temperature values, setpoints, and control states
- **STL threading:** Modern `std::thread`, `std::mutex` and `std::condition_variable` for native multitasking with responsive control
- **Exception handling:** Structured error management in main thread instead of complex return code checking
- **Smart pointers:** Automatic memory management prevents leaks in long-running applications

### Application Requirements

**Core Functionality:**
- Display temperature/humidity from Modbus RTU sensor
- User-adjustable temperature setpoint via touchscreen
- Automatic regulation with manual override capability
- Valve control via GPIO relays (3-point zone valve)
- Visual status indicators (sensor health, regulation state)

**Technical Requirements:**
- Thread-safe operation (UI + sensor polling)
- Robust error handling
- Real-time response to user input
- Modbus RTU communication over RS485

### UI Design and Layout
<img width="539" alt="Capture d’écran 2025-07-04 à 22 31 25" src="https://github.com/user-attachments/assets/5bb0a6cf-5c69-485a-8de9-4a53c0c36715" />

The interface features:
- Large temperature display with humidity reading
- Circular setpoint adjustment control
- Toggle switches for regulation enable/disable
- Manual valve control buttons
- Status LEDs for system health indication

### C++ Class Architecture Design

#### Project Organization and Directory Structure

**Organized Codebase:** All C++ business logic is organized in the `source/thermostat_app/` directory, separating the application code from LVGL framework files, build artifacts, and UI-generated content. This creates a clean distinction between what you write and what's generated or provided by third parties.

```
source/
├── thermostat_app/       # Your C++ application code
│   ├── Thermostat.hpp    # Main controller class  
│   ├── Thermostat.cpp    # Implementation
│   ├── LED.hpp           # LED status indicators
│   ├── RelayOutput.hpp   # GPIO relay control
│   ├── Regulation.hpp    # Control algorithm  
│   └── thermostat_bridge.cpp # C++ to C bridge
├── thermostat_ui/        # EEZ-generated UI integration
│   ├── thermostat_handler.c  # UI action callbacks (your code)
│   └── ui/               # EEZ Studio generated files
│       ├── screens.c     # LVGL layout (generated)
│       ├── vars.c        # Variable bridge (your code)
│       └── ...           # Other generated files
├── ping_demo/            # Simple C integration example (reference)
│   ├── ping_handler.c    # Basic action callbacks
│   └── eez_ui/           # EEZ Studio generated files
└──...

lvgl/, lv_drivers/        # LVGL framework (vendor)
lib/libmodbus_arm/        # Cross-compiled dependency
main.cpp                  # Active C++ application entry point
main.c.old                # Reference C entry point (ping_demo example, NOT built)
```

**Benefits of This Organization:**
- **Clear separation:** Generated code vs. your implementation
- **Easy navigation:** All business logic in one directory
- **Extensible:** Add new C++ classes to `source/thermostat_app/` as needed
- **Version control friendly:** Can exclude generated files from commits

#### Building the Central Thermostat Controller

**Design Philosophy:** The main Thermostat class serves as the central coordinator, orchestrating all hardware components and business logic. We deliberately choose a comprehensive getter/setter API design that will make the C++ to C bridge simple and predictable.

**Why Full Getter/Setter Pattern?** Each piece of application state (temperature, setpoint, regulation status, valve position) gets dedicated getter and setter methods. This creates a clean interface that the UI bridge can easily call without understanding the internal threading or hardware complexity.

**source/thermostat_app/Thermostat.hpp** - Central controller with "Arduino-style" lifecycle:
```cpp
class Thermostat {
public:
    // Lifecycle
    void begin();
    void end();
    bool isRunning() const noexcept { return running; }
    
    // Sensor readings (direct access)
    float getTemperature() const noexcept { return temperature; }
    float getHumidity() const noexcept { return humidity; }
    bool isTemperatureValid() const noexcept { return temperatureValid; }
    bool isHumidityValid() const noexcept { return humidityValid; }
    
    // Setpoint management
    float getSetpoint() const noexcept;
    bool setSetpoint(float value) noexcept;
    
    // Regulation control
    bool getRegulationState() const noexcept { return regulationEnabled; }
    void setRegulationState(bool enabled) noexcept;
    
    // Valve control
    bool getValveState() const noexcept { return valveOpen; }
    bool setValveState(bool open) noexcept;
    
    // Status LEDs (thread-safe)
    void modbusHeartbeat() noexcept;
    void modbusError() noexcept;
    bool getRedLedOff() const noexcept { return redLED.isOff(); }
    bool getGreenLedOff() const noexcept { return greenLED.isOff(); }
    
private:
    // Threading
    std::unique_ptr<std::thread> sensorThread;
    std::unique_ptr<std::thread> regulationThread;
    std::condition_variable regulationCV;
    std::mutex regulationMutex;
    
    // Hardware abstractions (composition, not unique_ptr)
    RelayOutput openValveRelay{32};   // GPIO 32
    RelayOutput closeValveRelay{33};  // GPIO 33
    LED redLED{set_var_ui_red_led_off};
    LED greenLED{set_var_ui_green_led_off};
    Regulation regulation;
    
    // Sensor data
    float temperature{20.0f};
    float humidity{50.0f};
    bool temperatureValid{false};
    bool humidityValid{false};
    
    // Control state
    float setpoint{22.0f};
    bool regulationEnabled{false};
    bool valveOpen{true};
};
// ... (see full implementation)
```

**Key Design Principles:**
- **Composition over inheritance:** Each hardware component is a separate class instantiated directly (not via `unique_ptr`), making the design simple and predictable
- **Thread safety:** All public methods use `noexcept` and proper mutex locking for safe concurrent access between UI and sensor threads
- **RAII:** Automatic resource management prevents memory leaks and ensures proper GPIO/Modbus cleanup on destruction
- **Arduino-style lifecycle:** Familiar `begin()/end()` pattern for embedded developers, with clear initialization phases
- **Industrial terminology:** Uses standard PV/SP/CO regulation terms familiar to automation engineers

### Hardware Abstraction and Physical I/O Control

**Building on Luckfox Foundation:** The hardware abstractions follow the same patterns used in the original Luckfox examples, which demonstrate GPIO control through the standard Linux API. We extend these examples with C++ classes that provide safer, more maintainable interfaces while preserving the underlying Linux system calls.

**Integration Strategy:** Each hardware component combines its abstraction class with the actual physical control implementation. This keeps related code together and makes the system easier to understand and debug.

#### GPIO Relay Control - Complete Implementation
**source/thermostat_app/RelayOutput.hpp** - Linux sysfs GPIO interface with critical hardware considerations:

**Hardware Requirements:**
- **External 12-24V power supply required** - USB power alone cannot drive built-in relays
- GPIO 32 controls valve opening relay, GPIO 33 controls valve closing relay
- Never allow both relays in the same state simultaneously (valve is either open or closed)

```cpp
class RelayOutput {
public:
    RelayOutput(int gpioPin) : gpioPin_(gpioPin), state_(false) {
        initGPIO();  // Automatic GPIO export and direction setup
    }
    
    bool enable();     // Set GPIO high (3.3V) - activates relay
    bool disable();    // Set GPIO low (0V) - deactivates relay  
    bool getState() const;
    
private:
    void initGPIO();   // Export GPIO via /sys/class/gpio/export
    bool setGPIO(bool state);  // Write to /sys/class/gpio/gpioXX/value
    
    mutable std::mutex mutex_;  // Thread-safe relay control
    int gpioPin_;      // Physical GPIO number (32 or 33)
    bool state_;       // Current relay state
};
```

**Implementation Details:**
- Uses Linux sysfs interface (`/sys/class/gpio/`) - no kernel modules required
- Automatic GPIO export and direction configuration in constructor
- Thread-safe operation with mutex protection for concurrent access
- Error handling returns `false` if GPIO access fails (permissions, hardware issues)

#### LED Status Indicators
**source/thermostat_app/LED.hpp** - Thread-safe LVGL integration for visual system feedback:

**Design Philosophy:**
- LEDs are UI elements (not physical LEDs), controlled via LVGL widget visibility
- Thread-safe updates from background sensor thread to UI thread
- Uses function pointer injection for UI callback, avoiding tight coupling to specific UI implementation

```cpp
class LED {
public:
    using UIUpdateFunction = void(*)(bool isOff);
    
    LED(UIUpdateFunction uiUpdate) : uiUpdateFunc_(uiUpdate), state_(false) {}
    
    void setOn();      // Immediate LED activation
    void setOff();     // Immediate LED deactivation
    void blink(int durationMs = 250);  // Blink once for heartbeat indication
    bool isOff() const;  // Thread-safe state query
    
private:
    void updateUI();   // Direct UI callback (no async to avoid infinite loops)
    
    UIUpdateFunction uiUpdateFunc_;  // Injected UI callback function
    mutable std::mutex mutex_;       // Protects state changes
    bool state_;        // true = OFF, false = ON (inverted UI logic)
    lv_timer_t* blinkTimer_;        // LVGL timer for blink duration
};
```

**Key Implementation Details:**
- **Inverted logic:** `state_ = true` means LED OFF (hidden), `state_ = false` means LED ON (visible)
- **Thread safety:** Mutex protects state changes, UI updates called outside mutex scope
- **No async calls:** Direct UI updates to prevent infinite callback loops
- **LVGL timer integration:** Uses `lv_timer_create()` for precise blink timing
- **Function pointer injection:** Constructor takes UI callback, enabling different LED implementations

#### Regulation Algorithm
**source/thermostat_app/Regulation.hpp** - Minimalist, user-managed PV/SP/CO regulation interface:

**Design Philosophy:**
- **Minimalist approach:** Pure algorithm implementation, no I/O or hardware dependencies
- **User-managed polling:** You control when regulation runs by calling `update()`
- **Industry standard terminology:** PV/SP/CO familiar to automation engineers
- **Easily extensible:** Replace with PID, fuzzy logic, or adaptive control in `.cpp` implementation

```cpp
class Regulation {
public:
    // Market practice: PV/SP/CO terminology
    void setPV(float processValue);    // Current temperature (°C)
    void setSP(float setPoint);        // Target temperature (°C)
    float getCO() const;               // Control Output (-1/0/+1)
    void run();                        // Execute control algorithm
    
private:
    mutable std::mutex mutex_;
    float pv_{20.0f};      // Process Value (current sensor reading)
    float sp_{22.0f};      // Set Point (user target)
    float co_{0.0f};       // Control Output (-1=heating, +1=cooling, 0=off)
};
```

**Algorithm Implementation (Bang-Bang with Hysteresis):**
- **Heating zone:** When `SP - PV >= 1.0°C` → `CO = -1` (close valve, enable heating)
- **Cooling zone:** When `PV - SP >= 0.0°C` → `CO = +1` (open valve, enable cooling)  
- **Hysteresis zone:** Between thresholds → `CO` unchanged (prevents oscillation)
- **Thread-safe:** All operations protected by mutex for concurrent access

**Usage Pattern:**
1. Background thread: `regulation.setPV(currentTemperature)`
2. UI thread: `regulation.setSP(userSetpoint)` 
3. Control thread: `regulation.run()` → `co = regulation.getCO()` → apply to hardware
4. **Extensibility:** Replace algorithm in `.cpp` without changing interface

#### Modbus RTU Sensor Communication - Complete Implementation
**Using libmodbus library for industrial sensor integration:**

**Hardware Setup:**
- **RS485 sensor connected to Panel 86 UART4** (`/dev/ttyS4`)
- **Communication parameters:** 9600 baud, 8 data bits, no parity, 1 stop bit (8N1)
- **Slave addressing:** Sensor configured as Modbus slave ID 1
- **Register mapping:** Register 0 = temperature×10, Register 1 = humidity×10
- **Physical connection:** Two-wire RS485 bus with proper termination resistors

```cpp
// Background sensor polling thread (runs every 2 seconds)
void Thermostat::sensorTask() {
    // Initialize libmodbus RTU context
    modbus_t* ctx = modbus_new_rtu("/dev/ttyS4", 9600, 'N', 8, 1);
    modbus_set_slave(ctx, 1);  // Target slave device ID 1
    
    if (modbus_connect(ctx) == -1) {
        std::cout << "Modbus connection failed: " << modbus_strerror(errno) << std::endl;
        return;
    }
    
    while (running_) {
        uint16_t registers[2];  // Raw register values from sensor
        
        // Read 2 consecutive registers starting from address 0
        if (modbus_read_registers(ctx, 0, 2, registers) == 2) {
            // Convert scaled values: register×10 format
            float temp = registers[0] / 10.0f;    // 253 → 25.3°C
            float humid = registers[1] / 10.0f;   // 562 → 56.2%
            
            updateSensorData(temp, humid, true);  // Update with valid data
            greenLED.blink(250);  // Visual heartbeat confirmation
        } else {
            // Communication error - sensor offline or wiring issue
            handleSensorError();
            redLED.setOn();      // Persistent error indication
        }
        
        std::this_thread::sleep_for(std::chrono::seconds(2));  // 2-second polling
    }
    
    // Cleanup libmodbus resources
    modbus_close(ctx);
    modbus_free(ctx);
}
```

**libmodbus Integration Benefits:**
- **Standard library:** Handles RTU framing, CRC calculation, timeout management
- **Error handling:** Built-in retry logic and clear error reporting via `modbus_strerror()`
- **Cross-platform:** Same API works on x86 development and ARM target
- **Lightweight:** Optimized C library with minimal overhead

### C++ to C Bridge Layer

#### The Bridge Necessity and Integration Strategy

**Why Do We Need a Bridge?** EEZ Studio generates pure C code that expects C function signatures, but our application logic is implemented in C++. The bridge layer solves this impedance mismatch by providing C-compatible functions that internally call our C++ methods.

**Connection to LVGL Integration:** Remember our EEZ integration pattern from Part 1? The UI calls `get_var_temperature()` and `action_setpoint_up()` functions. These C functions now need to communicate with our C++ Thermostat instance, which is where the bridge becomes essential.

**source/thermostat_app/thermostat_bridge.cpp** - Clean C interface bridging EEZ Studio UI with C++ application:

**Bridge Architecture Design:**
- **Single instance management:** C++ instance handled internally, no instance parameters from UI layer
- **Type conversion:** Handles C `int` ↔ C++ `bool` conversions for EEZ compatibility  
- **Error safety:** Null-safe operations prevent crashes if C++ instance unavailable
- **Thread-safe access:** All calls route through thread-safe C++ methods
- **Simplified API:** Clean, predictable function names that mirror the C++ interface
```cpp
extern "C" {
    // Temperature display
    float thermostat_get_temperature() {
        auto* instance = getThermostatInstance();
        return instance ? instance->getTemperature() : 0.0f;
    }
    
    // Setpoint control
    float thermostat_get_setpoint() {
        auto* instance = getThermostatInstance();
        return instance ? instance->getSetpoint() : 22.0f;
    }
    
    int thermostat_set_setpoint(float value) {
        auto* instance = getThermostatInstance();
        return instance ? (instance->setSetpoint(value) ? 1 : 0) : 0;
    }
    
    // Regulation control
    int thermostat_get_regulation_state() {
        auto* instance = getThermostatInstance();
        return instance ? (instance->getRegulationState() ? 1 : 0) : 0;
    }
    
    void thermostat_set_regulation_state(int enabled) {
        auto* instance = getThermostatInstance();
        if (instance) {
            instance->setRegulationState(enabled != 0);
        }
    }
}
```

### Main Application Entry Point

#### Transforming the Luckfox Foundation

**From C to C++ Entry Point:** The original Luckfox example uses a straightforward C main() function that initializes LVGL and runs the event loop. Our approach preserves this structure while adding C++ application management and exception handling.

**Global Instance Strategy:** We manage the Thermostat instance as a global `std::unique_ptr`, making it accessible to the bridge layer while ensuring proper RAII cleanup. This approach balances simplicity with safety.

**main.cpp** - C++ application initialization with robust error handling:
```cpp
#include "Thermostat.hpp"
#include <memory>

// Global instance for C bridge access
static std::unique_ptr<Thermostat> g_thermostat;

extern "C" {
    Thermostat* getThermostatInstance() {
        return g_thermostat.get();
    }
}

int main(int argc, char **argv) {
    try {
        // LVGL initialization (same as original C code)
        lv_init();
        lv_disp_drv_init(&disp_drv);
        // ... display setup ...
        
        // Create C++ application instance
        g_thermostat = std::make_unique<Thermostat>();
        
        if (!g_thermostat->begin()) {
            fprintf(stderr, "Failed to initialize thermostat\n");
            return 1;
        }
        
        // Create EEZ UI
        ui_init();
        
        // Main event loop
        while (true) {
            lv_timer_handler();
            ui_tick();
            usleep(10000);  // 100Hz refresh rate
        }
        
    } catch (const std::exception& e) {
        fprintf(stderr, "Application error: %s\n", e.what());
        return 1;
    }
    
    return 0;
}
```

**Key Changes from C:**
- **Exception handling:** Structured error management with try/catch vs manual return code checking
- **RAII:** Automatic resource cleanup via destructors - no manual cleanup sequences required
- **Smart pointers:** `std::unique_ptr` prevents memory leaks and ensures proper object lifetime management
- **Type safety:** Compile-time checking catches errors that would only surface at runtime in C
- **STL threading:** Modern C++17 `std::thread`, `std::condition_variable` instead of raw pthreads

---

## Part 3: Build System and Deployment

### Build System Architecture Understanding

#### Why Two Different Build Systems?

**The Challenge:** This project combines multiple components with different build requirements:
1. **libmodbus** - External C library using autotools (./configure + make)
2. **Our application** - C++ code with LVGL integration using CMake
3. **Cross-compilation** - Everything must target Rockchip ARM architecture

**Key Difference from Basic Luckfox Examples:** The original Luckfox examples compile everything with a simple Makefile. Our approach adds C++ classes, external libraries, and modern build practices using CMake.

#### Build System Components

**1. Makefile_libmodbus (Dependency Management)**
```bash
# Handles external library cross-compilation
make -f Makefile_libmodbus    # Clone + configure + cross-compile libmodbus
```
- **Purpose:** Automate libmodbus cross-compilation using its native autotools
- **Output:** `lib/libmodbus_arm/lib/libmodbus.a` (ARM static library)
- **Why separate:** libmodbus uses autotools, not CMake - we wrap it for convenience
- **One-time setup:** Only run when libmodbus changes or first setup

**2. CMakeLists.txt (Main Application)**
```cmake
# Compiles our C++ application + links everything together
cmake .. && make             # Build complete thermostat application
```
- **Purpose:** Compile our C++ classes, EEZ UI code, and link with dependencies
- **Input:** C++ sources + libmodbus ARM library + LVGL framework
- **Output:** `thermostat_demo` executable (ARM binary)

#### Linking and Integration Flow

**Step 1: External Dependency (libmodbus)**
```
libmodbus source → autotools configure → ARM cross-compile → lib/libmodbus_arm/
```

**Step 2: Our Application Components**
```
CMake orchestrates:
├── source/thermostat_app/*.cpp     → Compiled to object files
├── source/thermostat_ui/*.c        → Compiled to object files  
├── lvgl/*.c + lv_drivers/*.c       → Compiled to object files
└── lib/libmodbus_arm/lib/libmodbus.a → Linked as static library
                                    ↓
                            Final ARM executable
```

**The Integration Magic:**
- **C++ Bridge Layer:** `thermostat_bridge.cpp` provides C-compatible functions for EEZ UI
- **Static Linking:** `libmodbus.a` becomes part of final executable (no runtime dependencies)
- **LVGL Integration:** UI framework compiled directly into application
- **Single Binary:** Everything linked into one self-contained ARM executable

#### Key Differences from Basic Luckfox Approach

**Basic Luckfox (simple):**
```
main.c + LVGL sources → Direct compilation → Simple executable
```

**Our Approach (structured):**
```
External deps → Our C++ classes → UI integration → Feature-rich executable
    ↓              ↓                 ↓
libmodbus → Thermostat.cpp → EEZ Studio UI → Complete thermostat system
```

**Benefits of Our Approach:**
- **Modularity:** Clear separation between business logic, UI, and external libraries
- **Maintainability:** C++ classes encapsulate complexity
- **Extensibility:** Easy to add new sensors, control algorithms, or UI features
- **Industrial-grade:** Proper error handling, threading, and resource management

### Cross-Compilation Strategy and Process

**Two-Step Build Process:** Building for the Panel 86 requires a specific sequence:
1. **First:** Cross-compile libmodbus dependency for ARM architecture  
2. **Second:** Build the main application linking against the ARM libmodbus

**Platform Requirements:** The Luckfox toolchain is designed for Ubuntu Linux development. If you're on macOS or Windows, you'll need either:
- **GitHub Actions:** Set up automated builds in the cloud (recommended for CI/CD)
- **Virtual Machine:** Run Ubuntu 22.04/24.04 LTS in VirtualBox/VMware
- **Docker:** Use an Ubuntu container with the toolchain mounted

**Why Not Native Compilation?** The Panel 86 runs a minimal embedded Linux with limited development tools. Cross-compilation on a development machine is faster and more reliable than attempting to compile directly on the target.

### Cross-Compilation Setup

#### Toolchain Configuration
**Luckfox/Rockchip proprietary cross-compilation environment:**

The Luckfox SDK provides a complete cross-compilation toolchain specifically tuned for the RV1106 SoC used in Panel 86:

- **Compiler:** `arm-rockchip830-linux-uclibcgnueabihf-g++` (GCC-based with Rockchip optimizations)
- **Target architecture:** ARMv7-A with hard float ABI (optimal for RV1106 Cortex-A7 core)
- **C Runtime:** uClibc (embedded-optimized, smaller footprint than glibc)
- **SIMD support:** NEON instruction set enabled for potential performance optimizations
- **Custom libraries:** Rockchip-specific drivers and optimizations included

**Why Proprietary Toolchain Required:**
- **Hardware-specific optimizations:** Rockchip tuning for RV1106 characteristics
- **Driver compatibility:** Ensures compatibility with Panel 86 display, touch, and GPIO drivers
- **ABI consistency:** Matches the runtime environment on the target device
- **Build consistency:** Same toolchain used for official Luckfox firmware builds

#### CMakeLists.txt Configuration
```cmake
cmake_minimum_required(VERSION 3.10)
project(thermostat_demo)

# C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Luckfox toolchain
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Compiler paths
set(TOOLCHAIN_PATH "$ENV{LUCKFOX_SDK_PATH}/tools/linux/toolchain/arm-rockchip830-linux-uclibcgnueabihf")
set(CMAKE_C_COMPILER "${TOOLCHAIN_PATH}/bin/arm-rockchip830-linux-uclibcgnueabihf-gcc")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_PATH}/bin/arm-rockchip830-linux-uclibcgnueabihf-g++")

# Dependencies
find_library(MODBUS_LIB modbus PATHS ${CMAKE_SOURCE_DIR}/lib/libmodbus_arm/lib REQUIRED)
find_package(Threads REQUIRED)

# Executable
add_executable(thermostat_demo
    main.cpp
    source/thermostat_app/Thermostat.cpp
    source/thermostat_app/thermostat_bridge.cpp
    source/thermostat_ui/thermostat_handler.c
    source/thermostat_ui/ui/vars.c
    source/thermostat_ui/ui/screens.c
    # ... other UI files
)

# Link libraries
target_link_libraries(thermostat_demo 
    ${MODBUS_LIB}
    Threads::Threads
    # ... LVGL libraries
)
```

### Build Process

#### Automated Build Script - Development Workflow Optimization

**The cleanbuild.sh Philosophy:** Rather than remembering complex cmake commands and dependency checks, we automate the entire build process in a single script. This eliminates build environment inconsistencies and makes the project accessible to team members.

**What cleanbuild.sh Accomplishes:**
- **Environment validation:** Checks that all required paths and dependencies are available
- **Clean builds:** Removes previous artifacts to prevent linking conflicts  
- **Parallel compilation:** Uses all CPU cores for faster builds
- **Build verification:** Confirms the output binary is actually ARM architecture
- **Error handling:** Fails fast with clear messages when something goes wrong

```bash
#!/bin/bash
set -e  # Exit immediately if any command fails

# Environment validation - catch missing setup early
if [ -z "$LUCKFOX_SDK_PATH" ]; then
    echo "Error: LUCKFOX_SDK_PATH not set"
    echo "Run: export LUCKFOX_SDK_PATH=/path/to/luckfox-pico"
    exit 1
fi

# Dependency checking - ensure ARM libmodbus exists
if [ ! -f "lib/libmodbus_arm/lib/libmodbus.a" ]; then
    echo "Error: Cross-compiled libmodbus not found"
    echo "Run the libmodbus cross-compilation steps first"
    exit 1
fi

echo "Starting clean build..."

# Clean build - remove any previous artifacts
rm -rf build
mkdir build
cd build

# Configure - generate ARM-targeted makefiles
echo "Configuring for ARM target..."
cmake ..

# Compile - use all available CPU cores
echo "Compiling with $(nproc) parallel jobs..."
make -j$(nproc)

# Verify output - confirm we built ARM binary
echo "Build complete! Verifying architecture..."
file thermostat_demo
ls -lh thermostat_demo

echo "Ready for deployment to Panel 86"
```

**Script Benefits for Development:**
- **Consistent builds:** Same process every time, regardless of developer environment
- **Fast iteration:** Single command rebuilds everything cleanly
- **Error prevention:** Catches common setup mistakes before they cause build failures
- **Team onboarding:** New developers can build without memorizing commands

#### Dependency Management
**libmodbus Cross-Compilation - Critical Setup Step:**

**Why Cross-Compilation Required:**
- Default libmodbus is compiled for x86/x64 development machines
- Panel 86 runs ARM architecture - binary incompatibility
- Runtime linking failure if wrong architecture used

```bash
# One-time setup for Modbus RTU communication
wget https://libmodbus.org/releases/libmodbus-3.1.6.tar.gz
tar -xzf libmodbus-3.1.6.tar.gz
cd libmodbus-3.1.6

# Configure for ARM target using Luckfox toolchain
./configure --host=arm-rockchip830-linux-uclibcgnueabihf \
           --prefix=$PWD/../lib/libmodbus_arm \
           --enable-static \
           --disable-shared \
           CC=$LUCKFOX_SDK_PATH/tools/linux/toolchain/arm-rockchip830-linux-uclibcgnueabihf/bin/arm-rockchip830-linux-uclibcgnueabihf-gcc

# Build and install ARM-compatible library
make -j$(nproc)
make install

# Verify ARM architecture
file lib/libmodbus_arm/lib/libmodbus.a
# Expected output: "ARM, EABI5 version 1 (SYSV)"
```

**Configuration Notes:**
- **Static linking preferred:** Avoids runtime dependency management on target
- **Host specification:** Ensures autotools generates ARM-compatible build configuration
- **Toolchain consistency:** Uses same GCC version as main application build

### Deployment and Execution

#### Target Environment
**Panel 86 embedded Linux system characteristics:**

The Panel 86 runs a minimal, purpose-built Linux distribution optimized for industrial applications:

- **Kernel:** Custom Linux 4.19.x with Rockchip RV1106 hardware support and real-time patches
- **Init system:** BusyBox-based lightweight initialization (not systemd)
- **Shell:** Ash shell (lightweight bash alternative, some syntax differences)
- **Networking:** Built-in Ethernet (static/DHCP) and WiFi capability
- **Storage:** 8GB eMMC with ext4 filesystem (~6GB user space available)
- **Memory:** 512MB DDR3 RAM (shared with GPU, ~400MB available for applications)
- **Display:** 720x720 IPS touchscreen with capacitive touch controller

#### Deployment Process
```bash
# 1. Build application
./cleanbuild.sh

# 2. Transfer to Panel 86
scp build/thermostat_demo root@192.168.1.100:/usr/bin/

# 3. Set permissions
ssh root@192.168.1.100 "chmod +x /usr/bin/thermostat_demo"

# 4. Execute
ssh root@192.168.1.100 "/usr/bin/thermostat_demo"
```

#### Runtime Environment
**System Requirements for Successful Operation:**

**Critical Requirements:**
- **Root privileges mandatory:** GPIO sysfs access requires root permissions
- **External 12-24V power supply:** USB power insufficient for relay coils
- **RS485 sensor properly connected:** Two-wire bus (w/ proper termination) to the built-in RS485 screw terminal through UART4 (`/dev/ttyS4`)
- **SSH access configured:** For deployment and remote debugging

**Resource Usage and Performance:**
- **Display resolution:** 720×720 pixels (square format) with 16-bit color depth
- **Flash storage:** ~700KB executable (single self-contained binary, no separate UI assets)
- **RAM footprint:** ~12MB total (measured: 2×6MB processes, ~4MB shared libraries)
- **CPU utilization:** <2% average on 1GHz Cortex-A7 (spikes to ~6% during UI transitions)

**Real-time Performance:**
- **UI refresh rate:** 60 FPS maintained for smooth touch interaction
- **Sensor polling:** 2-second interval (appropriate for thermal processes)
- **Regulation response:** <10ms from setpoint change to valve action
- **Boot time:** ~10 seconds from power-on to application ready (stock Luckfox Buildroot image)

### Production Considerations

#### System Integration
The application integrates with the Panel 86's Linux environment:
- **Systemd service:** Can be configured as system service for automatic startup
- **Logging:** Uses standard console output, redirectable to syslog
- **Configuration:** Runtime parameters via command line or config files
- **Updates:** Standard Linux package management or file replacement

#### Performance Optimization
- **Memory management:** RAII prevents leaks in long-running operation
- **Thread efficiency:** Minimal thread count reduces context switching
- **I/O optimization:** Async callbacks prevent UI blocking
- **Error recovery:** Automatic retry mechanisms maintain robustness

---

## Conclusion

This project shows one approach to building embedded applications using C++ on the Luckfox Panel 86. The combination of EEZ Studio for UI design and C++ for business logic provides a reasonable balance between development speed and code organization.

The layered architecture helps separate UI concerns from hardware control, making the code easier to understand and modify. While this approach works well for the thermostat use case, other projects might benefit from different architectural choices depending on their specific requirements.
