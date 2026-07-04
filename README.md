# Wall Locator — ToF Obstacle & Wall Detection Board

> A custom PCB that uses a **Time-of-Flight sensor** to detect obstacles and, thanks to the sensor's 3D matrix, **tell a wall apart from any other object** — lighting an LED when an obstacle is detected.

<!-- 👇 Add the "PCB soudé" photo from your slides here — a hand-soldered board is a strong first impression -->
![Assembled PCB](docs/pcb-soldered.jpg)

---

## 🎯 Overview

Team project at **ENSEA** (Automation & Electronics), supervised by Laurent Monchal. The goal was to design a complete electronics board **from scratch**, covering the **entire chain**: schematic → PCB routing → hand soldering → embedded C firmware.

The board reads a **VL53L5CX Time-of-Flight sensor** over I²C and lights an LED when an obstacle is detected. Going further, it uses the sensor's **multizone (3D) matrix** to detect flat surfaces and distinguish a wall from an arbitrary object.

**Possible applications:** household robots (e.g. robot vacuums), automotive parking sensors.

---

## 🧩 My Role

<!-- ⚠️ 3-person team (Romane Gosselin, Hugo Mathoux, Nassim Boussaada). Be specific about what YOU did. -->
> e.g. *"I was responsible for the schematic design and C codding.

---

## 🛠️ Hardware

| Block | Component | Notes |
|-------|-----------|-------|
| Microcontroller | **STM32G431** (LQFP32) | The board's brain |
| Sensor | **VL53L5CX** Time-of-Flight | I²C, range up to **4 m**, multizone matrix |
| Memory | **EEPROM** | SDA / SCL shared with the sensor on the I²C bus |
| Power | Power LEDs + connectors | On-board supply indication |

- **PCB:** 2-layer board, **50 × 50 mm**, designed and routed in **KiCad**
- **Assembly:** hand-soldered (SMD components, including the LQFP32 MCU)

### Schematic iterations
The design went through several revisions before routing:
- Removed the DAC block and two unused connectors
- Added a dedicated **VL53L5CX** block wired to the sensor's pins
- Added an **EEPROM** block, sharing the I²C lines (SDA / SCL) with the sensor

<!-- Add a schematic screenshot and/or the KiCad 3D render here -->
![Schematic](docs/schematic.png)

---

## 💻 Firmware

Written in **C** on the STM32G431 (STM32CubeIDE project):

- Defined the full pin mapping (I²C, sensor control lines `LPn` / `PWREN` / `INT`, status LEDs)
- Integrated **ST's VL53L5CX driver/firmware** and read the sensor over **I²C**
- Lights an LED when an obstacle is present
- Exploits the sensor's **multizone matrix** to detect flat surfaces → distinguishes a **wall** from an arbitrary object

---

## 📊 Results

- ✅ Functional board detecting obstacles up to **4 m**
- ✅ **Successfully distinguishes a wall from other objects** using the sensor's 3D matrix
- ✅ Full hardware chain delivered: schematic → routed PCB → soldered board → working firmware

---

## 🧗 Challenges

<!-- Your slides flagged these — add one line of detail for each, it shows real engineering maturity -->
- **EEPROM footprint** — `[what went wrong and how you fixed it]`
- **Memory** — `[the issue you ran into]`
- **A damaged component** — `[what broke and how you recovered]`

---

## 🚀 Possible Improvements

- **Measure & display** the wall distance on a screen, using a higher-performance sensor
- **Room mapping** — use the on-board memory to build a map of the room

---

## 📁 Repository Contents

- `hardware/` — KiCad project (schematic + PCB)
- `hardware/exports/` — schematic PDF, 3D render, gerbers
- `firmware/` — C source code
- `docs/` — photos (bare & soldered board), pin mapping, notes

---

<sub>Team project · ENSEA · Romane Gosselin, Hugo Mathoux, Nassim Boussaada · supervised by Laurent Monchal</sub>
