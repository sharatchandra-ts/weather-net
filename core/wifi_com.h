#pragma once

#include <WiFi.h>
#include <HTTPClient.h>

// WiFi credentials
extern const char* WIFI_SSID;
extern const char* WIFI_PASS;
extern const char* SERVER_URL;

// Function declarations
void connectWiFi();
bool isWiFiConnected();
void sendData();
void readData(float temp, float hum, float ldr, float mq135);
