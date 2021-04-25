#include "ThingSpeak.h"
#include "secrets.h"
#include "DHT.h"
#include <Wire.h>
#include <WiFi.h>
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHT11);
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int keyIndex = 0;
WiFiClient  client;
unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;
// Initialize our values
String myStatus = "";
void setup()
{
  Serial.begin(115200);
  Serial.println(F("DHTxx test!"));
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  dht.begin();
}
void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }
  delay(2000);
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (isnan(h) || isnan(t))
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  ThingSpeak.setField(1, t);
  ThingSpeak.setField(2, h);
  Serial.print("Humidity:");
  Serial.print(h);
  Serial.println("%");
  Serial.print("Temp:");
  Serial.println(t);
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (x == 200)
  { 
    Serial.println("Channel update successful.");
  }
  else
  {
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  delay(20000);
}
