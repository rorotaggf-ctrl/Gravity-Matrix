# Gravity-Matrix

An interactive physics simulation, digital sand toy, and graphical desk instrument powered by an ESP32, developed for **Hack Club Half-Life (Week 4: Displays)**.  
The system captures board tilt and physical impacts via a 6-axis MPU-6050 IMU and drives a 1.3" IPS TFT display (240x240, ST7789 controller via SPI). The firmware features an interactive tilt menu, a real-time cellular automata sand simulation with dynamic avalanche collision handling, and a trigonometric analog clock GUI with flicker-free differential rendering.

---

## Features

- **Microcontroller:** ESP32 NodeMCU (Xtensa dual-core LX6, 240 MHz, 320 KB SRAM, USB-C).
- **Display Module:** 1.3" IPS full-color screen (240x240 pixels, 65K colors, ST7789 controller via hardware SPI).
- **Inertial Sensor:** GY-521 Breakout (MPU-6050 3-axis accelerometer + 3-axis gyroscope via Fast-Mode I2C at 400 kHz).
- **Cellular Automata Sand Engine:** Real-time 60x60 particle simulation ($4 \times 4$ pixel grain scaling) calculating gravity slip, granular resting angles, and shake agitation.
- **Trigonometric Analog Clock GUI:** Real-time geometric watchface with trigonometric ($sin / cos$) hand vectoring and differential rendering (erasing and drawing only modified vectors to eliminate display flicker).
- **Tilt-Controlled Menu System:** Gesture-driven UI allowing mode selection via pitch/roll tilt and shake gestures without physical buttons.
- **Power Delivery:** Powered directly via the USB-C port with ceramic decoupling capacitors (100nF) on peripheral rails.
- **Modular Sockets:** All major components mount into 2.54mm female pin headers for serviceability.

---

## Pinout Configuration

| Component | Pin Label | ESP32 Pin / GPIO | Protocol / Function | Description |
| :--- | :--- | :--- | :--- | :--- |
| **ST7789 Display** | GND | GND | Power | Ground connection |
| **ST7789 Display** | VCC | 3V3 | Power | 3.3V Logic & Driver Power |
| **ST7789 Display** | SCL | GPIO 18 | VSPI SCK | Hardware SPI Clock |
| **ST7789 Display** | SDA | GPIO 23 | VSPI MOSI | Hardware SPI Master Out |
| **ST7789 Display** | RES | GPIO 4 | GPIO Output | Hardware Reset Line |
| **ST7789 Display** | DC | GPIO 2 | GPIO Output | Data / Command Selection |
| **ST7789 Display** | BLK | 3V3 | Power | Backlight Constant Enable |
| **MPU-6050 Sensor** | VCC | 3V3 | Power | Sensor Core Power |
| **MPU-6050 Sensor** | GND | GND | Power | Ground connection |
| **MPU-6050 Sensor** | SCL | GPIO 22 | I2C SCL | Fast-Mode I2C Clock (400 kHz) |
| **MPU-6050 Sensor** | SDA | GPIO 21 | I2C SDA | Fast-Mode I2C Data |

---

## Bill of Materials (Grant Funded)

> [!NOTE]
> This parts list covers items funded via Hack Club Half-Life ($30.00 Tier 1 Limit).

