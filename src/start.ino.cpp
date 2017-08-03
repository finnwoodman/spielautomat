# 1 "/var/folders/38/phyg322s7tl085xcjvqqpwwh0000gn/T/tmpt7nohy"
#include <Arduino.h>
# 1 "/Users/Fejngold/Documents/Arduino/Spielautomat/src/start.ino"
#include <arduino.h>
#include <GameData.h>


GameData Games(100,11);
void setup();
void loop();
#line 7 "/Users/Fejngold/Documents/Arduino/Spielautomat/src/start.ino"
void setup(){
  delay(10000);
  Games.init();
  Games.report(true);
  Games.grab();


  Games.search(5, 7, 5, 10, 1);
  int i = Games.getGame();
}


void loop(){
}