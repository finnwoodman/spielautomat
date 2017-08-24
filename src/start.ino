
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
AgeSelector sAge(A6, A7);
Toggle tPilot(11);
Voltmeter vMeter(A3);
CoinAcceptor Coin;
Rotary rotary(33,34);
SolSound solenoid(A2);



void setup(){
  Serial.begin(9600);
  //Arcadebus
  arcadeBus.add(32, 31);
  arcadeBus.add(30, 29);
  arcadeBus.add(28, 27);
  arcadeBus.add(26, 25);
  arcadeBus.add(24,12);
  arcadeBus.setBlink(100,5);
  arcadeBus.report(false);
  //Rotary switches
  rPlayers.report(false);
  rDuration.report(false);
  //AgeSelector
  sAge.setThreshold(5);
  sAge.setSteps(0 , 200 , 400, 600, 800, 900, 1023);
  sAge.setAges(3 , 5, 8, 12, 16);
  sAge.report(false);
  //Voltmeter
  vMeter.report(false);

  //Rotary
  rotary.autoDecreaseSteps(150);
  rotary.setMax(3);
  rotary.report(false);
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


  Line.tint(CRGB::Yellow);
  Line.refresh();


  //GameData
  Games.report(true);
  Games.init(false);
  Games.grab();
  //Games.print(0);

  //Test Section
  //arcadeBus.test(500);


}


void loop(){
  arcadeBus.refresh();
  rPlayers.refresh();
  rDuration.refresh();
  sAge.refresh();
  tPilot.refresh();
  vMeter.set(map(rotary.getSpeed(), 0,200,0,255));
  vMeter.refresh();
  rotary.refresh();
  solenoid.refresh();

  if (rotary.getSteps() > rotary.getMaxSteps()) {
    Line.setModus(1);
  }

  if (rotary.getSteps() < 1) {
    Line.setModus(2);
  }

  if ((rotary.getSteps() > 1) && (rotary.getSteps() < rotary.getMaxSteps())) {
    Line.setModus(0);
  }

  Line.line(rotary.getSteps(), rotary.getMaxSteps());
  Line.refresh();

}

void interrupt(){
  Coin.increase();
}