| Part | What it's for | Qty | Price (USD) | Price (EUR) | Vendor | Purchase Link |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| Fasizi 1.3" IPS TFT Display (ST7789) | Primary visual display for cellular automata | 1 | $7.83 | 6,99 € | Amazon | [Amazon Link](https://www.amazon.de/dp/B09Z299F3Q) |
| ICQUANZX GY-521 MPU6050 Sensor | 6-axis tilt and acceleration tracking | 1 | $6.71 | 5,99 € | Amazon | [Amazon Link](https://www.amazon.de/dp/B07P963VNL) |
| ESP32 NodeMCU WROOM-32E Dev Board | Main computational processor | 1 | $5.03 | 4,49 € | eBay | [eBay Link](https://www.ebay.de/itm/157477097103) |
| Domestic Shipping (Germany) | Tracked delivery for ESP32 | 1 | $3.35 | 2,99 € | eBay | [eBay Link](https://www.ebay.de/itm/157477097103) |
| Gtziqa 100nF Ceramic Capacitors (150-Pack) | Power supply decoupling & noise filtering | 1 | $6.26 | 5,59 € | Amazon | [Amazon Link](https://www.amazon.de/dp/B0CX1TV9G7) |
| **Total Grant Cost** | | | **$29.18** | **26,05 €** | | |

*Remaining Tier 1 Budget: $0.82*

---

## Additional Self-Funded Components

> [!IMPORTANT]
> The following items are self-funded or sourced from existing workshop inventory to keep the project strictly within the grant limits.

| Part | What it's for | Qty | Price (USD) | Price (EUR) | Vendor | Purchase Link |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| Custom 2-Layer PCB (5 copies) | Mainboard carrier PCB | 1 | $8.10 | 7,23 € | JLCPCB | [JLCPCB Quote](https://jlcpcb.com/quote) |
| PCB Shipping (Standard Line) | Delivery to Germany | 1 | $9.55 | 8,53 € | JLCPCB | [JLCPCB Quote](https://jlcpcb.com/quote) |
| Female Pin Headers 2.54mm | Sockets for ESP32 and modules | 1 | $0.00 | 0,00 € | Inventory | Existing parts |
| M3 Standoffs & Screws | Mechanical mounting hardware | 4 | $0.00 | 0,00 € | Inventory | Existing parts |
| **Total Self-Funded** | | | **$17.65** | **15,76 €** | | |

---

## Hardware Design & Schematics

### KiCad Schematic View
Complete circuit diagram connecting the ESP32 NodeMCU socket headers to the SPI display bus, fast-mode I2C accelerometer, and rail decoupling capacitors.

<img width="3371" height="1261" alt="KiCad Schematic" src="https://github.com/user-attachments/assets/deabe9f8-225d-437d-81bb-2b6437762164" />

### KiCad PCB Layout & Trace Routing
Two-layer carrier board layout with routed differential SPI/I2C signals, optimized component placement, and ground plane fills on both layers.

<img width="2831" height="1227" alt="KiCad PCB Layout" src="https://github.com/user-attachments/assets/fabf514f-839e-4193-8992-44ffca825b46" />

---

## Firmware Architecture & Implementation

Development is carried out in **VS Code** using **PlatformIO** and the Espressif 32 framework, organized in a modular structure:

- **`config.h`:** Global pin definitions for hardware SPI (GPIO 18, 23, 2, 4) and I2C buses (GPIO 21, 22), screen dimensions, and RGB565 color definitions.
- **`imu.h` / `imu.cpp`:** Direct-register I2C driver for MPU-6050 streaming raw 3-axis acceleration and tilt data without high overhead.
- **`sand_view.h` / `sand_view.cpp`:** Real-time falling sand simulation executing on a 60x60 grid with selective pixel differential drawing for flicker-free 30+ FPS refresh rates.
- **`clock_view.h` / `clock_view.cpp`:** Analog watchface GUI calculating hand positions trigonometrically ($sin / cos$) with selective line redraws to prevent full-screen redraw artifacts.
- **`menu_view.h` / `menu_view.cpp`:** Tilt-driven selection state machine navigating between instruments via real-time roll/pitch thresholds.
- **`main.cpp`:** Central execution loop orchestrating sensor updates and instrument transitions.

### Development Status
- [x] Universal automated Git sync scripts (`sync.sh` / `sync.ps1`).
- [x] MPU-6050 direct raw register polling over I2C bus (Registers `0x3B`–`0x40`).
- [x] Modular hardware configuration and display initialization via SPI.
- [x] Real-time cellular automata particle engine with avalanche sliding.
- [x] Trigonometric analog clock GUI with flicker-free differential line updates.
- [x] Tilt and shake gesture navigation state machine.
- [ ] Final integration run on physical carrier board.

### Firmware Source Snapshots
<img width="1669" height="810" alt="Code Snippet 1" src="https://github.com/user-attachments/assets/2f483256-e911-404a-9508-ed5a127ce95b" />
<img width="1667" height="797" alt="Code Snippet 2" src="https://github.com/user-attachments/assets/e5b32698-0fe6-49f9-b2c3-e91807cf2a00" />
<img width="1667" height="813" alt="Code Snippet 3" src="https://github.com/user-attachments/assets/7752784d-199b-4b3a-bdfd-14e52e5a3968" />
<img width="1240" height="788" alt="Code Snippet 4" src="https://github.com/user-attachments/assets/0ea33e48-313b-479d-9821-d3e32cc48239" />