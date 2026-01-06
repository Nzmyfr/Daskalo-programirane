#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
const int echoONE = 9;
const int trigONE = 10;
const int echoTWO = 6;
const int trigTWO = 5;
const int thresholdCm = 10;
int parking = 5;

float distanceONE;
float distanceTWO;
float durationONE;
float durationTWO;

Servo myServo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  myServo.attach(3);
  lcd.init();
  lcd.backlight();
  pinMode(trigONE, OUTPUT);
  pinMode(echoONE, INPUT);
  pinMode(trigTWO, OUTPUT);
  pinMode(echoTWO, INPUT);
}

void loop() {
  digitalWrite(trigONE, LOW);
  delayMicroseconds(2);
  digitalWrite(trigONE, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigONE, LOW);

  durationONE = pulseIn(echoONE, HIGH);
  distanceONE = (durationONE * 0.034) / 2;

  digitalWrite(trigTWO, LOW);
  delayMicroseconds(2);
  digitalWrite(trigTWO, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigTWO, LOW);

  durationTWO = pulseIn(echoTWO, HIGH);
  distanceTWO = (durationTWO * 0.034) / 2;


  if (distanceONE <= thresholdCm) {
    parking --;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Space Left: ");
    lcd.print(parking);
    for (int pos = 90; pos >= 0; pos -=1){
      myServo.write(pos);
      delay(15);
    }
    delay(500);
    for (int pos = 0; pos <= 90; pos +=1){
      myServo.write(pos);
      delay(15);
    }
  }
  if (distanceTWO <= thresholdCm) {
    lcd.clear();
    parking ++;
    lcd.setCursor(0, 0);
    lcd.print("Space Left: ");
    lcd.print(parking);
    for (int pos = 90; pos >= 0; pos -=1){
      myServo.write(pos);
      delay(15);
    }
    delay(500);
    for (int pos = 0; pos <= 90; pos +=1){
      myServo.write(pos);
      delay(15);
    }
  }
  
  delay(500);
}

