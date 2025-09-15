#include "wifi_com.h"
#include "secrets.h"

struct Reading{
    float temp;
    float hum;
    float ldr;
    float mq135;
    int machine = MACHINE_ID;
};

Reading reading[BUFFER_SIZE];
int c_index = 0;

void connectWiFi()
{
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

void sendData() {
    if (!isWiFiConnected()) {
        Serial.println("WiFi not connected!");
        return;
    }

    HTTPClient http;
    Serial.println("Connecting to server: " + String(SERVER_URL));
    http.begin(SERVER_URL);

    // Headers
    http.addHeader("Content-Type", "application/json");
    http.addHeader("User-Agent", "ESP32-WeatherStation");

    // JSON payload
    String jsonData = "[";
    for (int i = 0; i < BUFFER_SIZE; i++){
        jsonData += "{";
        jsonData += "\"temperature\":" + String(reading[i].temp, 2) + ",";
        jsonData += "\"humidity\":" + String(reading[i].hum, 2) + ",";
        jsonData += "\"light_level\":" + String(reading[i].ldr, 2) + ",";
        jsonData += "\"air_quality\":" + String(reading[i].mq135, 2) + ",";
        jsonData += "\"machine\":" + String(reading[i].machine); // int, not float
        jsonData += "}";

        if (i < BUFFER_SIZE - 1)
            jsonData += ",";
    }

    jsonData += "]";

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

void readData(float temp, float hum, float ldr, float mq135){

    reading[c_index].temp = temp;
    reading[c_index].hum = hum;
    reading[c_index].ldr = ldr;
    reading[c_index++].mq135 = mq135;

    if(c_index >= BUFFER_SIZE){
        sendData();
        c_index = 0;
    }
}