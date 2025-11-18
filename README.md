# Embedded System Programming Course Project

**Course:** Embedded System Programming (EE3031)  
**Semester:** 1 – Academic year: 2024-2025  
**Lecturer:** Bui Quoc Bao  
**Student:** Tran Vu Gia Huy (ID: 2252267)

## Project Objective

Design, simulate, and program a temperature data logging device for automobiles. The system reads temperature from an LM35 sensor and logs the sampled data to a MicroSD card for later analysis[web:1].

## Components Used

- STM32F103C8T6 Blue Pill board
- LM35 temperature sensor
- Push buttons (system power on/off, start/stop recording)
- LCD display
- MicroSD card module

## User Manual

### System Power On/Off

- Press the **Power** button to turn on the logger.  
- The LCD displays system status and a welcome message.
- Press the **Power** button again to turn off the logger. The display will turn off.

### Starting Data Logging

- With the system powered on, press the **Start** button to begin logging temperature data.
- The LCD shows "Logging..." and continuously displays real-time temperature readings.
- The logger automatically saves temperature data to the MicroSD card until stopped[web:1].

### Stopping Data Logging

- Press the **Stop** button to end data logging.
- The LCD confirms logging has stopped.
- The logger writes the last temperature value to the MicroSD card and stops recording.

### Viewing Data

- Remove the MicroSD card and connect it to a PC or card reader.
- Data is stored in plain text files with timestamped temperature readings.

### Troubleshooting

- If the LCD is blank, check all connections and power supply.
- If the logger fails to save data, verify that the MicroSD card is inserted and formatted as FAT32.
- Ensure the LM35 sensor is properly connected to the microcontroller[web:1].
