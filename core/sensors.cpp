#include <sensors.h>

DHT dht(DHT_PIN, DHT11);

void initSensors(){
  dht.begin();
}

float readTemperature(){
  return dht.readTemperature();
}

float readHumidity(){
  return dht.readHumidity();
}

float readLight(){
  return analogRead(LDR_PIN);
}

float readGas(){
  return analogRead(MQ135_PIN);
}