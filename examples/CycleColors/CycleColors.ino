// this example shows how the same interface is offered for the differnt light strips
// however, the inherent differences in how they work may yield weird results when 
// running together like this (in this case, each one will look odd when the other is
// displayed)

#include <FairyLights.h>

// for 2-wire / M1359L light strip
#define VCC_PIN 6

pin pins_2wire[1] = { VCC_PIN };
FairyLights *strip2 = FairyLightsFactory( TwoWire, pins_2wire);

// for 3 wire light strip
#define CENTER_PIN 12
#define RED_PIN 11
#define BLUE_PIN 10

pin pins_3wire[3] = { CENTER_PIN, RED_PIN, BLUE_PIN };
FairyLights *strip3 = FairyLightsFactory( ThreeWire, pins_3wire);

void setup() {
  strip2->setColor(Black);
  strip3->setColor(Black);
}

void loop() {
  strip2->nextColor();
  strip2->display(1000);

  strip3->nextColor();
  strip3->display(1000);
}
