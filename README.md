# BCM Button Analysis PCB

A compact 2-layer PCB developed for anticipation-based clinical studies at Baylor College of Medicine. Designed for low-noise human-input capture with sub-100 ms latency and reliable USB serial output.

## Hardware Overview
- **MCU:** ATmega32U4 (native USB)
- **Inputs:**
  - BNC connectors for shielded photoresistor signal input and signal output to oscilloscope
  - Terminal blocks for buttons
- **Power:** USB 5V with onboard regulation
- **PCB:** 2-layer, KiCAD design, ~20 components assembled
- **Purpose:** Stable, low-latency human-input acquisition

## Key Features
- De-bounced and filtered input capture
- Clean analog/digital separation for noise reduction
- Robust, lab-friendly connector interfaces
- Oscilloscope-verified timing and signal integrity

## Firmware Summary
- C/C++ polling loop at regular intervals
- Detection of button presses and light-level changes
- USB serial logging with timestamps
- Reliable event timing for clinical data collection

<img width="1323" height="834" alt="BCM PCB Pic 2" src="https://github.com/user-attachments/assets/bcb3697f-509b-4646-8d46-74654e4de212" />
