#define BLYNK_PRINT Serial
#include "DHT.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(4, DHT11);
char auth[] = "44004249418e42a9ba74b705343b1ccf";
char ssid[] = "dnmgiot2018";
char pass[] = "dnmgiot2018";
void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
}
void loop()
{
  Blynk.run();
  delay(2000);
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (isnan(h) || isnan(t))
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  Serial.print(h);
  Serial.println("Humidity");
  Serial.print(t);
  Serial.println("Temperature");
  Blynk.virtualWrite(V0, h);
  Blynk.virtualWrite(V1, t);
}
