# Gravity-Matrix

An interactive physics simulation and digital sand toy powered by an ESP32 NodeMCU, developed for **Hack Club Half-Life (Week 4: Design with Displays)**.

The project simulates individual sand grains rolling and settling on an 8x8 LED matrix display driven by a MAX7219 controller. An MPU-6050 6-axis IMU reads real-time gravity and tilt vectors, while a custom lightweight cellular-automata engine computes realistic particle collisions, avalanche slipping, and shake inertia on the microcontroller.

---

## Hardware Architecture & Design

### Concept & Schematic Layout
![Hardware Concept Sketch](images/concept_sketch.png)
*Initial hardware block diagram showing SPI display bus, I2C IMU routing, and decoupling topology.*

### PCB & 3D Previews
![3D Board View](images/pcb_3d.png)
*Render of the custom 2-layer carrier board seating the ESP32 NodeMCU, LED matrix, and sensor module.*

![KiCad PCB Editor](images/pcb_layout.png)
*Complete board layout designed in KiCad with continuous ground planes and short SPI/I2C trace runs.*

---

## Features

- **Microcontroller:** ESP32-WROOM-32E (Dual-Core 240 MHz, 4MB Flash, USB-C)
- **Display Module:** MAX7219 Red 8x8 Dot Matrix (64 individually addressable LEDs via hardware SPI)
- **Motion Sensor:** GY-521 Breakout Board (InvenSense MPU-6050 6-DOF Accelerometer & Gyroscope via I2C)
- **Real-Time Physics:** Cellular automata algorithm running at 25 Hz with avalanche gravity slipping and collision resolution
- **Interactive Gestures:** Dynamic inertia calculations detecting physical shaking to disperse and randomize settled particles
- **Decoupling Protection:** Onboard 100nF ceramic capacitor mitigating switching transients and SPI line ripple
- **Modular Hardware:** Through-hole 2.54 mm socket headers allowing all modules to be swapped without desoldering

---

## Pinout Configuration

| Component | Pin Function | ESP32 GPIO | Bus / Protocol | Notes |
| :--- | :--- | :--- | :--- | :--- |
| **MAX7219 Matrix** | DIN (MOSI) | GPIO 23 | Hardware VSPI | Serial data input to shift register |
| **MAX7219 Matrix** | CLK (SCK) | GPIO 18 | Hardware VSPI | Shift register clock |
| **MAX7219 Matrix** | CS / LOAD | GPIO 5 | GPIO Output | Latch enable (Active LOW) |
| **MAX7219 Matrix** | VCC | 5V / VIN | Power | 5V supply rail |
| **MAX7219 Matrix** | GND | GND | Ground | Common system ground |
| **GY-521 MPU-6050** | SDA | GPIO 21 | I2C Data | 400 kHz fast-mode bus line |
| **GY-521 MPU-6050** | SCL | GPIO 22 | I2C Clock | Bus clock line |
| **GY-521 MPU-6050** | VCC | 3V3 / 5V | Power | Onboard LDO input rail |
| **GY-521 MPU-6050** | GND | GND | Ground | Common system ground |

---

## Bill of Materials (Grant Funded)

> [!NOTE]
> This parts list covers items funded via Hack Club Half-Life ($30.00 Tier 1 Limit). For the synchronized platform file, see `BOM.csv`.

| Part | What it's for | Qty | Price (USD) | Price (EUR) | Vendor | Purchase Link |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 7219 MAX Dot Matrix 8x8 Modul | Sand and particle LED matrix display | 1 | $7.27 | 6,49 € | Amazon | [Amazon Link](https://www.amazon.de/dp/B0B49JCNPS) |
| ICQUANZX GY-521 MPU6050 Modul | 6-DOF gravity vector and tilt sensing | 1 | $6.71 | 5,99 € | Amazon | [Amazon Link](https://www.amazon.de/dp/B07P963VNL) |
| ESP32 NodeMCU WROOM-32E | Physics simulation engine & SPI master | 1 | $5.03 | 4,49 € | eBay | [eBay Link](https://www.ebay.de/itm/157477097103) |
| eBay Tracked Shipping | Fast domestic shipping from Berlin | 1 | $3.35 | 2,99 € | eBay | [eBay Link](https://www.ebay.de/itm/157477097103) |
| Gtziqa 100nF Capacitors (150-Pack) | VCC & SPI decoupling noise filtering | 1 | $6.26 | 5,59 € | Amazon | [Amazon Link](https://www.amazon.de/dp/B0CX1TV9G7) |
| **Total Grant Cost** | | | **$28.62** | **25,55 €** | | |

*Remaining Tier 1 Budget: $1.38*

---

## Additional Self-Funded Components

> [!IMPORTANT]
> The following components are funded personally or sourced from existing workshop inventory to complete the build without exceeding the Hack Club Tier 1 grant limit ($30.00).

| Part | What it's for | Qty | Price (USD) | Price (EUR) | Vendor | Purchase Link |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| Custom 2-Layer PCB (5 copies) | Main carrier PCB for LED matrix and ESP32 | 1 | $8.10 | 7,23 € | JLCPCB | [JLCPCB Quote](https://jlcpcb.com/quote) |
| PCB Tracked Shipping | Standard tracked delivery to Germany | 1 | $9.55 | 8,53 € | JLCPCB | [JLCPCB Quote](https://jlcpcb.com/quote) |
| Female Pin Headers 2.54mm | Sockets for modular ESP32 mounting | 2 | $0.00 | 0,00 € | Inventory | Existing parts |
| M3 Stand-offs & Screws | Board elevation and mounting | 4 | $0.00 | 0,00 € | Inventory | Existing parts |
| **Total Self-Funded** | | | **$17.65** | **15,76 €** | | |

---

## Firmware Architecture

Built in **VS Code** with PlatformIO using the Espressif 32 Arduino framework.

- **`matrix.h` / `matrix.cpp`:** Bitbang/Hardware SPI register driver for the MAX7219 IC (Scan Limit 8, Normal Operation, Brightness mapping, direct row byte streaming).
- **`sensor.h` / `sensor.cpp`:** Low-level I2C communication with MPU-6050, converting raw 16-bit register reads into discrete directional vectors and sudden delta shock detection.
- **`physik.h` / `physik.cpp`:** Custom 8x8 cellular automata simulation running full diagonal/vertical slip evaluation, granular stacking, and random noise dispersion.
- **`main.cpp`:** Central execution loop operating at a fixed 40 ms tick rate with zero heap allocation.

### Development Status
- [x] Hardware concept sketch & pinout definition
- [x] Bill of Materials (Grant + Self-funded breakdown)
- [ ] KiCad schematic and PCB trace routing
- [ ] PCB Gerber export and DRC validation
- [ ] Firmware engine integration and tilt testing
- [ ] Final assembly and soldering verification
