
#include <Rotary.h>
#include <ArcadeCollector.h>
#include <Voltmeter.h>
#include <AgeSelector.h>

 Rotary rotary(0,1);
 ArcadeCollector arcadeBus(3);
 Voltmeter vMeter(2);
 AgeSelector Age(A9, A8);

 void setup() {

 rotary.autoDecrease(2000);
 rotary.report(true);
 delay(5000);
 vMeter.set(100);
 Age.setThreshold(5);
 Age.setSteps(0 , 200 , 400, 600, 800, 900, 1023);
 Age.setAges(3 , 5, 8, 12, 16);
 }

void loop(){
  delay(100);
  vMeter.set(100);
  vMeter.refresh();
  Age.refresh();
}
