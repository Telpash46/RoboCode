#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Fixed by RoboCode
LiquidCrystal_I2C lcd_27(0x27, 16, 2);

void setup()
{
  lcd_27.begin ();
  lcd_27.backlight();
}

void loop()
{
  lcd_27.setCursor(1-1, 1-1);
  lcd_27.print( "nevidimka syuy" );
}
