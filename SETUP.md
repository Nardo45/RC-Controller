## Quick start — prerequisites

- **Option A (PlatformIO, recommended):** VSCode + PlatformIO extension.
- **Option B (Arduino IDE):** Arduino IDE 1.8+/Arduino CLI with ESP32 board package installed.
- **Libraries:** `RF24` by nRF24 (also available via PlatformIO Library Manager or Arduino Library Manager).
- **Hardware:** ESP32 module (ESP32-WROOM-32D recommended), nRF24L01 module, joysticks, pressure sensors, wiring and power supply.

---

## PlatformIO setup (recommended)

1. Install VSCode and the PlatformIO extension.
2. Clone the repository:

```bash
git clone https://github.com/Nardo45/RC-Controller.git
cd RC-Controller
```

3. Example `platformio.ini` (put this in the repo root if not present, upload\_port depends on your system):

```ini
[env:esp32doit-devkit-v1]
platform = espressif32
board = esp32doit-devkit-v1
framework = arduino
upload_port = COM4
monitor_speed = 115200
lib_deps = nrf24/RF24@^1.4.11
```

4. Open the project in VSCode (PlatformIO will detect the `platformio.ini`). Select the `esp32dev` environment and click **Upload**.

---

## Arduino IDE setup

1. Install the ESP32 board support: open Boards Manager and install `esp32` (Espressif Systems).
2. Install the `RF24` library via Library Manager.
3. Open the `.ino` or main sketch file (if your project uses a `.cpp`/`.h` structure, open the top-level `.ino` that includes them or use `Sketch > Add File...`).
4. Select the correct ESP32 board and COM port, then upload.

---

## Configure and flash

1. Double-check the pin assignments in `include/CONFIG.hpp` to match your wiring.
2. Confirm the nRF24L01 address (`const byte address[6] = "9TfT0"`) and set the same address on your receiver.
3. Flash the firmware.

---

## Serial monitor

- Open the serial monitor at **115200** baud to view startup logs and debug prints. (The repo initializes `Serial.begin(115200)`.)

---

## Calibration & testing

- Confirm joystick movement is mapped to changing analog values in serial prints (add `Serial.println()` temporarily inside `joystickHandler` or `loop`).
- Check pressure sensors respond to applied force and produce varying readings.

---

## Notes & hardware tips

- nRF24L01 modules are power-hungry during transmissions; add a 10µF–47µF electrolytic capacitor close to the Vcc and GND pins of the module to stabilize the supply.
- Use short runs of wire for analog signals to reduce noise.
- If you plan to support other ESP32 modules, document the pin differences in `CONFIG.hpp`.

---

## Receiver

- Writing a compatible receiver that reads `sizeof(Payload)` into a matching struct and parses the values is the simplest approach. Ensure the radio address and radio settings (data rate, power level) match on both ends.
