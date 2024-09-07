#include <Blocks.h>
#include <GameBoy.h>

GameBoy gb;

const int DELAY = 300;
const int X_MIN = 0;
const int Y_MIN = 0;
const int X_MAX = 7;
const int Y_MAX = 15;
const int VICTORY_LENGTH = 127;
const int up = 1;
const int right = 2;
const int bottom = 3;
const int left = 4;
const int BOARD_BRIGHTNESS = 2;
int modeCount = 0;
int AppleX;
int AppleY;
int x = 1, y = 0;
int dirX, dirY;
int snakeX[128];
int snakeY[128];
int direction = right;
int lenSnake = 1;
bool state;

byte ARROWS[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 1, 0, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {1, 1, 1, 0, 0, 1, 1, 1},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 0, 1, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

byte CAR[8][8] = {
  {0, 1, 0, 1, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 0, 0, 0},
  {0, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 1, 1, 1, 0},
  {0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 1, 0, 1, 0}
};

byte SNAKE[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 1, 1, 0, 0, 0, 0, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 1, 1, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 0, 1, 1, 1, 1, 0, 0}
};


void setup() {
  // put your setup code here, to run once:

  gb.begin(BOARD_BRIGHTNESS);
  randomSeed(analogRead(2) + analogRead(5));
  Serial.begin(9600);
  generateApple();
  snakeX[0] = 4;
  snakeY[0] = 7;
}

void makeMove() {
  switch (gb.getKey()) {
    case 4:
      if (direction != right) {
        direction = left;
      }
      break;
    case 5:
      if (direction != left) {
        direction = right;
      }
      break;
    case 6:
      if (direction != up) {
        direction = bottom;
      }
      break;
    case 3:
      if (direction != bottom) {
        direction = up;
      }
      break;
    default:
      break;
  }
}

boolean isPartOfSnake (int x, int y) {
  for (int i = 0; i < lenSnake - 1; i++) {
    if ((x == snakeX[i]) && (y == snakeY[i])) {
      return true;
    }
  }
  return false;
}

void generateApple() {
  gb.wipePoint(AppleX, AppleY);
  AppleX = random(X_MIN, X_MAX);
  AppleY = random(Y_MIN, Y_MAX);
  while (isPartOfSnake(AppleX, AppleY)) {
    AppleX = random(X_MIN, X_MAX);
    AppleY = random(Y_MIN, Y_MAX);
  }
}



void move() {
  for (int i = lenSnake - 1; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  switch (direction) {
    case up:
      if (direction != bottom) {
        if (snakeY[0] == 0) {
          snakeY[0] = Y_MAX;
        } else {
          snakeY[0]--;
        }
      }
      break;
    case bottom:
      if (direction != up) {
        if (snakeY[0] == Y_MAX) {
          snakeY[0] = Y_MIN;
        } else {
          snakeY[0]++;
        }
      }
      break;
    case left:
      if (direction != right) {
        if (snakeX[0] == 0) {
          snakeX[0] = X_MAX;
        } else {
          snakeX[0]--;
        }
      }
      break;
    case right:
      if (direction != left) {
        if (snakeX[0] == X_MAX) {
          snakeX[0] = X_MIN;
        } else {
          snakeX[0]++;
        }
      }
      break;
    default:
      break;
  }
}

void drawSnake() {
  for (int i = 0; i < lenSnake; i++) {
    gb.drawPoint(snakeX[i], snakeY[i]);
  }
}


void drawFruit() {
  state = !state;
  if (state == true) {
    gb.drawPoint(AppleX, AppleY);
  } else {
    gb.wipePoint(AppleX, AppleY);
  }
}

int modeSelector() {
  switch (gb.getKey()) {
    case 4:
      modeCount++;
      delay(250);
      if (modeCount > 1) {
        modeCount = 0;
      }
      break;
    case 5:
      modeCount--;
      delay(250);
      if (modeCount < 0) {
        modeCount = 1;
      }
      break;
  }
  return modeCount;
}

void mainMenu() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      gb.wipePoint(i, j);
      gb.setLed(i, j, ARROWS[i][j]);
    }
  }

  switch (modeSelector()) {
    case 0:
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          gb.wipePoint(i, j);
          gb.setLed(i, j, CAR[i][j]);
        }
      }



      break;
    case 1:
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          gb.wipePoint(i, j);
          gb.setLed(i, j, SNAKE[i][j]);
        }
      }
      break;
  }
}

void loop() {
  mainMenu();

}

void gameSnake() {
  if (lenSnake == VICTORY_LENGTH) {
    victory();
  }

  for (int s = 1; s < lenSnake; s++) {
    if (snakeX[0] == snakeX[s] && snakeY[0] == snakeY[s]) {
      fail();
    }
  }
  makeMove();

  gb.clearDisplay();

  move();
  drawSnake();

  drawFruit();

  if (snakeX[0] == AppleX && snakeY[0] == AppleY) {
    lenSnake += 1;
    gb.sound(SCORE);
    for (int a = 0; a < lenSnake; a++) {
      generateApple();

    }

    drawFruit();
  }
  delay(DELAY);
}


void fail() {
  gb.testMatrix(10);
  gb.sound(COLLISION);
  lenSnake = 1;
}

void victory() {
  gb.testMatrix(5);
  delay(1);
  gb.testMatrix(5);
  gb.sound(COLLISION);
  lenSnake = 1;
}
