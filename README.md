# Gravity-Matrix

An interactive physics-simulation and digital sand toy powered by an ESP32, developed for **Hack Club Half-Life (Week 4: Displays)**.  
The system captures board tilt and physical impacts via a 6-axis MPU-6050 IMU and runs a real-time cellular automata sand simulation displayed on a 1.3" IPS TFT display (240x240, ST7789 driver). The core physics and bit-packing operations are written in pure C99 and cycle-optimized Xtensa LX6 assembly.

---

## Hardware & PCB Previews

### 1. 3D Render
The fully assembled board featuring the central 1.3" IPS display, top-mounted gyroscope/accelerometer breakout, and socketed ESP32 module.

![PCB 3D View](images/pcb_3d.png)

### 2. PCB Layout
Two-layer custom layout with isolated 3.3V power rails, dedicated SPI/I2C trace runs, and top/bottom ground fill planes (`GND`).

![KiCad PCB Editor](images/pcb_layout.png)

### 3. Schematic
Clean modular schematic separating the ESP32 socket headers, display bus interface, sensor connections, and decoupling capacitors.

![KiCad Schematic](images/schematic.png)

---

## Features

- **Microcontroller:** ESP32 NodeMCU (Xtensa dual-core LX6, 240 MHz, 320 KB SRAM, USB-C).
- **Display Module:** 1.3" IPS full-color screen (240x240 pixels, 65K colors, ST7789 controller via hardware SPI).
- **Inertial Sensor:** GY-521 Breakout (MPU-6050 3-axis accelerometer + 3-axis gyroscope via Fast-Mode I2C).
- **Low-Level Simulation Engine:** Real-time cellular automata sand physics with momentum, obstacle bouncing, and shock agitation.
- **Assembly Optimizations:** Native Xtensa LX6 assembly routines (`.S`) for cycle-accurate bit-reversal and rapid buffer mixing.
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

## Firmware Architecture & Implementation

Development is carried out in **VS Code** using **PlatformIO** with a focus on bare-metal execution:
- [x] Universal automated Git sync script (`sync.sh`).
- [x] MPU-6050 direct raw register polling over I2C bus (Registers `0x3B`–`0x40`).
- [x] Particle cellular automata engine implemented in pure C (`physik.c`).
- [x] Xtensa LX6 assembly primitives for bit-reversal and buffer agitation (`bit_asm.S`).
- [ ] ST7789 bare-metal SPI initialization and command transmission sequence.
- [ ] Scaled particle block renderer ($4 \times 4$ pixel grain scaling).
- [ ] Final end-to-end integration test on physical hardware.
