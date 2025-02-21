#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define CURRENT_SENSOR_PIN A0
#define VOLTAGE_SENSOR_PIN A1

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  int currentValue = analogRead(CURRENT_SENSOR_PIN);
  int voltageValue = analogRead(VOLTAGE_SENSOR_PIN);
  
  float current = currentValue * (5.0 / 1023.0);
  float voltage = voltageValue * (5.0 / 1023.0);
  
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" Humidity: ");
  Serial.print(humidity);
  Serial.print(" Current: ");
  Serial.print(current);
  Serial.print(" Voltage: ");
  Serial.println(voltage);
  
  delay(2000);
}
