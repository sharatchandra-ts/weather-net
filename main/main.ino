#include "DHT.h"
#include "sensors.h"
#include "wifi_com.h"

// Global vars for averaged values
float avgTemp = 0, avgHum = 0, avgLight = 0, avgAir = 0;

// For summing during the minute
float tempSum = 0, humSum = 0, lightSum = 0, airSum = 0;
int count = 0;

// Timing control
unsigned long lastSendTime = 0; // tracks last send
const unsigned long sendInterval = 60000; // 60 sec

void setup() {
  Serial.begin(115200);
  initSensors();
  connectWiFi();
}

void loop() {
  float temperature = readTemperature();
  float humidity = readHumidity();
  float light_level = readLight();
  float air_quality = readGas();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  /*
  Serial.print("Temperature: " + temperature);
  Serial.print(" °C | Humidity: " + humidity);
  Serial.print(" % | Light: " + light_level);
  Serial.println(" | Air Quality: " + air_quality);
  */
 
  // Add the reading to sums
  addReading(temperature, humidity, light_level, air_quality);

  // Check if 60 seconds have passed
  if (millis() - lastSendTime >= sendInterval) {
    calculateMinuteAverage();
    sendData(avgTemp, avgHum, avgLight, avgAir);
    lastSendTime = millis(); // reset timer
  }

  delay(1000); // read every second
}

void addReading(float t, float h, float l, float a) {
  tempSum += t;
  humSum += h;
  lightSum += l;
  airSum += a;
  count++;
}

void calculateMinuteAverage() {
  if (count == 0) return; // avoid division by zero
  
  avgTemp = tempSum / count;
  avgHum = humSum / count;
  avgLight = lightSum / count;
  avgAir = airSum / count;

  // Reset sums for next minute
  tempSum = humSum = lightSum = airSum = 0;
  count = 0;
}
