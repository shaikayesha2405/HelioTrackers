#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

const char* ssid = "E";
const char* password = "123456788";

unsigned long channelID = 2850348;
const char* apiKey = "KOJWHL7CUSQWTIHE";

WiFiClient client;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  ThingSpeak.begin(client);
}

void loop() {
  if (Serial.available() > 0) {
    String sensorData = Serial.readStringUntil('\n');
    float temperature, humidity, current, voltage;
    sscanf(sensorData.c_str(), "Temperature: %f Humidity: %f Current: %f Voltage: %f", 
           &temperature, &humidity, &current, &voltage);

    ThingSpeak.setField(1, temperature);
    ThingSpeak.setField(2, humidity);
    ThingSpeak.setField(3, current);
    ThingSpeak.setField(4, voltage);
    
    int httpCode = ThingSpeak.writeFields(channelID, apiKey);
    if (httpCode == 200) {
      Serial.println("Data sent successfully to ThingSpeak!");
    } else {
      Serial.println("Error sending data to ThingSpeak.");
    }
  }
  delay(20000);
}