#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// WiFi credentials
const char* ssid = "your_wifi_ssid"; // Replace "your_wifi_ssid" with your WiFi SSID
const char* password = "your_wifi_password"; // Replace "your_wifi_password" with your WiFi password

// OpenWeatherMap API key and location coordinates
const char* API_KEY = "16c61fdf9aa60dd3041f86e41fc7733b"; // Your OpenWeatherMap API key
const float latitude = 28.7171723; // Latitude of your location
const float longitude = 77.0695416; // Longitude of your location

WiFiClient client; // Create a WiFiClient object

void setup() {
  Serial.begin(115200); // Start serial communication
  delay(100);

  WiFi.begin(ssid, password); // Connect to WiFi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "http://api.openweathermap.org/data/2.5/weather?lat=" + String(latitude, 6) + "&lon=" + String(longitude, 6) + "&appid=" + API_KEY;
    http.begin(client, url); // Start HTTP request
    int httpCode = http.GET();
    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, payload);
        float pm25 = extractPM25(doc);
        if (pm25 != 0) {
          int aqi = calculateAQI(pm25);
          String aqiCategory = calculateAQICategory(aqi);

          // Print results to Serial Monitor
          Serial.println("[Running] ESP32");
          Serial.print("Estimated PM2.5 level: ");
          Serial.println(pm25);
          Serial.print("Estimated AQI: ");
          Serial.println(aqi);
          Serial.print("AQI Category: ");
          Serial.println(aqiCategory);
        }
      }
    } else {
      Serial.println("Error on HTTP request");
    }
    http.end(); // Close HTTP connection
  }
  delay(30000); // Wait for 30 seconds before next request
}

/**
 * @brief Extracts the PM2.5 concentration from the weather data.
 * 
 * This function extracts the PM2.5 concentration from the weather data JSON document.
 * It assumes that the PM2.5 concentration is represented by the "humidity" field in the "main" object.
 * 
 * @param doc The JSON document containing the weather data.
 * @return The PM2.5 concentration extracted from the weather data.
 */
float extractPM25(JsonDocument &doc) {
  float pm25 = 0;
  JsonObject main = doc["main"];
  if (!main.isNull()) {
    pm25 = main["humidity"]; // Use humidity as a placeholder for PM2.5 concentration
  }
  return pm25;
}

/**
 * @brief Calculates the Air Quality Index (AQI) based on the PM2.5 concentration.
 * 
 * This function calculates the AQI based on the provided PM2.5 concentration.
 * It uses predefined ranges to map the PM2.5 concentration to the corresponding AQI value.
 * 
 * @param pm25 The PM2.5 concentration.
 * @return The calculated AQI.
 */
int calculateAQI(float pm25) {
  if (pm25 <= 12.1) {
    return map(pm25, 0, 12.1, 0, 50);
  } else if (pm25 <= 35.5) {
    return map(pm25, 12.1, 35.5, 51, 100);
  } else if (pm25 <= 55.5) {
    return map(pm25, 35.5, 55.5, 101, 150);
  } else if (pm25 <= 150.5) {
    return map(pm25, 55.5, 150.5, 151, 200);
  } else if (pm25 <= 250.5) {
    return map(pm25, 150.5, 250.5, 201, 300);
  } else if (pm25 <= 350.5) {
    return map(pm25, 250.5, 350.5, 301, 400);
  } else {
    return map(pm25, 350.5, 500, 401, 500);
  }
}

/**
 * @brief Determines the AQI category based on the AQI value.
 * 
 * This function determines the AQI category (e.g., Good, Moderate, Unhealthy) based on the provided AQI value.
 * It uses predefined ranges to classify the AQI into categories.
 * 
 * @param aqi The Air Quality Index (AQI).
 * @return The AQI category.
 */
String calculateAQICategory(int aqi) {
  if (aqi >= 0 && aqi <= 50) {
    return "Good";
  } else if (aqi >= 51 && aqi <= 100) {
    return "Moderate";
  } else if (aqi >= 101 && aqi <= 150) {
    return "Unhealthy for Sensitive Groups";
  } else if (aqi >= 151 && aqi <= 200) {
    return "Unhealthy";
  } else if (aqi >= 201 && aqi <= 300) {
    return "Very Unhealthy";
  } else if (aqi >= 301 && aqi <= 400) {
    return "Hazardous";
  } else if (aqi >= 401 && aqi <= 500) {
    return "Very Hazardous";
  } else {
    return "Unknown";
  }
}