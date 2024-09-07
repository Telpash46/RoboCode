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

int AppleX1;
int AppleY1;
bool Apple1Eaten = false;

int AppleX2;
int AppleY2;
bool Apple2Eaten = false;

int AppleX3;
int AppleY3;
bool Apple3Eaten = false;

int AppleX4;
int AppleY4;
bool Apple4Eaten = false;


int x = 1, y = 0;
int dirX, dirY;
int snakeX[128];
int snakeY[128];
int direction = right;
int lenSnake = 1;
bool state = true;
int EATEN_APPLES = 4;


void setup() {
  // put your setup code here, to run once:

  gb.begin(BOARD_BRIGHTNESS);
  randomSeed(analogRead(2) + analogRead(5));
  Serial.begin(9600);
  Serial.println(EATEN_APPLES);
  generateApple(4, 7);
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

void generateApple(int buffx, int buffy) {

  gb.wipePoint(buffx, buffy);
  if (buffx == AppleX1 && buffy == AppleY1) {
    Apple1Eaten = true;
  }
  if (buffx == AppleX2 && buffy == AppleY2) {
    Apple2Eaten = true;
  }
  if (buffx == AppleX3 && buffy == AppleY3) {
    Apple3Eaten = true;
  }
  if (buffx == AppleX4 && buffy == AppleY4) {
    Apple4Eaten = true;
  }

  if (EATEN_APPLES >= 4) {
    AppleX1 = random(X_MIN, X_MAX);
    AppleY1 = random(Y_MIN, Y_MAX);

    AppleX2 = AppleX1 + 1;
    AppleY2 = AppleY1;

    AppleX3 = AppleX1;
    AppleY3 = AppleY1 + 1;

    AppleX4 = AppleX1 + 1;
    AppleY4 = AppleY1 + 1;

    while (isPartOfSnake(AppleX1, AppleY1)) {
      generateApple(buffx, buffy);
    }
    EATEN_APPLES = 0;
    Apple1Eaten = false;
    Apple2Eaten = false;
    Apple3Eaten = false;
    Apple4Eaten = false;
  }
}

void fail() {
  gb.testMatrix(10);
  gb.sound(COLLISION);
  lenSnake = 1;
  snakeX[0] = 4;
  snakeY[0] = 7;
}

void victory() {
  gb.testMatrix(5);
  delay(1);
  gb.testMatrix(5);
  gb.sound(COLLISION);
  lenSnake = 1;
  snakeX[0] = 4;
  snakeY[0] = 7;
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
    if (!Apple1Eaten) {
      gb.drawPoint(AppleX1, AppleY1);
    }
    if (!Apple2Eaten) {
      gb.drawPoint(AppleX2, AppleY2);
    }
    if (!Apple3Eaten) {
      gb.drawPoint(AppleX3, AppleY3);
    }
    if (!Apple4Eaten) {
      gb.drawPoint(AppleX4, AppleY4);
    }
  } else {
    if (!Apple1Eaten) {
    gb.wipePoint(AppleX1, AppleY1);
    }

    if (!Apple2Eaten) {
    gb.wipePoint(AppleX2, AppleY2);
    }

    if (!Apple3Eaten) {
    gb.wipePoint(AppleX3, AppleY3);
    }

    if (!Apple4Eaten) {
    gb.wipePoint(AppleX4, AppleY4);
    }
    
  }
}

void loop() {
  Serial.println(EATEN_APPLES);
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

  if (snakeX[0] == AppleX1 && snakeY[0] == AppleY1) {
    lenSnake += 1;
    gb.sound(SCORE);
    EATEN_APPLES += 1;
    for (int a = 0; a < lenSnake; a++) {
      generateApple(snakeX[0], snakeY[0]);

    }
  }

  if (snakeX[0] == AppleX2 && snakeY[0] == AppleY2) {
    lenSnake += 1;
    EATEN_APPLES += 1;
    gb.sound(SCORE);
    for (int a = 0; a < lenSnake; a++) {
      generateApple(snakeX[0], snakeY[0]);

    }
  }

  if (snakeX[0] == AppleX3 && snakeY[0] == AppleY3) {
    lenSnake += 1;
    EATEN_APPLES += 1;
    gb.sound(SCORE);
    for (int a = 0; a < lenSnake; a++) {
      generateApple(snakeX[0], snakeY[0]);

    }
  }


  if (snakeX[0] == AppleX4 && snakeY[0] == AppleY4) {
    lenSnake += 1;
    EATEN_APPLES += 1;
    gb.sound(SCORE);
    for (int a = 0; a < lenSnake; a++) {
      generateApple(snakeX[0], snakeY[0]);

    }

  }

  drawFruit();

  delay(DELAY);
}
