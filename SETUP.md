# Quick start — prerequisites

- **PlatformIO (required)** — either:
  - **PlatformIO IDE for VSCode** (recommended for a friendly UI), or  
  - **PlatformIO Core (CLI)** for command-line usage (works on Linux / macOS / Windows / ARM).
- **Libraries:** `RF24` (available via PlatformIO Library Manager as `nrf24/RF24`).
- **Hardware:** ESP32 module (ESP32-WROOM-32D recommended), nRF24L01 module, joysticks, pressure sensors, wiring and power supply.

---

## Install PlatformIO

### Option 1 — VSCode + PlatformIO IDE (easy GUI)
1. Install Visual Studio Code.
2. Open Extensions → search for **PlatformIO IDE** and install. PlatformIO IDE bundles PlatformIO Core so no separate Core install is required. :contentReference[oaicite:0]{index=0}

### Option 2 — PlatformIO Core (CLI)
If you prefer working in a terminal (or using CI), install PlatformIO Core. Two common methods:

- **Installer script (recommended)** — creates an isolated environment for PlatformIO Core (avoids system Python issues). See the installer repo/docs. Example usage:

```bash
# download installer script and run with python3
curl -fsSL https://raw.githubusercontent.com/platformio/platformio-core-installer/master/get-platformio.py -o get-platformio.py
python3 get-platformio.py
````

* **pip (PyPI)** — installs platformio into your Python environment:

```bash
python3 -m pip install -U platformio
```

After install, verify:

```bash
pio --version
```

(Official docs: installation and pip instructions). ([GitHub][1])

---

## Clone the repo

```bash
git clone https://github.com/Nardo45/RC-Controller.git
cd RC-Controller
```

---

## `platformio.ini` (project config)

Place this file at the repository root (you already have one — confirm it contains the right settings). Example (yours):

```ini
; PlatformIO Project Configuration File

[env:esp32doit-devkit-v1]
platform = espressif32
board = esp32doit-devkit-v1
framework = arduino
upload_port = COM4    ; Depends on your system (optional — PlatformIO can auto-detect)
monitor_speed = 115200
lib_deps = nrf24/RF24@^1.4.11
```

Notes:

* `framework = arduino` means the ESP32 Arduino core is used as the runtime, but **this does not require the Arduino IDE** — PlatformIO handles the toolchain and library installation. ([docs.platformio.org][2])
* Remove or change `upload_port` if you prefer auto-detection, or set it to `/dev/ttyUSB0` (Linux) or `COM3` (Windows) for your environment.

---

## Build & flash (examples)

### Using VSCode (PlatformIO IDE)

* Open the project folder in VSCode. PlatformIO will detect `platformio.ini`.
* Use the PlatformIO toolbar or the left-side PlatformIO panel to **Build**, **Upload**, and open the **Serial Monitor**.

### Using the CLI (PlatformIO Core)

From the repo root:

```bash
# build (default environment)
pio run

# build and upload to board (auto-detects port if not set)
pio run -t upload

# target a named environment (if you have multiple environments)
pio run -e esp32doit-devkit-v1 -t upload
```

Helpful device/monitor commands:

```bash
# list connected devices / serial ports
pio device list

# open serial monitor (auto-detects port and uses monitor_speed)
pio device monitor --baud 115200
# or explicitly:
pio device monitor -p /dev/ttyUSB0 -b 115200
```

(PlatformIO CLI docs: build/upload/monitor commands). ([docs.platformio.org][3])

---

## Configure and flash

1. Edit `include/CONFIG.hpp` to match your wiring and pin choices.
2. Confirm the nRF24L01 radio address (e.g. `const byte address[6] = "9TfT0"`) and set the same address on the receiver.
3. Build and upload using VSCode PlatformIO or the CLI (`pio run -t upload`).

---

## Serial monitor & debugging

* Open the serial monitor at **115200** to view boot logs and debug output.
* If the port is not detected automatically, use `pio device list` to find the correct device name and pass `-p` to `pio device monitor`.

---

## Calibration & testing

* Add temporary `Serial.println()` calls in `joystickHandler` or `loop` to verify analog mappings.
* Verify pressure sensors change readings when force is applied.

---

## Notes & hardware tips

* nRF24L01 modules require a stable 3.3V supply during TX bursts — add a 10µF–47µF electrolytic capacitor close to the module Vcc and GND pins.
* Keep analog signal wiring short to reduce noise.
* If you want to support other ESP32 modules, document alternate pin assignments in `CONFIG.hpp`.

---

## Receiver

* Implement a receiver that reads `sizeof(Payload)` into the same struct layout you use on the controller and parse fields accordingly.
* Make sure radio settings (address, data rate, power level) match on both ends.

---

## Troubleshooting

* If PlatformIO fails to install components inside VSCode, open the PlatformIO terminal (View → Terminal) and try `pio update` or install PlatformIO Core manually (see **Option 2**). ([PlatformIO Community][4])
* If upload fails with `No such file` or `device busy`, check that no other application (e.g., serial terminal) is holding the port, and that you selected the correct board environment in `platformio.ini`.

---

## Appendix — Useful CLI commands (quick list)

```bash
pio --version
pio run
pio run -t upload
pio run -e <env> -t upload
pio device list
pio device monitor -p <port> -b 115200
pio lib install "nrf24/RF24"
```

(See PlatformIO docs for more advanced options and CI integration). ([docs.platformio.org][5])

[1]: https://github.com/platformio/platformio-core-installer?utm_source=chatgpt.com "PlatformIO Core Installer"
[2]: https://docs.platformio.org/en/latest/core/installation/index.html?utm_source=chatgpt.com "Installation — PlatformIO latest documentation"
[3]: https://docs.platformio.org/en/latest/core/userguide/project/cmd_init.html?utm_source=chatgpt.com "pio project init — PlatformIO latest documentation"
[4]: https://community.platformio.org/t/installation-of-platformio-in-vs-code-problem/46656?utm_source=chatgpt.com "Installation of PlatformIO in VS Code problem"
[5]: https://docs.platformio.org/en/latest/core/userguide/index.html?utm_source=chatgpt.com "CLI Guide — PlatformIO latest documentation"
