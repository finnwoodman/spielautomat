
#include <Rotary.h>
#include <ArcadeCollector.h>
#include <Arcade.h>
#include <Voltmeter.h>
#include <AgeSelector.h>
#include <CoinAcceptor.h>
#include <RotarySwitch.h>
#include <SolSound.h>
//#include <LED_Wrapper.h>




 Rotary rotary(34,35);
 ArcadeCollector arcadeBus(4);


 RotarySwitch rSwitch(A8, 10);
 SolSound SolSound(17);
 AgeSelector Age(A6, A7);
 Voltmeter vMeter(A2);
 //CoinAcceptor Coin;
//Arcade Button(0,1);
//LED_Wrapper LED(2, 24);
 /*void interrupt(){
   Coin.increase();
 }*/

 void setup() {
 //rSwitch.report(true);
 arcadeBus.add(31, 32);
 arcadeBus.add(29, 30);
 arcadeBus.add(27, 28);
 arcadeBus.add(25, 26);
 arcadeBus.report(true);
 arcadeBus.setBlink(100, 10);
 rotary.autoDecrease(2000);
 rotary.report(true);
 rSwitch.report(true);
 vMeter.set(255);
 vMeter.refresh();
 delay(5000);
 //LED.report(true);




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
  //arcadeBus.refresh();
  /*switch (arcadeBus.getActive()) {
    case 0:
      vMeter.set(50);
      SolSound.bell();
      break;
    case 1:
      vMeter.set(100);
      break;
    case 2:
      vMeter.set(150);
      break;
    case 3:
      vMeter.set(200);
      break;
  }*/
  //vMeter.refresh();
  //SolSound.refresh();

  rSwitch.refresh();

 //Age.refresh();
//  vMeter.set(100);
//  vMeter.refresh();
  delay(25);






//  delay(1000);
//rotary.refresh();
//Button.refresh();

}
