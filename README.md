# Designing a Thermostat for Cars - Final Project

**Course:** Embedded System Programming (EE3031)  
**Semester:** 1 – Academic year: 2025–2026  
**Lecturer:** Bui Quoc Bao  
**Student:** Tran Vu Gia Huy (ID: 2252267)

<img width="1330" height="720" alt="Screenshot 2025-12-08 122957" src="https://github.com/user-attachments/assets/d52b97bd-96aa-441f-864e-039eca7c26e3" />


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
- Resistor, Transistor, Flyback diode, etc...

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

## Software Architechture

```
Thermostat_STM32_DS18B20/  
├── Core/  
│ ├── Inc/  
│ │ ├── main.h # Pin definitions  
│ │ ├── ds18b20.h # DS18B20 driver header  
│ │ └── lcd.h # LCD 16x2 driver header  
│ └── Src/  
│ ├── main.c # Application logic  
│ ├── ds18b20.c # DS18B20 implementation  
│ ├── lcd.c # LCD driver  
│ └── system_stm32f1xx.c # System init  
├── Layer Architecture:  
│ ├── HAL Layer (STM32Cube) ← GPIO/Timer/SysTick drivers  
│ ├── Driver Layer ← ds18b20.c + lcd.c (peripheral drivers)  
│ └── Application Layer ← main.c (state machine + UI logic)  
└── Debug # Simulation file (.hex) for Proteus  
```


## State Machine

<img width="1800" height="733" alt="Screenshot 2025-12-08 022607" src="https://github.com/user-attachments/assets/08cbd398-6335-426c-8b6f-9deae7c939ef" />

## Demo Video

[Youtube Link](https://youtu.be/TE3IlUvzKdI)
