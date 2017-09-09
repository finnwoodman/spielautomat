# 1 "/var/folders/38/phyg322s7tl085xcjvqqpwwh0000gn/T/tmpQRXAQm"
#include <Arduino.h>
# 1 "/Users/Fejngold/Documents/Arduino/Spielautomat/src/start.ino"

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
void setup();
void loop();
void interrupt();
#line 31 "/Users/Fejngold/Documents/Arduino/Spielautomat/src/start.ino"
void setup(){
  Serial.begin(9600);

  arcadeBus.add(32, 31, &Line, CRGB::Red);
  arcadeBus.add(30, 29, &Line, CRGB::Gold);
  arcadeBus.add(28, 27, &Line, CRGB::Lime);
  arcadeBus.add(26, 25, &Line, CRGB::RoyalBlue);
  arcadeBus.add(24,12, &Line, CRGB::White);
  arcadeBus.setBlink(100,5);
  arcadeBus.report(false);


  rPlayers.report(false);
  int _players [] = {3,2,1,10,9,8,7,6,5,4};
  rPlayers.addMapping(_players);
  rPlayers.addCorrector(20);


  rDuration.report(false);
  int _duration [] = {45,30,20,15,10,5,3,1,0,60};
  rDuration.addCorrector(20);
  rDuration.addMapping(_duration);


  minAge.setThreshold(2);
  minAge.setSteps(0 , 20 , 50, 130, 200, 350, 750, 1023);
  minAge.setAges(30, 20, 15, 10, 7, 5, 3);
  minAge.report(false);


  maxAge.setThreshold(2);
  maxAge.setSteps(0 , 15 , 50, 120, 220, 400, 750, 1023);
  maxAge.setAges(99, 60, 30, 20, 15, 10, 7);
  maxAge.report(false);


  vMeter.report(false);


  Coin.report(false);
  attachInterrupt(10, interrupt ,RISING);


  Line.counterClockwise();
  Line.setColor(CRGB::Blue);

  Line.setArrowSize(7);

  Line.addArrow(19, CRGB::Grey);
  Line.addArrow(26, CRGB::Grey);
  Line.addArrow(50, CRGB::Grey);
  Line.addArrow(73,CRGB::Grey);
  Line.setArrows(19, 26, 50, 73, 99);
  Line.setWaveColors(CRGB::Amethyst, CRGB::Green);

  Line.refresh();


  rotary.autoDecreaseSteps(12);
  rotary.setMax(2);
  rotary.report(false);
  rotary.attachVMeter(&vMeter, 60);
  rotary.attachLine(&Line);
  rotary.attachSolenoid(&solenoid);




  Games.report(true);
  Games.init();
  Games.grab();
  solenoid.adjust(20);





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

  if (Line.getModus() == 2) {
    rotary.autoPauseIgnore(false);
  }

  if (Line.getModus() == 1) {
    if (Coin.getBudget(0.2) >= true) {
    Serial.println("++++ GAME BEGIN++++");
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
    Serial.println(Games.getGame());
    solenoid.bell();
    solenoid.refresh();
    Games.print(Games.getGame());
    solenoid.sequence(3, 750);
    Coin.reset();
    rotary.autoPauseIgnore(true);
  }
}
}

void interrupt(){
  Coin.increase();
}