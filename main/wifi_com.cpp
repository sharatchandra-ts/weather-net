#include "wifi_com.h"

const char* WIFI_SSID = "Abheri";
const char* WIFI_PASS = "phalaisinWCFA";
const char* SERVER_URL = "http://192.168.68.100:8000/weatherdata";

void connectWiFi() {
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        delay(1000);
    }
    Serial.print("\nConnected to WiFi: ");
    Serial.println(WIFI_SSID);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

bool isWiFiConnected() {
    return WiFi.status() == WL_CONNECTED;
}

void sendData(float temp, float hum, float ldr, float mq135) {
    if (!isWiFiConnected()) {
        Serial.println("WiFi not connected!");
        return;
    }

    HTTPClient http;
    http.begin(SERVER_URL);

    // Headers
    http.addHeader("Content-Type", "application/json");
    http.addHeader("User-Agent", "ESP32-WeatherStation");

    // JSON payload
    String jsonData = "{";
    jsonData += "\"temperature\":" + String(temp, 2) + ",";
    jsonData += "\"humidity\":" + String(hum, 2) + ",";
    jsonData += "\"light_level\":" + String(ldr, 2) + ",";
    jsonData += "\"air_quality\":" + String(mq135, 2);
    jsonData += "}";

    Serial.println("Sending JSON: " + jsonData);

    // POST request
    int httpCode = http.POST(jsonData);

    if (httpCode > 0) {
        Serial.println("HTTP Response: " + String(httpCode));
        if (httpCode == 200) {
            String response = http.getString();
            Serial.println("Server response: " + response);
        }
    } else {
        Serial.println("HTTP Error: " + String(httpCode));
        Serial.println("Check server URL and network connection");
    }

    http.end();
}
