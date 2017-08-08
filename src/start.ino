
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
/*ArcadeCollector arcadeBus(5);
RotarySwitch rPlayers(A8, 10);
RotarySwitch rDuration(A9, 10);
AgeSelector sAge(A6, A7);
Toggle tPilot(11);
Voltmeter vMeter(A2);
CoinAcceptor Coin;
Rotary rotary(34,35);
SolSound solenoid(17);
LED_Wrapper LED();*/


void setup(){
  delay(10000);
  Serial.println("Beginn Setup");
/*  //Arcadebus
  arcadeBus.add(31, 32);
  arcadeBus.add(29, 30);
  arcadeBus.add(27, 28);
  arcadeBus.add(25, 26);
  arcadeBus.add(24,12);
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
  vMeter.test();
  //Rotary
  rotary.autoDecrease(2000);
  rotary.report(false);
  //LED*/


  //GameData
  Games.report(true);
  Games.init();
  Games.grab();
  Games.printData();
  Games.print(0);

  //Test Section
  //arcadeBus.test(500);

}


void loop(){
/*  arcadeBus.refresh();
  rPlayers.refresh();
  rDuration.refresh();
  tPilot.refresh();
  vMeter.refresh();
  rotary.refresh();
  solenoid.refresh();*/

}
