
#include <Rotary.h>
#include <ArcadeCollector.h>
#include <Arcade.h>
#include <Voltmeter.h>
#include <AgeSelector.h>
#include <CoinAcceptor.h>

 //Rotary rotary(0,1);
 //ArcadeCollector arcadeBus(2);
 //Voltmeter vMeter(2);
 AgeSelector Age(A9, A8);
 //CoinAcceptor Coin;
//Arcade Button(0,1);

 /*void interrupt(){
   Coin.increase();
 }*/

 void setup() {
 /*arcadeBus.add(0, 1);
 arcadeBus.report(true);
 arcadeBus.setBlink(100, 10);*/
 //Button.blink_on(100, 10);
 //rotary.autoDecrease(2000);
 //rotary.report(true);

 //delay(5000);
 //vMeter.set(100);
 Age.setThreshold(5);
 Age.setSteps(0 , 200 , 400, 600, 800, 900, 1023);
 Age.setAges(3 , 5, 8, 12, 16);
 Age.report(true);

 //Coin.report(true);
 //Coin.setInterval(200);
 //attachInterrupt(0, interrupt ,RISING);
// attachInterrupt(0, CallCoin, RISING);*/

 }



void loop(){
  Age.refresh();
  delay(250);
//rotary.refresh();
//Button.refresh();
}
