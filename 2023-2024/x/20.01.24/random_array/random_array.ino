#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int T = 0;
//Fixed by RoboCode
LiquidCrystal_I2C lcd_27(0x27, 16, 2);

void setup()
{
  lcd_27.begin ();
  lcd_27.backlight();
}

void loop()
{
  T = ( ( analogRead(1) * 500 ) / 1023 );
  lcd_27.setCursor(1-1, 1-1);
  lcd_27.print( T );
  delay(1000);
  lcd_27.clear();
}
