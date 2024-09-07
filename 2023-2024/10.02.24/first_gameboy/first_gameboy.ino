#include <Blocks.h>
#include <GameBoy.h>

int x = 7, y = 0;
GameBoy pl; // создать экземпляр класса

void setup() {
  // put your setup code here, to run once:
  pl.begin(15); // яркость от 0 до 15
}

void loop() {
  // put your main code here, to run repeatedly:
  pl.drawPoint(x, y);
  y++;
  delay(250);
  pl.wipePoint(x, y-1);
  delay(230);
  if (y > 15) {
    y = 0;
  }
}
