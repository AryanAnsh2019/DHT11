#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(4, DHT11);
LiquidCrystal_I2C lcd(0x27, 16, 2);
int mypins[3] = {25, 33, 27}, i;
void setup()
{
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  lcd.init();
  lcd.backlight();
  dht.begin();
  for (i = 0; i < 3; i++)
  {
    pinMode(mypins[i], OUTPUT);
  }
  pinMode(5, OUTPUT);
}
void loop()
{
  delay(2000);
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (isnan(h) || isnan(t))
  {
    lcd.println(F("Failed to read from DHT sensor!"));
    return;
  }
  lcd.setCursor(0, 0);
  lcd.print("Humidity:");
  lcd.print(h);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("Temp.:");
  lcd.print(t);
  lcd.print("C");
  if (t >= 40)
  {
    digitalWrite(mypins[0], HIGH);
    digitalWrite(5, HIGH);
    delay(10);
    digitalWrite(5, LOW);
    delay(10);
  }
  else if (t < 40 && t > 20)
  {
    digitalWrite(mypins[1], HIGH);
    digitalWrite(5, HIGH);
    delay(100);
    digitalWrite(5, LOW);
    delay(100);
  }
  else
  {
    digitalWrite(mypins[2], HIGH);
    digitalWrite(5, HIGH);
    delay(1000);
    digitalWrite(5, LOW);
    delay(1000);
 }
} 
