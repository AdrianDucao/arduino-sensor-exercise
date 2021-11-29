#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  lcd.begin();

  // Turn on the blacklight
  lcd.setBacklight((uint8_t)1);

  // row 1
  lcd.print("Hello, world!");

  // row 2
  lcd.setCursor(0, 1);
  lcd.print("iyotan sa kanto");
}

void loop()
{
  // Do nothing here...
}
