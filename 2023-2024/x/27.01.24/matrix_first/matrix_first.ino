#include <LedControl.h>

LedControl lc=LedControl(12, 11, 10, 1);

int matr[8][8];
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lc.shutdown(0, false);
  lc.setIntensity(0, 8); // максимум яркость 16
  lc.clearDisplay(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  lc.setLed(0, 1, 1, 1); // заработает только 1 диод 2 строка 2
}
