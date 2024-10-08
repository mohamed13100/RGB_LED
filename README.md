# Arduino LED Matrix Project

This project utilizes an Arduino Uno, a sound sensor, and a Bluetooth module (HC-5) to create an interactive LED matrix display. The project can be controlled via a mobile application, allowing you to choose colors, control speed, and play games using sound input.

## Features

1. **Color Selection**
   - Choose from 7 different colors to display your shapes.
   - Control the color via the mobile application.

2. **Speed Control**
   - Adjust the speed of the shape movement on the LED matrix.
   - Speed can be set from 0 to 255, allowing for fine-tuned control.

3. **Snake Game**
   - Play a classic snake game on the LED matrix.
   - The snake's movement can be controlled and influenced by sound input from the sound sensor.

4. **Sound-Activated Games**
   - Engage in other games that respond to sound input.
   - The sound sensor detects changes and influences game dynamics, making the gameplay more interactive.

5. **Bluetooth Connectivity**
   - Use the HC-5 Bluetooth module to connect your Arduino to a mobile app.
   - Control all features, including color selection, speed control, and game modes, remotely from your smartphone.

## Components Used

- **Arduino Uno**
- **LED Matrix**
- **Sound Sensor**
- **Bluetooth Module HC-5**
- **Mobile Application** (for sending commands to the Arduino)

## Getting Started

1. **Hardware Setup**
   - Connect the LED matrix to the Arduino.
   - Interface the sound sensor and Bluetooth module (HC-5) with the Arduino.
   - Ensure proper power supply and wiring.

2. **Mobile Application**
   - Download the required mobile app (link or name of the app).
   - Pair your smartphone with the HC-5 module via Bluetooth.
   - Use the app to send commands to the Arduino to control the LED matrix.

3. **Arduino Code**
   - Upload the provided Arduino sketch to your Uno board.
   - Ensure that the correct libraries are installed for FastLED and Bluetooth communication.

## Usage

1. **Color and Speed Control**
   - Open the mobile app and select your preferred color and speed.
   - The LED matrix will update in real-time based on your selections.

2. **Playing Games**
   - Choose the snake game or other sound-activated games from the app.
   - Play the games using either manual controls via the app or sound input via the sensor.


