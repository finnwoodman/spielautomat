#include <arduino.h>
#include <GameData.h>


GameData Games(100,11);

void setup(){
  delay(10000);
  Games.init();
  Games.report(true);
  Games.grab();
  //Games.printData();

  Games.search(5, 7, 5, 10, 1);
  int i = Games.getGame();
}


void loop(){
}
