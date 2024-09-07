#include <EEPROM.h>


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
   for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (EEPROM.read(0) != 0) {
    Serial.println("Restored: " + EEPROM.read(0));
  } else {
    EEPROM.write(0, 5);
    Serial.println("Wrote");
  }
}
