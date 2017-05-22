#include <Rotary.h>

 Rotary rotary(0,1);

 void setup() {
 rotary.report(true);
 rotary.autoDecrease(2000);
 }

void loop(){
   rotary.refresh();
}
