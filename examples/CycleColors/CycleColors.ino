
#define VCC_PIN 13

#include <FairlyLights.h>

FairlyLights strip(VCC_PIN, FL_M1359L);

void setup() {
  strip.on();
  strip.setColor(FL_BLUE);
}

void loop() {
  static int color = FL_BLUE;

  strip.setColor((color++)%8);

  delay(1000);
}

