# Dual-Mode Stopwatch

## Overview

The **Dual-Mode Stopwatch** is an embedded system project implemented using an **ATmega32** microcontroller. This stopwatch provides two operating modes for timekeeping, allowing users to measure elapsed time with precision. The system is designed to run in a simulation environment such as **Proteus** or be deployed on real hardware.

## Features
- **Two Modes of Operation**
  - **Manual Mode**: Start, stop, and reset the stopwatch using physical buttons.
  - **Automatic Mode**: The stopwatch runs continuously with preset intervals.
- **Seven-Segment Display**: Shows the elapsed time in HH:MM:SS format.
- **External Interrupts**: Used for button press detection to control stopwatch functions.
- **Timers**: Utilized for precise time measurement.
- **Efficient Embedded C Implementation**.

## Project Structure
The project follows a modular design with different drivers handling specific functionalities:

### **Drivers Used**
- **LCD Driver**: Displays information and status updates.
- **Keypad Driver**: Handles user inputs for mode selection and control.
- **UART Driver**: Facilitates serial communication (if needed for debugging).
- **TWI (I2C) Driver**: Manages communication with external devices.
- **Timer Driver**: Controls timekeeping operations for the stopwatch.
- **Interrupt Driver**: Detects button presses and triggers necessary actions.

## How It Works
1. **Compile the Project**:
   - Build the project in **Eclipse** by selecting **Project > Build Project**.
   - This will generate an **.elf** file required for execution.

2. **Locate the `.elf` File**:
   - The compiled `.elf` file can be found in the `Debug/` or `Release/` folder.
   - If missing, refresh the project in Eclipse or check the console output.

3. **Load the `.elf` File into the ATmega32**:
   - Open **Proteus** or **AVR Studio**.
   - Upload the `.elf` file to the ATmega32 microcontroller in the simulation.
   - Run the simulation to test the stopwatch functionality.

4. **Ensure Each Component Has Its Own `.elf` File**:
   - If errors occur during simulation, make sure that each **ATmega32 microcontroller** has its own **.elf** file.
   - The `.elf` files for ATmega32 can be found in the `Debug/` folder.
   - Any external `.elf` files provided in the GitHub repository must be used accordingly.

5. **Use the Stopwatch**:
   - Select the operating mode (Manual or Automatic).
   - Start, stop, and reset the stopwatch using button inputs.
   - Observe the timer on the **seven-segment display**.

## Requirements
- **Hardware**:
  - ATmega32 microcontroller
  - Seven-segment display
  - Push buttons for mode selection and control
  - Power supply
- **Software**:
  - **Eclipse IDE** with AVR-GCC toolchain
  - **Proteus** for simulation
  - **AVR Studio** (optional for debugging)

## Contributing
Contributions are welcome! Feel free to submit issues or pull requests to improve the project.

## License
This project is open-source under the **MIT License**.

