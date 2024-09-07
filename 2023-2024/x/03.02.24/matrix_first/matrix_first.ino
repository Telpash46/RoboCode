#include <LedControl.h>

LedControl lc = LedControl(12, 11, 10, 1);

void setup() {
  // put your setup code here, to run once:
  lc.shutdown(0, false);
  lc.setIntensity(0, 1);
  lc.clearDisplay(0);
}

void triangle() {
  lc.setLed(0, 3, 2, 1);
  lc.setLed(0, 3, 3, 1);
  lc.setLed(0, 3, 4, 1);
  lc.setLed(0, 3, 5, 1);
  lc.setLed(0, 3, 6, 1);
  lc.setLed(0, 2, 3, 1);
  lc.setLed(0, 2, 4, 1);
  lc.setLed(0, 2, 5, 1);
  lc.setLed(0, 1, 4, 1);
}

void blank_square() {
  lc.setLed(0, 1, 1, 1);
  lc.setLed(0, 2, 1, 1);
  lc.setLed(0, 3, 1, 1);
  lc.setLed(0, 4, 1, 1);
  lc.setLed(0, 5, 1, 1);
  lc.setLed(0, 6, 1, 1);
  lc.setLed(0, 1, 2, 1);
  lc.setLed(0, 6, 2, 1);
  lc.setLed(0, 1, 3, 1);
  lc.setLed(0, 6, 3, 1);
  lc.setLed(0, 1, 4, 1);
  lc.setLed(0, 6, 4, 1);
  lc.setLed(0, 1, 5, 1);
  lc.setLed(0, 6, 5, 1);
  lc.setLed(0, 1, 6, 1);
  lc.setLed(0, 2, 6, 1);
  lc.setLed(0, 3, 6, 1);
  lc.setLed(0, 4, 6, 1);
  lc.setLed(0, 5, 6, 1);
  lc.setLed(0, 6, 6, 1);
}

void loop() {
  lc.setRow(0, 2, B01010101);
}
