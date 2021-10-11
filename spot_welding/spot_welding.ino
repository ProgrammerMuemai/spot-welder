
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3f, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display
#define btn_start 3
#define relay 2
bool sw_status = false;

void setup()
{
  lcd.init();
  lcd.backlight();
  pinMode(btn_start, INPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
  Serial.begin(9600);
}

void loop()
{
  int val = map(analogRead(A0), 0, 1023, 0, 100);
  float valf = val / 100.0;
  float newval = mapf(valf, 0.0, 1.0, 0.0, 0.2);
  float mstime = newval*1000.0;

  lcd.setCursor(0, 0);
  lcd.print("Delay:");
  lcd.setCursor(6, 0);
  lcd.print(mstime);
  lcd.setCursor(11, 0);
  lcd.print("ms");
  lcd.setCursor(0, 1);
  lcd.print("Ready...");


  if (digitalRead(btn_start) == HIGH and sw_status == false) {
    digitalWrite(relay, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Working...");
    delay(valf * 1000);
    digitalWrite(relay, HIGH);
    sw_status = true;
  }
  if (digitalRead(btn_start) == LOW) {
    sw_status = false;
  }
}
double mapf(double val, double in_min, double in_max, double out_min, double out_max) {
  return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
