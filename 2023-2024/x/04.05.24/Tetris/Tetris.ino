#include "Blocks.h"
#include <GameBoy.h>

GameBoy gb;
int x = 2;
int y = -1;
int rot = 0;
int BLOCK_ID;

void setup() {
  // put your setup code here, to run once:
  gb.begin(2);
  Serial.begin(9600);
  randomSeed(analogRead(0) + analogRead(5));
  BLOCK_ID = random(0,6);
  createBlock(BLOCK_ID);
}

void makeMove() {
  if (gb.getKey() == 4) x--;
  if (gb.getKey() == 5) x++;
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

void createBlock(int num) {
  switch (num) {
    case 0: 
      gb.generateBlock(gb.block, I_Block_1, I_Block_2, I_Block_3, I_Block_4);
      break;
    case 1: 
      gb.generateBlock(gb.block, Z_Block_1, Z_Block_2, Z_Block_3, Z_Block_4);
      break;
    case 2: 
      gb.generateBlock(gb.block, S_Block_1, S_Block_2, S_Block_3, S_Block_4);
      break;
    case 3: 
      gb.generateBlock(gb.block, L_Block_1, L_Block_2, L_Block_3, L_Block_4);
      break;
    case 4: 
      gb.generateBlock(gb.block, J_Block_1, J_Block_2, J_Block_3, J_Block_4);
      break;
    case 5: 
      gb.generateBlock(gb.block, T_Block_1, T_Block_2, T_Block_3, T_Block_4);
      break;
    case 6: 
      gb.generateBlock(gb.block, O_Block_1, O_Block_2, O_Block_3, O_Block_4);
      break;
    default:
      break;  
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  makeMove();
  gb.drawDisplay();
  drawBlock(gb.block[rot], x, y);
  y++;
  delay(100);


}
