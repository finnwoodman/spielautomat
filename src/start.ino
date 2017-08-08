
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
ArcadeCollector arcadeBus(5);
RotarySwitch rPlayers(A8, 10);
RotarySwitch rDuration(A9, 10);
AgeSelector sAge(A6, A7);
Toggle tPilot(11);
Voltmeter vMeter(A3);
//CoinAcceptor Coin;
Rotary rotary(33,34);
SolSound solenoid(16);
//LED_Wrapper LED();


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
  rotary.autoDecrease(5000);
  rotary.report(true);
  //LED*/


  //GameData
  Games.report(false);
  Games.init();
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
  vMeter.refresh();
  rotary.refresh();
  solenoid.refresh();


}
