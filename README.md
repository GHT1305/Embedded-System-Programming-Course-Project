# Designing a Thermostat for Cars - Final Project

**Course:** Embedded System Programming (EE3031)  
**Semester:** 1 – Academic year: 2025–2026  
**Lecturer:** Bui Quoc Bao  
**Student:** Tran Vu Gia Huy (ID: 2252267)

<img width="1462" height="691" alt="Screenshot 2025-12-02 110435" src="https://github.com/user-attachments/assets/91becaae-d1ab-4ec6-b7ac-efb52e9b22f2" />

## Project Objective

Design, simulate, and implement an automatic temperature control system for automobiles.  
The system measures the cabin temperature using a DS18B20 sensor, STM32 microcontroller and automatically controls a cooling fan based on a user‑defined set temperature shown on an LCD display.

## Hardware Components

- STM32F103C8T6 microcontroller 
- DS18B20 digital temperature sensor (1‑Wire)  
- LCD 16x2  
- DC cooling fan 
- 3 push buttons:
  + SET – enter/exit temperature setting mode
  + UP – increase set temperature
  + DOWN – decrease set temperature
- Status LED 

## Software Tools

- STM32CubeIDE (Version 1.19.0)
- Proteus (Version 8.17)

## System Features

- On power‑up, a welcome message is shown on the LCD and the LED blinks to indicate that the system has started successfully.
- After initialization, the system enters display mode and shows temperature from the DS18B20 sensor, set temperature, and fan status 'ON / OFF'.
- If the measured temperature "is higher than or equals the set temperature" → fan turns ON and the LED is ON. Otherwise, if the measured temperature "is lower than the set temperature" → fan turns OFF and the LED is OFF.
- When the user presses the SET button in display mode, the system switches to “SET TEMPERATURE MODE”.  
- While in setting mode, user press 'UP / DOWN' button to increase or decrease the set temperaure by 1 °C.
- Press SET again to: exit setting mode and return to display mode with the new set temperature.




