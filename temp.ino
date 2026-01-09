#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// DS18B20 setup
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// LCD setup (change address if needed)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  sensors.begin();

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Temp Sensor");
}

void loop() {
  lcd.clear();
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);

  float newTemp = (tempC - 32) * 5 / 9;
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(newTemp);
  lcd.print((char)223); // degree symbol
  lcd.print("C   ");

  delay(500);
}
