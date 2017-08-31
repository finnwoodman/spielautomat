
#include <Rotary.h>
#include <ArcadeCollector.h>
#include <Arcade.h>
#include <Voltmeter.h>
#include <AgeSelector.h>
#include <CoinAcceptor.h>
#include <RotarySwitch.h>
#include <SolSound.h>
#include <Toggle.h>
#include <LED_Wrapper.h>
#include <GameData.h>


GameData Games(100,11);
//Hardware
LED_Wrapper Line;
ArcadeCollector arcadeBus(5);
RotarySwitch rPlayers(A8, 10);
RotarySwitch rDuration(A9, 10);
AgeSelector minAge(A7);
AgeSelector maxAge(A6);
Toggle tPilot(11);
Voltmeter vMeter(A2);
CoinAcceptor Coin;
Rotary rotary(33,34);
SolSound solenoid(A3);



void setup(){
  Serial.begin(9600);
  //Arcadebus
  arcadeBus.add(32, 31, &Line, CRGB::Red);
  arcadeBus.add(30, 29, &Line, CRGB::Yellow);
  arcadeBus.add(28, 27, &Line, CRGB::Green);
  arcadeBus.add(26, 25, &Line, CRGB::Blue);
  arcadeBus.add(24,12, &Line, CRGB::White);
  arcadeBus.setBlink(100,5);
  arcadeBus.report(false);

  //Rotary switches
  rPlayers.report(false);
  int _players [] = {1,2,3,4,5,6,7,8,9,10};
  rPlayers.addMapping(_players);
  rDuration.report(false);
  int _duration [] = {60,45,30,20,15,10,5,3,1,0};
  rDuration.addMapping(_duration);
  //AgeSelector
  minAge.setThreshold(2);
  minAge.setSteps(0 , 20 , 50, 130, 200, 350, 750, 1023);
  minAge.setAges(30, 20, 15, 10, 7, 5, 3);
  minAge.report(false);

  maxAge.setThreshold(2);
  maxAge.setSteps(0 , 15 , 50, 120, 220, 400, 750, 1023);
  maxAge.setAges(99, 60, 30, 20, 15, 10, 7);
  maxAge.report(false);

  //Voltmeter
  vMeter.report(false);

  //Coins
  Coin.report(false);
  attachInterrupt(10, interrupt ,RISING);

  //LED
  Line.counterClockwise();
  Line.setColor(CRGB::Blue);

  Line.setArrowSize(7);

  Line.addArrow(19, CRGB::Red);
  Line.addArrow(26, CRGB::Orange);
  Line.addArrow(50, CRGB::Green);
  Line.addArrow(73,CRGB::White);
  Line.setWaveColors(CRGB::White, CRGB::Black);

  Line.refresh();

  //Rotary
  rotary.autoDecreaseSteps(50);
  rotary.setMax(5);
  rotary.report(false);
  rotary.attachVMeter(&vMeter, 60);
  rotary.attachLine(&Line);


  //GameData
  Games.report(false);
  Games.init();
  Games.grab();

  solenoid.adjust(20);
  solenoid.sequence(5, 500);

  //Test Section
  //arcadeBus.test(500);


}


void loop(){
  arcadeBus.refresh();
  rPlayers.refresh();
  rDuration.refresh();
  minAge.refresh();
  maxAge.refresh();
  tPilot.refresh();
  rotary.refresh();
  vMeter.refresh();
  solenoid.refresh();
  Line.line(rotary.getSteps(), rotary.getMaxSteps());
  Line.refresh();
/*  if (Line.getModus() == 1) {
    if (Coin.getBudget(0.2) == true) {
    Serial.println("++++ GAME BEGIN++++");
    Serial.print("Personen: " );
    Serial.println(rPlayers.getMapping());
    Serial.print("Minuten: " );
    Serial.println(rDuration.getMapping());
    Serial.print("Alter von: " );
    Serial.print(minAge.getMin());
    Serial.print(" bis " );
    Serial.println(minAge.getMax());
    Serial.print("Kategorie: " );
    Serial.println(arcadeBus.getActive());
    Serial.println("++++ GAME END ++++");
    Coin.level();
    // Games.search(rPlayers.getPosition(), rDuration.getPosition() , minAge., int maxAge, int _cat);
  }
}*/
}

void interrupt(){
  Coin.increase();
}
