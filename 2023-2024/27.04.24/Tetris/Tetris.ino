#include <Blocks.h>
#include <GameBoy.h>

GameBoy gb;

void setup() {
  // put your setup code here, to run once:
  gb.begin(2);
}

void loop() {
  // put your main code here, to run repeatedly:
  drawBlock(I_Block_1, 3, 0);
  delay(500);
  gb.clearDisplay();
  
  drawBlock(I_Block_2, 3, 0);
  delay(500);
  gb.clearDisplay();
  
  drawBlock(I_Block_3, 3, 0);
  delay(500);
  gb.clearDisplay();
  
  drawBlock(I_Block_4, 3, 0);
  delay(500);
  gb.clearDisplay();
}

void drawBlock(byte arr[4][4], int x, int y) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (arr[j][i] == 1) {
        gb.drawPoint(x + i, y + j);
      }
    }
  }
}
