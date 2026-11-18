# Sorting Master

# 4-DOF Auto Sorting Robot Arm

An automated 4 Degree of Freedom (4-DOF) robotic arm designed to sort objects dynamically based on color and weight, built for the Hack Club Fabricate grant.

## 📌 Project Overview
This project combines custom 3D mechanical design, a custom-designed PCB, and an ESP32 microcontroller to build an intelligent sorting station. The arm identifies incoming items using a color sensor, weighs them via a load cell, and routes them to designated bins.

## 🛠️ Key Features & Hardware
- **Microcontroller:** ESP32 (38 pin development board) handling Wi-Fi/BLE capability and real time logic.
- **Actuation:** 5x servo motors driving the base, shoulder, elbow, wrist, and gripper kinematics.
- **Sensing & Feedback:** 
  - **TCS34725:** RGB color sensor for accurate object classification.
  - **HX711:** 24 bit ADC module paired with a load cell for weight verification.
- **Power Management:** XL4015 step down buck converter stepping 12V down to a stable 5V rail for servos, supported by a 1000uF radial electrolytic capacitor for transient spike filtering.
- **Custom PCB:** Designed in KiCad with dedicated power tracks (0.75mm) and signal traces (0.25mm) plus a solid ground pour (`GND`).

## 📂 Repository Contents
- **/CAD:** Fusion 360 source files (`.f3d`) and universal STEP exports (`.step`).
- **/Hardware:** KiCad schematic, layout files, and zipped Gerber manufacturing outputs.
- **/Firmware:** Arduino/ESP32 source code for servo kinematics, color sensing, and scale calibration.
- **/Docs:** Circuit schematic PDF, Bill of Materials (BOM), and JLCPCB cart verification screenshot.

## Assembly & Replication Instructions
1. **Mechanical Build:** 3D print the structural parts from the `/CAD` folder and assemble using M3 hardware, timing belts, and pulleys.
2. **PCB Fabrication:** Upload `Hardware/Gerbers/sorting_arm_gerbers.zip` to JLCPCB along with the BOM.
3. **Flashing Firmware:** Open `/Firmware/sorting_arm_firmware.ino` in the Arduino IDE, install the required libraries (`Adafruit_TCS34725`, `HX711`), and flash to your ESP32.
