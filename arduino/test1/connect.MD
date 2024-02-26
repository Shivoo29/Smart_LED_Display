# Connecting ESP32 to Arduino

This guide will show you how to connect an ESP32 board to an Arduino board for communication between the two devices.

## Requirements

- ESP32 board
- Arduino board
- USB cables for both ESP32 and Arduino
- Breadboard and jumper wires (optional)

## Steps

1. **Prepare the Hardware:**
   - Connect the ESP32 board to your computer via USB.
   - Connect the Arduino board to your computer via USB.

2. **Install Necessary Software:**
   - Ensure that you have the Arduino IDE installed on your computer.
   - Install the required board drivers for both ESP32 and Arduino if you haven't already.

3. **Upload Code to ESP32:**
   - Write the code for the ESP32 in the Arduino IDE.
   - Connect the ESP32 to the Arduino board using jumper wires:
     - Connect the ESP32's TX pin to the Arduino's RX pin.
     - Connect the ESP32's RX pin to the Arduino's TX pin.
     - Optionally, connect the ESP32's GND pin to the Arduino's GND pin for common ground.
   - Upload the code to the ESP32 using the Arduino IDE.

4. **Configure Arduino for Serial Communication:**
   - Write the code for the Arduino in the Arduino IDE.
   - Use the `Serial` library to establish serial communication with the ESP32:
     ```cpp
     void setup() {
       Serial.begin(115200); // Set baud rate to 115200
     }
     
     void loop() {
       // Your code here
     }
     ```
   - Use `Serial.print()` and `Serial.read()` functions to send and receive data between the Arduino and ESP32.

5. **Testing:**
   - Upload the code to the Arduino board using the Arduino IDE.
   - Open the Serial Monitor in the Arduino IDE to view the communication between the ESP32 and Arduino.

6. **Troubleshooting:**
   - Double-check the wiring connections between the ESP32 and Arduino.
   - Ensure that the baud rates are matching between the ESP32 and Arduino (usually 115200).

## Additional Notes

- Make sure to power both the ESP32 and Arduino boards adequately.
- Test your setup thoroughly before deploying it in your project.


## Arduino Setup

In your Arduino code, you need to read the data sent by the ESP32 over Serial and then process it accordingly. Here's a basic example of how you can read and process the data:

```cpp
void setup() {
  Serial.begin(115200); // Initialize serial communication
  // Initialize P10 LED display or any other required setup
}

void loop() {
  if (Serial.available() > 0) {
    // Read data from ESP32
    String data = Serial.readStringUntil('\n');
    
    // Process data (example: print to Serial Monitor)
    Serial.println("Received data from ESP32: " + data);
    
    // Add logic to display data on the LED display
    // You can parse the data string and extract PM2.5, AQI, and category information for display
  }
}
