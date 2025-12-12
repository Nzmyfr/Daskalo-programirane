#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int TRIG_PIN = 9;
const int ECHO_PIN = 10;
const int BUZZER_PIN = 13;   // <-- added buzzer pin

long duration;
float distance;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);  // <-- set buzzer as output
}

void loop() {

  // Clear the trig pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Trigger the sensor: 10µs HIGH pulse
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure the echo pulse duration
  duration = pulseIn(ECHO_PIN, HIGH);

  // Convert duration to distance (cm)
  distance = duration * 0.0343 / 2;

  // Display distance
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  lcd.setCursor(0, 0);
  lcd.print("Dist: ");
  lcd.print(distance);
  lcd.print(" cm   ");

  // -------------------------------------
  // BUZZER ALARM WHEN <= 10 CM
  // -------------------------------------
  if (distance <= 10 && distance > 0) {
    digitalWrite(BUZZER_PIN, HIGH);   // buzzer ON
  } else {
    digitalWrite(BUZZER_PIN, LOW);    // buzzer OFF
  }

  delay(500);
}
