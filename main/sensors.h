#pragma once

#include "DHT.h"
#include "config.h"

extern DHT dht;

void initSensors();

float readTemperature();

float readHumidity();

float readLight();

float readGas();