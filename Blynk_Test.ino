#include <ESP8266WiFi.h>
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
#include <SPI.h>
#include <SimpleTimer.h>
#include <DHT.h>
 
//cek email dan copy paste kan disini
char auth[] = "dEfZPRAwJA0uNLFE5s6fxnNQfJlOPjJX";
 
//isikan nama wifi dan passwordnya
char ssid[] = "NEXIAN";
char pass[] = "pastibisa";

#define DHTPIN 2  // GPIO D4

#define DHTTYPE DHT11 // dht11

DHT dht (DHTPIN, DHTTYPE);
SimpleTimer timer;

void sendSensor () {
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t))  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // you can send any value at any time
  // please don't send more that 10 values per second
  Blynk.virtualWrite(V5, h); // V5 for humidity
  Blynk.virtualWrite(V6, t); // V6 for temperature
}
 
void setup() {
  Serial.begin(9600); // see the connection status in serial monitor
  Blynk.begin(auth, ssid, pass);

  dht.begin();

  //setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}
 
void loop() {
  Blynk.run(); // initiates blynk
  timer.run(); // initiates SimpleTimer
}
