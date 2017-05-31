
#include <Rotary.h>
#include <ArcadeCollector.h>
#include <Voltmeter.h>

 Rotary rotary(0,1);
 ArcadeCollector arcadeBus(3);
 Voltmeter vMeter(2);

 void setup() {

 rotary.autoDecrease(2000);
 delay(5000);
 vMeter.set(200, 50);
 }

void loop(){
  vMeter.refresh();
}
