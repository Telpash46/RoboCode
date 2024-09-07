#include <Blocks.h>
#include <GameBoy.h>
GameBoy gb;

int car_speed = 100;
int enemy_x = 2;

int mycar_x = 2;
int mycar_y = 12;


void setup() {
  // put your setup code here, to run once:

  gb.begin(0);
  playerCar(mycar_x, mycar_y);
}


void loop() {
  
  // put your main code here, to run repeatedly:

  //mainRacing();

  GameOver();
}



int UpdateEnemyPos () {
  randomSeed(analogRead(A5));
  
  int buff = random(1,10);
  
   if (buff <= 5) {
    buff = 2;
   } else {
    buff = 5;
   }
  return buff;
  }

void PlayerCarController () {
  switch (gb.getKey()) {
    case 4:
      ClearPlayerCar(5, 12);
      playerCar(2, 12);
      break;

    case 5:
      ClearPlayerCar(2, 12);
      playerCar(5, 12);
      break;

    default:
      break;
  }}

void mainRacing () {
  enemy_x = UpdateEnemyPos();
  
  
  for (int enemy_y = 0; enemy_y < 16; enemy_y++) {
  


  createLine(enemy_y);
  createLine(enemy_y + 5);
  createLine(enemy_y + 10);
  createLine(enemy_y + 15);
  
  enemyCar(enemy_x, enemy_y);
  
  PlayerCarController();
  
  delay(car_speed);
  

  
  clearLine(enemy_y);
  clearLine(enemy_y + 5);
  clearLine(enemy_y + 10);
  clearLine(enemy_y + 15);


  ClearEnemyCar(enemy_x, enemy_y);
  }

}


void createLine (int y) {
  gb.drawPoint(0, y);
  gb.drawPoint(0, y + 1);
  gb.drawPoint(0, y + 2);

  gb.drawPoint(7, y);
  gb.drawPoint(7, y + 1);
  gb.drawPoint(7, y + 2);
}

void clearLine (int y) {
  gb.wipePoint(0, y);
  gb.wipePoint(0, y + 1);
  gb.wipePoint(0, y + 2);

  gb.wipePoint(7, y);
  gb.wipePoint(7, y + 1);
  gb.wipePoint(7, y + 2);
}



void GameOver () {
  gb.drawPoint(6, 1);
  gb.drawPoint(5, 1);
  gb.drawPoint(4, 1);
  gb.drawPoint(3, 1);
  gb.drawPoint(2, 1);
  gb.drawPoint(1, 1);
  gb.drawPoint(1, 2);
  gb.drawPoint(1, 3);
  gb.drawPoint(1, 4);
  gb.drawPoint(1, 5);
  gb.drawPoint(1, 6);
  gb.drawPoint(2, 6);
  gb.drawPoint(3, 6);
  gb.drawPoint(4, 6);
  gb.drawPoint(5, 6);
  gb.drawPoint(6, 6);
  gb.drawPoint(6, 5);
  gb.drawPoint(6, 4);
  gb.drawPoint(5, 4);
  gb.drawPoint(4, 4);
  gb.drawPoint(3, 4);



  gb.drawPoint(1, 9);
  gb.drawPoint(2, 9);
  gb.drawPoint(3, 9);
  gb.drawPoint(4, 9);
  gb.drawPoint(5, 9);
  gb.drawPoint(6, 9);

  gb.drawPoint(6, 10);
  gb.drawPoint(6, 11);
  gb.drawPoint(6, 12);
  gb.drawPoint(6, 13);
  gb.drawPoint(6, 14);

  gb.drawPoint(1, 10);
  gb.drawPoint(1, 11);
  gb.drawPoint(1, 12);
  gb.drawPoint(1, 13);
  gb.drawPoint(1, 14);

  gb.drawPoint(2, 14);
  gb.drawPoint(3, 14);
  gb.drawPoint(4, 14);
  gb.drawPoint(5, 14);
  gb.drawPoint(6, 14);
}





void enemyCar(int x, int y) {
  gb.drawPoint(x, y);
  gb.drawPoint(x, y - 1);
  gb.drawPoint(x - 1, y - 1);
  gb.drawPoint(x + 1, y - 1);
  gb.drawPoint(x, y - 2);
  gb.drawPoint(x - 1, y - 3);
  gb.drawPoint(x + 1, y - 3);
  }

void playerCar(int x, int y) {
  gb.drawPoint(x, y);
  gb.drawPoint(x, y + 1);
  gb.drawPoint(x - 1, y + 1);
  gb.drawPoint(x + 1, y + 1);
  gb.drawPoint(x, y + 2);
  gb.drawPoint(x - 1, y + 3);
  gb.drawPoint(x + 1, y + 3);
  }

void ClearPlayerCar(int x, int y) {
  gb.wipePoint(x, y);
  gb.wipePoint(x, y + 1);
  gb.wipePoint(x - 1, y + 1);
  gb.wipePoint(x + 1, y + 1);
  gb.wipePoint(x, y + 2);
  gb.wipePoint(x - 1, y + 3);
  gb.wipePoint(x + 1, y + 3);
  }

void ClearEnemyCar(int x, int y) {
  gb.wipePoint(x, y);
  gb.wipePoint(x, y - 1);
  gb.wipePoint(x - 1, y - 1);
  gb.wipePoint(x + 1, y - 1);
  gb.wipePoint(x, y - 2);
  gb.wipePoint(x - 1, y - 3);
  gb.wipePoint(x + 1, y - 3);
  /*2, 6*/
  }
