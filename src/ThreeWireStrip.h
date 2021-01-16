#ifndef THREE_WIRE_h
#define THREE_WIRE_h

#include <Arduino.h>
#include "FairyLights.h"
#include "ThreeWireStripHalf.h"

// these were fairly arbitrary picks
// it looked good to *our* eyes
#define TW_PWM_MIN  100
#define TW_PWM_MAX 1000

#define pwm_value(x) map(x, 0, 255, TW_PWM_MIN, TW_PWM_MAX)
// #define pwm_value(x) x

class ThreeWireStrip: public FairyLights {
  public:
    ThreeWireStrip(pin center, pin red, pin blue);

    ThreeWireStripHalf *oddStrip();
    ThreeWireStripHalf *evenStrip();

    void setRGB(byte red, byte green, byte blue);

    ThreeWireStripHalf* oddNodes();
    ThreeWireStripHalf* evenNodes();

    // overrides
    void setBlack();
    void nextColor();
    void setColor(fl_color value);
    void setBrightness(byte value);

    void display();
    void display(int approxMs);

    void fade(fl_color fromColor, fl_color toColor);

  private:
    ThreeWireStripHalf* _odd_strip;
    ThreeWireStripHalf* _even_strip;
};

#endif
