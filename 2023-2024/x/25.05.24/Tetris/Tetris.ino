#include "Blocks.h"
#include <GameBoy.h>
GameBoy gb;
int x = 2, y = -1;
int rot = 0;
int acc = 1;
int speed = 200;
int score = 0;
int level = 0;
void setup() {
  randomSeed(analogRead(0) + analogRead(5));
  gb.begin(1);
  createBlock(random(0,  7));
  Serial.begin(9600);
}

bool loss() {
  if (gb.checkBlockCollision(gb.block[rot], x, 0)) {
    return true;
  }
  else {
    return false;
  }
}

bool win() {
  if (score >= 2) {
    return true;
  }
  return false;
}

void makeMove() {
  if (gb.getKey() == 4) {
    if (!gb.checkBlockCollision(gb.block[rot], x - 1, y)) {
      x--;
    }
  }
  if (gb.getKey() == 5) {
    if (!gb.checkBlockCollision(gb.block[rot], x + 1, y)) {
      x++;
    }
  }
  if (gb.getKey() == 1) {
    if (!gb.checkBlockCollision(gb.block[rot], x + 1, y)) {
      if (rot == 3) {
        rot = 0;
      } else {
        rot++;
      }
    }
  }

  if (gb.getKey() == 6) {
    acc = 4;
  } else {
    acc = 1;
  }

}
void createBlock(int num) {
  randomSeed(analogRead(0));
  //2
  x = random(0,5); y = -1; rot = random(0, 4);
  if (num == 0) gb.generateBlock(gb.block, I_Block_1, I_Block_2, I_Block_3, I_Block_4);
  if (num == 1) gb.generateBlock(gb.block, Z_Block_1, Z_Block_2, Z_Block_3, Z_Block_4);
  if (num == 2) gb.generateBlock(gb.block, S_Block_1, S_Block_2, S_Block_3, S_Block_4);
  if (num == 3) gb.generateBlock(gb.block, L_Block_1, L_Block_2, L_Block_3, L_Block_4);
  if (num == 4) gb.generateBlock(gb.block, J_Block_1, J_Block_2, J_Block_3, J_Block_4);
  if (num == 5) gb.generateBlock(gb.block, T_Block_1, T_Block_2, T_Block_3, T_Block_4);
  if (num == 6) gb.generateBlock(gb.block, O_Block_1, O_Block_2, O_Block_3, O_Block_4);

}
void drawBlock(byte arr[4][4], int x, int y) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4 ; j++) {
      if (arr[j][i] == 1) {
        gb.drawPoint (x + i, y + j);
      }
    }
  }
}

void loop() {
  if (loss()) {
    score = 0;
    gb.sound(COLLISION);
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 16; j++) {
        gb.wipePoint(i, j);
      }
    }
    gb.testMatrix(10);
  }
  if (win()) {
    gb.sound(COLLISION);
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 16; j++) {
        gb.wipePoint(i, j);
        gb.setLed(i, j, WIN[j][i]);
      }
    }
    delay(2000);
    gb.clearDisplay();
    score = 0;
    level = 0;
  }
  makeMove();
  Serial.println(level);
  if (gb.checkBlockCollision(gb.block[rot], x, y + 1)) {
    gb.memBlock(gb.block[rot], x, y);
    int lines = gb.fullLine();
    if (lines != 0) {
      score += lines;
      level += lines;
    }

    if (level >= 5) {
      gb.sound(SCORE);
      acc += 1;
      level = 0;
    }
    createBlock(random(0, 7));
  }
  else {
    y++;
  }
  gb.drawDisplay();
  drawBlock(gb.block[rot], x, y);
  delay(speed / acc);
}
