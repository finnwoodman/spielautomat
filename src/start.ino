
#include <Rotary.h>
#include <ArcadeCollector.h>
#include <Arcade.h>
#include <Voltmeter.h>
#include <AgeSelector.h>
#include <CoinAcceptor.h>
#include <RotarySwitch.h>
#include <SolSound.h>

 //Rotary rotary(0,1);
 //ArcadeCollector arcadeBus(2);
// Voltmeter vMeter(2);
int selectorPin;
int numOfSteps;
float divider;
//RotarySwitch rSwitch(A9, 10);
SolSound SolSound(0);
 //AgeSelector Age(A9, A8);
 //CoinAcceptor Coin;
//Arcade Button(0,1);

 /*void interrupt(){
   Coin.increase();
 }*/

 void setup() {
SolSound.bell();
SolSound.bell();
SolSound.bell();
 //rSwitch.report(true);
 /*arcadeBus.add(0, 1);
 arcadeBus.report(true);
 arcadeBus.setBlink(100, 10);*/
 //Button.blink_on(100, 10);
 //rotary.autoDecrease(2000);
 //rotary.report(true);

 delay(5000);
 //vMeter.set(100);

 /*Age.setThreshold(5);
 Age.setSteps(0 , 200 , 400, 600, 800, 900, 1023);
 Age.setAges(3 , 5, 8, 12, 16);
 Age.report(true);*/

 //Coin.report(true);
 //Coin.setInterval(200);
 //attachInterrupt(0, interrupt ,RISING);
// attachInterrupt(0, CallCoin, RISING);*/

 }



void loop(){
SolSound.refresh();
//  Age.refresh();
//  vMeter.set(100);
//  vMeter.refresh();
//  delay(1000);
//  vMeter.set(255);
//  vMeter.refresh();
//  delay(1000);
//rotary.refresh();
//Button.refresh();
}
