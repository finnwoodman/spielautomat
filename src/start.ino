
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


GameData Games(130,12);
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
  arcadeBus.add(32, 31);
  arcadeBus.add(30, 29);
  arcadeBus.add(28, 27);
  arcadeBus.add(26, 25);
  arcadeBus.add(24,12);
  arcadeBus.setBlink(100,5);
  arcadeBus.report(true);

  //rPlayer
  rPlayers.report(false);
  int _players [] = {10,9,8,7,6,5,4,3,2,1};
  rPlayers.addMapping(_players);
  rPlayers.addCorrector(20);

  //rDuration
  rDuration.report(false);
  int _duration [] = {60,45,30,20,15,10,5,3,1,0};
  rDuration.addCorrector(20);
  rDuration.addMapping(_duration);

  //minAge
  minAge.setThreshold(2);
  minAge.setSteps(0 , 20 , 50, 130, 200, 350, 750, 1023);
  minAge.setAges(30, 20, 15, 10, 7, 5, 3);
  minAge.report(false);

  //maxAge
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
  Line.setArrows(19, 26, 50, 73, 99);
//  Line.setArrows(0,73,50,26,19);
  Line.setWaveColors(CRGB::White, CRGB::Black);
  Line.refresh();

  //Rotary
  rotary.autoDecreaseSteps(12);
  rotary.setMax(15);
  rotary.report(false);
  rotary.attachVMeter(&vMeter, 60);
  rotary.attachLine(&Line);



  //GameData
  Games.report(false);
  Games.init(false);
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
  vMeter.refresh();
  solenoid.refresh();
  Line.line(rotary.getSteps(), rotary.getMaxSteps());
  Line.refresh();
  rotary.refresh();


  if (Line.getModus() == 1) {
    if (Coin.getBudget(0.2) >= true) {
/*    Serial.println("++++ GAME BEGIN++++");
    Serial.print("Personen: " );
    Serial.println(rPlayers.getMapping());
    Serial.print("Minuten: " );
    Serial.println(rDuration.getMapping());
    Serial.print("Alter von: " );
    Serial.print(minAge.getValue());
    Serial.print(" bis " );
    Serial.println(maxAge.getValue());
    Serial.print("Kategorie: " );
    Serial.println(arcadeBus.getActive()+1);
    Serial.print("mit Ball: " );
    Serial.println(tPilot.get());
    Serial.print("Name: " );
    Serial.println();
    Serial.println("++++ GAME END ++++");
    Games.search(rPlayers.getPosition(), rDuration.getMapping(),minAge.getValue(),maxAge.getValue(),arcadeBus.getActive()+1, tPilot.get());
    Serial.println("++++ GAME IS++++");
    Serial.println(Games.getGame());*/
    solenoid.bell();
    solenoid.refresh();
    Games.print(Games.getGame());
    solenoid.sequence(3, 750);
    Coin.reset();
    rotary.level();

  }
}
}

void interrupt(){
  Coin.increase();
}
