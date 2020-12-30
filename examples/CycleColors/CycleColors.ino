
#define VCC_PIN 13

#include <M1359.h>

M1359Strip strip(VCC_PIN);

void setup() {
  strip.on();
  strip.setColor(M1359_BLUE);
}

void loop() {
  static int color = M1359_BLUE;

  strip.setColor((color++)%8);

  delay(1000);
}

