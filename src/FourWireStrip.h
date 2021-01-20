#ifndef FOUR_WIRE_H
#define FOUR_WIRE_H

#include <Arduino.h>
#include "FairyLights.h"

struct RGB {
  byte red;
  byte green;
  byte blue;
};

class FourWireStrip: public FairyLights {
  public:
    FourWireStrip(pin red, pin green, pin blue, pin vcc);

    void FourWireStrip::setRGB(RGB rgb);
    void setRGB(byte red, byte green, byte blue);

    // overrides
    void setBlack();
    void nextColor();
    void setColor(fl_color value);
    void setBrightness(byte value);

    void display();
    void display(int approxMs);

    void fade(fl_color fromColor, fl_color toColor, int approxMs);

  private:
    pin _vcc_pin;
    pin _red_pin;
    pin _green_pin;
    pin _blue_pin;

    unsigned long _brightness;
    
    // the underlying RGB values might get out of 
    // sync from the "color" - this is expected    
    fl_color _color;
    RGB _rgb;
};

#endif
