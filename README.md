## Project summary

**RC-Controller** is a compact ESP32-based remote controller for radio-controlled vehicles and projects. It reads two analog joysticks and two thin-film pressure sensors, packages the data into a small `Payload` struct, and sends it over an nRF24L01 transceiver. The codebase is intended to be minimal, easy to adapt, and friendly to PlatformIO and Arduino IDE users.

---

## Status

- Hardware:  ESP32-WROOM-32D
- Firmware: Working basic telemetry and transmit path implemented

---

## Features

- Reads two full analog joysticks (HW-504 compatible wiring)
- Two analog thin-film pressure sensors for triggers
- Debounced push buttons (joystick switches) using `INPUT_PULLUP`
- Packets transmitted via nRF24L01 using `RF24` library
- Simple, single-file payload definition for easy receiver integration

---

## Hardware (what I used)

- **MCU:** ESP32-WROOM-32D (other ESP32 modules with similar pinouts will work but may need pin adjustments)
- **Joysticks:** HW-504 (two units). Other joysticks OK if they follow the same pinout (two analog axes + push switch).
- **Triggers / pressure sensors:** 2× thin-film resistive sensors (10 kg) wired as voltage dividers with a 10K pull-down resistor.
- **Radio:** nRF24L01 (2.4 GHz transceiver)
- **Power:** 3.3V supply for ESP32 and nRF24L01 (nRF24 modules are sensitive to supply noise, add decoupling or a separate regulator if unstable)

---

## Pinout (from `CONFIG.hpp`)

- `JOY1_VRx_PIN` — GPIO36 (analog) — Joystick 1 X

- `JOY1_VRy_PIN` — GPIO39 (analog) — Joystick 1 Y

- `JOY1_SW_PIN`  — GPIO25 (digital input, `INPUT_PULLUP`) — Joystick 1 push button

- `JOY2_VRx_PIN` — GPIO34 (analog) — Joystick 2 X

- `JOY2_VRy_PIN` — GPIO35 (analog) — Joystick 2 Y

- `JOY2_SW_PIN`  — GPIO26 (digital input, `INPUT_PULLUP`) — Joystick 2 push button

- `PRESS_SENSOR_1_PIN` — GPIO33 (analog) — Pressure sensor 1

- `PRESS_SENSOR_2_PIN` — GPIO32 (analog) — Pressure sensor 2

- `NRF_CE_PIN` — GPIO2  — nRF24L01 CE

- `NRF_CSN_PIN` — GPIO15 — nRF24L01 CSN (chip select)

> Note: These pin assignments come directly from the project `CONFIG.hpp`. If you change the board or wiring, update that header.

---

## Payload struct

The code uses a packed `Payload` structure defined in `CONFIG.hpp` that contains the following fields:

```cpp
struct Payload {
  int16_t joy1X;
  int16_t joy1Y;
  bool joy1Button;
  int16_t joy2X;
  int16_t joy2Y;
  bool joy2Button;
  int16_t pressSens1;
  int16_t pressSens2;
};
```

- Analog reads on the ESP32 return 0–4095 by default. The project stores those raw values into `int16_t` fields — be mindful of range if you change data types or add mapping/scaling.

---

## Wiring notes

- **Joysticks (HW-504):** typically expose VRx, VRy (two potentiometer outputs) and a push switch. Connect VRx/VRy to the analog pins above, switch to the configured digital pin (with `INPUT_PULLUP` in software), and Vcc/GND to 3.3V/GND.

- **Thin-film pressure sensors (flexible FSR style):** wired as voltage dividers. One side of the sensor goes to 3.3V, the other side goes to a junction that connects to the ESP32 analog input through a 10K resistor; the junction also connects to ground through the 10K resistor. This creates a readable analog voltage proportional to applied pressure. (The project’s sensors are described: one side positive, the other to a junction with 10K to ground and the analog line in between.)

- **nRF24L01:** use the module’s 3.3V pin (NOT 5V) and provide sufficient decoupling (a 10µF electrolytic across Vcc and GND near the module is recommended). Connect CE to `NRF_CE_PIN` and CSN to `NRF_CSN_PIN`. SCK, MOSI, MISO use the ESP32's hardware SPI pins (default SPI pins on most ESP32 dev modules).

---

## Software / libraries

- Firmware is written for the Arduino framework on ESP32.
- Uses `RF24` (nRF24) library for nRF24L01 communication.
- Compatible with both PlatformIO and the Arduino IDE. Example `platformio.ini` snippet is included in `SETUP.md`.

---

## How to use

1. Follow the setup instructions in `SETUP.md` to install dependencies, configure, and flash the firmware.
2. Power the controller and ensure the receiver is configured with the same nRF24L01 address (`const byte address[6] = "9TfT0"` in `main.cpp`) and packet structure.
3. Use the serial monitor at 115200 baud for debug output (the sketch initializes `Serial.begin(115200)` in `setup`).

---

## Calibration & mapping

- The code currently sends raw analog values. You may want to map those values to a smaller range (e.g., -1000..1000 or -127..127) on either the controller or the receiver depending on your receiver code.
- Add deadzones to joystick axes in `joystickHandler` if you observe jitter around center.

---

## Troubleshooting

- **Radio not transmitting:** confirm CE/CSN wiring, correct address on receiver, and that the nRF24L01 has a stable 3.3V supply. Add a capacitor across Vcc/GND near the module.
- **Noisy analog reads:** add a small delay, remove long signal wires, add shielding, or put a small RC filter on analog lines. Consider averaging multiple reads.
- **Buttons read inverted:** code uses `INPUT_PULLUP`, so `LOW` typically means pressed.

---

## Contribution & license

This project is my personal project and I’m the solo developer. If you want collaboration, open an issue or a PR. Include a clear description and test steps.

LGPLv3. See [LICENSE.md](LICENSE.md) for details.

---

## Future work / TODO

- Add buttons
- Add CRC/checksum to payload
- KiCad schematics and PCB layout
