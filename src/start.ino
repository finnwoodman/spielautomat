#include <arduino.h>
#include <GameData.h>


GameData Games(100,11);

void setup(){
  delay(10000);
  Games.init();
  Games.report(true);
  Games.grab();

  Games.printData();

}


void loop(){
}
