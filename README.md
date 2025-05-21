![luckfox](https://github.com/LuckfoxTECH/luckfox-pico/assets/144299491/cec5c4a5-22b9-4a9a-abb1-704b11651e88)
# Luckfox Pico LVGL example
[中文](./README_CN.md)
+ This example is based on lvgl-8.3 for designing the interface.
+ This example uses lv_driver-8.1 to drive display and input devices.
+ A graphical interface development example specifically for the `Luckfox Pico 86Panel` series development boards.

## Platform Support
| Model              | Operating System | Resolution | Network Interface |
|--------------------|------------------|------------|-------------------|
| Luckfox Pico 86 Panel | Buildroot | 720x720 | Ethernet |
| Luckfox Pico 86 Panel W | Buildroot | 720x720 | Ethernet/Wi-Fi |

## Implementation Results
![LVGL_main](images/86UI_Demo.png)

## Interface Introduction
+ **Time**: Display time and date on the main interface, automatically synchronized after networking
+ **Wi-Fi**: Click to enter network configuration, click `Scan` to scan networks and enter Wi-Fi SSID and password. This button will not respond on Luckfox Pico 86 Panel.
+ **Music**: Swipe down on the main interface to enter the music playback interface, supports only `.mp3` format. Music files need to be placed in `/music` directory.
+ **Relay**: Control onboard relay

## Buildroot
### Compilation
+ Set environment variables:
    ```
    export LUCKFOX_SDK_PATH=<path_to_luckfox-pico_sdk>
    ```
    **Note:** Use absolute paths.

+ Compile with CMake to obtain the executable:
    ```
    mkdir build
    cd build
    cmake ..
    make -j
    ```

### Running
+ Upload the compiled executable `86UI_Demo` to the Luckfox Pico (using adb, ssh, or other methods).
+ Close the default running `86UI_Demo` program:
    ```
    killall 86UI_Demo
    ```
+ Set executable permissions and run:
    ```
    chmod a+x 86UI_Demo
    ./86UI_Demo
    ```
+ The factory program `/usr/bin/86UI_Demo` will start automatically at boot.
