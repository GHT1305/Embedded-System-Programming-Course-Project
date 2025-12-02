# Designing an Automatic Temperature Control for Vehicle (ATC) - Final Project

**Course:** Embedded System Programming (EE3031)  
**Semester:** 1 – Academic year: 2025–2026  
**Lecturer:** Bui Quoc Bao  
**Student:** Tran Vu Gia Huy (ID: 2252267)

## Project Objective

Design, simulate, and implement an automatic temperature control system for automobiles.  
The system measures the cabin temperature using a DS18B20 sensor and automatically controls a cooling fan based on a user‑defined set temperature shown on an LCD display.

## Hardware Components

- STM32F103C8T6 “Blue Pill” board  
- DS18B20 digital temperature sensor (1‑Wire)  
- 16x2 character LCD (HD44780 compatible)  
- DC cooling fan with driver (transistor/MOSFET/relay)  
- 3 push buttons:
  - SET – enter/exit temperature setting mode
  - UP – increase set temperature
  - DOWN – decrease set temperature
- Status LED (indicates fan state)  
- Power supply and basic passive components (resistors, jumpers, etc.)

## System Features

### Power‑up Behavior

- On power‑up, the STM32 initializes the clock, GPIO, DS18B20 driver, and LCD.  
- A splash screen with course code and student information is displayed, followed by a welcome screen “CAR ATC V1.0”.  
- After initialization, the system enters normal run mode and shows temperature, set temperature, and fan status.

### Normal Mode (Run Mode)

- The microcontroller periodically reads the current temperature from the DS18B20 sensor.  
- The LCD displays:
  - Line 1: `TEMP   SET   FAN`
  - Line 2: current temperature, set temperature, and fan status (`ON` or `OFF`).
- Fan control logic:
  - If measured temperature `temp >= temp_set` → fan turns ON and the LED is ON.
  - If measured temperature `temp < temp_set` → fan turns OFF and the LED is OFF.

### Setting Mode

- When the user presses the SET button in normal mode, the system switches to “SET TEMP MODE”.  
- The LCD shows:
  - Line 1: `SET TEMP MODE`
  - Line 2: the adjustable set temperature value.
- While in setting mode:
  - Press UP to increase `temp_set` by 1 °C.
  - Press DOWN to decrease `temp_set` by 1 °C.
  - The set temperature is limited between `temp_set_min` and `temp_set_max` (for example, 15 °C to 35 °C).
  - The LCD is updated immediately whenever UP or DOWN is pressed.
- Press SET again to:
  - Exit setting mode.
  - Return to normal mode with the new `temp_set` value applied for fan control.

*(Optionally, the final `temp_set` value can be stored in non‑volatile memory so that it is restored after power‑cycle.)*

## User Manual

### Operating the System

1. Power the STM32 Blue Pill and connected circuitry.  
2. Wait for the splash and welcome screens to complete.  
3. Observe the main screen showing:
   - Current cabin temperature (TEMP).
   - User set temperature (SET).
   - Fan status (FAN: ON/OFF).

### Adjusting the Set Temperature

1. In normal mode, press the SET button once to enter “SET TEMP MODE”.  
2. Use:
   - UP button to increase the set temperature.
   - DOWN button to decrease the set temperature.
3. When the desired set temperature is reached, press SET again to:
   - Exit setting mode.
   - Return to the main screen, where the fan now operates according to the new setpoint.

### Automatic Fan Control

- The fan runs fully automatically according to the measured temperature:
  - If the cabin temperature is greater than or equal to the set temperature, the fan turns ON to cool the cabin.
  - If the cabin temperature is below the set temperature, the fan turns OFF to save energy.

## Troubleshooting

- LCD is blank:
  - Check power supply for LCD and STM32.
  - Verify LCD data/control pin connections and contrast setting.
  - Ensure `LCD_Init()` is called correctly in the firmware.

- Temperature reading is always 0 °C or incorrect:
  - Check DS18B20 wiring: VDD, GND, DQ, and the pull‑up resistor (typically 4.7 kΩ) on the 1‑Wire data line.
  - Confirm that the configured GPIO pin for the 1‑Wire bus matches the pin used in the code.

- Fan does not run when LCD shows FAN = ON:
  - Check the FAN control pin connection from STM32 to the driver circuit.
  - Verify the driver (transistor/MOSFET/relay) wiring and that the fan’s power supply is present.
  - Ensure all grounds are common between STM32 and the fan power supply.

- Buttons do not respond or behave unexpectedly:
  - Confirm that SET, UP, and DOWN pins are configured as input with pull‑up resistors.
  - Check that push buttons properly pull the input pins to ground when pressed.
  - Inspect for loose or incorrect wiring on the button connections.
