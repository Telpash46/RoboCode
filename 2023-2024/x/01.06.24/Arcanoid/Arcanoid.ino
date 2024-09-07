#include <GameBoy.h>
#include "Blocks.h"
GameBoy gb;

int paddleX = 3;
int paddleY = 14;
int directionX = 1;
int directionY = -1;
int ballX = 4;
int ballY = 13;

void setup() {
  // put your setup code here, to run once:
  gb.begin(1);
}

void loop() {
  // put your main code here, to run repeatedly:
  makePaddle();
  gb.drawDisplay();
  drawPaddle(paddle, paddleX, paddleY);
  //500
  delay(200);
}

void drawPaddle(byte arr[3], int x, int y) {
  for (int i = 0; i < 3; i++) {
    if (arr[i] == 1) {
      gb.drawPoint(x + i, y);
    }
  }
}


void makePaddle() {
  if (gb.getKey() == 4 && paddleX > 0) {
    paddleX--;
  } else if (gb.getKey() == 5 && paddleX < 5) {
    paddleX++;
  }
}
  
