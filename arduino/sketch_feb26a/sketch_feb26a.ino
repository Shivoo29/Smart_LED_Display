void setup() {
  Serial.begin(115200); // Initialize serial communication
}

void loop() {
  if (Serial.available() > 0) {
    // Read data from ESP32
    String data = Serial.readStringUntil('\n');
    
    // Display received data on Serial Monitor
    Serial.println("Received data from ESP32: " + data);
  }
}
