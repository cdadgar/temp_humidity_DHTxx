/*
 *  DHT Temperature & Humidity Sensor 
 *  
 *  DHT22 - white case
 *    pros - bigger range and more accurate than DHT11
 *    cons - can sample once per 2 seconds
 *  DHT11 - blue case
 *    pros - can sample once per second
 *  
 *  VCC - 3.3 or 5v 
 *  DO - data out
 *  NC - not connected
 *  GND - ground
 *  
 * libraries:
 * DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
 * Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor
 */
 
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>


#define DHTPIN 2     // D4

#define DHTTYPE    DHT11
//#define DHTTYPE    DHT22
//#define DHTTYPE    DHT21


DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;


void setup() {
  // start serial port
  Serial.begin(115200);
  Serial.print(F("\n\n DHT Temperature & Humidity Sensor test\n\n"));
  
  // Initialize device.
  dht.begin();

  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
}

void loop() {
  // Delay between measurements.
  delay(delayMS);
  
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.print(F("°C, "));
    Serial.print(event.temperature * 9/5 + 32);
    Serial.println(F("°F"));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }
}
