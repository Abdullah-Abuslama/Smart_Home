# Smart_Home

## Overview
This project is a Smart Home Automation System that allows users to control various aspects of their home through a laptop using UART communication. The system includes two main subsystems: a **Safety Door** and **Lighting Control**. It also integrates a fan and lamp control feature, accessible once the door is unlocked, and an automated outside lighting system.

## Features
- **Safety Door System**: 
  - Controlled via laptop (UART) or a keypad.
  - Allows up to 10 users with unique IDs and passwords.
  - Security alarm triggers after three consecutive incorrect password attempts.
  
- **Fan and Lamp Control**:
  - Accessible only after the Safety Door is unlocked.
  - Can be controlled through the laptop or keypad.

- **Automated Outside Lighting**:
  - Lights automatically turn on when it gets dark.
  - Lights turn off at sunrise, using an LDR and ADC for precise ambient light detection.

## Hardware Components
- **UART**: Handles communication between the laptop and the home system.
- **CLCD (Character LCD)**: Displays information to the user.
- **TIMER**: Manages timing operations for various processes.
- **GIE (Global Interrupt Enable)**: Ensures proper handling of interrupts.
- **KEYPAD**: Interface for entering user credentials.
- **SERVO**: Controls the door locking mechanism.
- **LDR (Light Dependent Resistor) & ADC (Analog-to-Digital Converter)**: Together, these components sense and process ambient light levels to control outside lighting.
- **DIO (Digital Input/Output)**: Manages digital signals for controlling the fan, lamp, and other peripherals.

## Software Components
- **User Authentication System**: Handles user login, password verification, and security features.
- **Lighting Control Logic**: Automates outside lighting based on LDR input processed through the ADC.
- **Peripheral Control**: Manages fan and lamp states after door access.

## Installation
1. Clone the repository:
    ```bash
    git clone https://github.com/yourusername/smart-home-automation.git
    ```
2. Navigate to the project directory and open it in your preferred IDE.
3. Ensure all necessary drivers and libraries are installed.
4. Upload the code to your microcontroller and connect it to the required hardware components.

## Usage
- **Safety Door Access**:
  - Use the keypad or the connected laptop to enter your username and password.
  - If the credentials are correct, the door will unlock, allowing further control of the fan and lamp.
  - After three incorrect attempts, the system will trigger an alarm.

- **Fan and Lamp Control**:
  - Once the door is unlocked, use the same interface to turn the fan and lamp on or off.

- **Automated Outside Lighting**:
  - The system will automatically manage the outside lights based on the time of day, using LDR and ADC for accurate ambient light detection.

## Contributing
Feel free to contribute by submitting a pull request or opening an issue for any suggestions or improvements.

## License
This project is licensed under the Apache 2.0 License - see the [LICENSE](LICENSE) file for details.