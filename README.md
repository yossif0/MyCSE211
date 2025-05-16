# MyCSE211
# Real-Time Clock and Analog Signal Display System

## Overview
This project implements a dual-function embedded system using the NUCLEO-F401RE board with an Arduino Multifunction Shield. The system features:

1. **Real-Time Clock (RTC)**: Displays elapsed time in minutes and seconds on the 7-segment display
2. **Analog Signal Monitor**: Displays voltage readings from the on-board potentiometer

## Hardware Requirements
- STM32 NUCLEO-F401RE development board
- Arduino Multifunction Shield
- USB cable for power and programming

## Features

### Real-Time Clock
- Automatically starts counting from 00:00 (MM:SS) after system reset
- 7-segment display format: MM:SS (minutes and seconds)
- Press S1 to reset the clock to 00:00
- Continues running in the background even when the display shows voltage

### Analog Voltage Display
- Press and hold S3 to display the current voltage from the potentiometer
- Voltage range: 0V to 3.3V (displayed with appropriate precision)
- Returns to clock display when S3 is released
- RTC continues to run while voltage is displayed

## Pin Configuration

| Component | Pin | Function |
|-----------|-----|----------|
| 7-Segment Display | Configured via Shield | Displays time/voltage |
| Switch S1 | Shield Digital Pin | Reset clock |
| Switch S3 | Shield Digital Pin | Toggle to voltage display |
| Potentiometer | A0 | Analog input (0-3.3V) |

## Software Implementation

### Code Structure
- **Initialization**: Sets up GPIO pins, peripherals, ADC, and display
- **Main Loop**: Handles display updates and switch monitoring
- **Timer Interrupts**: Manages clock timing and display refresh
- **ADC Handling**: Reads and converts potentiometer position to voltage

### Key Functions
- `initSystem()`: Configures all hardware components
- `updateClock()`: Updates the internal time counters
- `displayTime()`: Formats and displays time on the 7-segment
- `readVoltage()`: Reads ADC value and converts to voltage
- `displayVoltage()`: Formats and displays voltage on the 7-segment

## Building and Flashing

1. Clone this repository
2. Open the project in your preferred STM32 IDE (STM32CubeIDE recommended)
3. Build the project
4. Connect the NUCLEO board via USB
5. Flash the program to the board

## Operation Instructions

1. Power on the system - the RTC will automatically start from 00:00
2. Press S1 at any time to reset the clock to 00:00
3. Press and hold S3 to view the current potentiometer voltage
4. Release S3 to return to the clock display

## Troubleshooting

- If the display is not working properly, check your shield connections
- If voltage readings are inaccurate, ensure proper ADC calibration
- If the clock is not counting correctly, verify timer configurations

## Additional Notes

- The potentiometer voltage ranges from 0V to 3.3V
- The system uses the internal reference voltage for ADC conversion
- The 7-segment display refreshes at approximately 100Hz to avoid flickering

## Author

[Youssef Ahmed Abdelsatar-Muhnnad Nasir El-din Aly]
[ID:2001275-2001556]
Department of Mechatronics
Faculty of Engineering
Ain Shams University

## License

This project is submitted as part of the CSE211s Introduction to Embedded Systems course, Spring 2025.
