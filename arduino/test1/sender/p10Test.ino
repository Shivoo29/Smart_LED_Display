#include <SPI.h>
#include <WiFi.h>

// Define the pin connections
#define DATA_PIN    23  // Connect to the DATA pin of the P10 LED display
#define CLK_PIN     18  // Connect to the CLK pin of the P10 LED display
#define CS_PIN      5   // Connect to the CS pin of the P10 LED display

// Define the SSID and password of your WiFi network
const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Connect to WiFi
  Serial.printf("Connecting to %s\n", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  // Initialize SPI communication
  SPI.begin(CLK_PIN, MISO, MOSI, CS_PIN);

  // Set the pin modes
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLK_PIN, OUTPUT);
  pinMode(CS_PIN, OUTPUT);

  // Clear the display
  clearDisplay();

  // Print "Hello, World!" on the display
  printText("Hello, World!");
}

void loop() {
  // Nothing to do here since we are printing static text in setup()
}

void clearDisplay() {
  digitalWrite(CS_PIN, LOW);  // Select the display
  SPI.transfer(0x42);  // Start of transmission command
  SPI.transfer(0x00);  // Clear the display command
  digitalWrite(CS_PIN, HIGH);  // Deselect the display
}

void printText(String text) {
  digitalWrite(CS_PIN, LOW);  // Select the display
  SPI.transfer(0x44);  // Start of data command

  for (int i = 0; i < text.length(); i++) {
    SPI.transfer(text[i]);
  }

  digitalWrite(CS_PIN, HIGH);  // Deselect the display
}
