
#include <Rotary.h>
#include <ArcadeCollector.h>

 Rotary rotary(0,1);
 ArcadeCollector arcadeBus(3);


 void setup() {
 arcadeBus.report(true);
 arcadeBus.add(0,1);
 arcadeBus.add(2,3);
 arcadeBus.add(4,5);
 arcadeBus.setBlink(100,4);
 rotary.autoDecrease(2000);

 }

void loop(){
   rotary.refresh();
   arcadeBus.refresh();


}
