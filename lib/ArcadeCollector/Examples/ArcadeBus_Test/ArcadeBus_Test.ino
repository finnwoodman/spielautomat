#include<Arcade.h>
#include<LED_Wrapper.h>
#include<FastLED.h>
#include<SolSound.h>
#include<ArcadeCollector.h>

ArcadeCollector arcadeBus(4);

void setup(){
  //arcadeBus.add(32, 31);
  arcadeBus.add(30, 29);
  arcadeBus.add(28, 27);
  arcadeBus.add(26, 25);
  arcadeBus.add(24,12);
  arcadeBus.setBlink(100,5);
  arcadeBus.report(true);
}


void loop(){
  arcadeBus.refresh();
}
