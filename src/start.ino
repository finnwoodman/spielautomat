
#include <Rotary.h>
#include <ArcadeCollector.h>
#include <Voltmeter.h>
#include <AgeSelector.h>
#include <CoinAcceptor.h>

 Rotary rotary(0,1);
 ArcadeCollector arcadeBus(3);
 Voltmeter vMeter(2);
 AgeSelector Age(A9, A8);
 CoinAcceptor Coin;

 void interrupt(){
   Coin.increase();
 }

 void setup() {

 rotary.autoDecrease(2000);
 rotary.report(true);
 delay(5000);
 vMeter.set(100);
 Age.setThreshold(5);
 Age.setSteps(0 , 200 , 400, 600, 800, 900, 1023);
 Age.setAges(3 , 5, 8, 12, 16);
 Coin.report(true);
 Coin.setInterval(200);
 attachInterrupt(0, interrupt ,RISING);
// attachInterrupt(0, CallCoin, RISING);

 }



void loop(){
  delay(100);
  vMeter.refresh();
  Age.refresh();
}
