#include <Button.h>
#include <Rotary.h>

 Rotary rotary(0,1);
 Button button(2, PULLUP);

 void setup() {
 rotary.report(true);
 rotary.autoDecrease(2000);

 }

void loop(){
   rotary.refresh();

}
