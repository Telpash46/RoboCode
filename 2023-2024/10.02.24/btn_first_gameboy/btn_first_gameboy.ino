#include <Blocks.h>
#include <GameBoy.h>

GameBoy pl; // создать экземпляр класса
int x, y;
void setup() {
  // put your setup code here, to run once:
  pl.begin(15); // яркость от 0 до 15
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int key = pl.getKey();
  Serial.println(key);

  if (key > 0) {
      pl.wipePoint(x, y);
    if (key == 3 && pl.isFree(x, y - 1)) {
      y--;
      
    } else if (key == 4 && pl.isFree(x - 1, y)) {
      x--;
    } else if (key == 5 && pl.isFree(x + 1, y)) {
      x++;
    } else if (key == 6 && pl.isFree(x, y + 1)) {
      y++;
    }
  }


  pl.drawPoint(x, y);
  delay(1);
 
}
