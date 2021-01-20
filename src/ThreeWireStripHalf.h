#ifndef THREE_WIRE_HALF_h
#define THREE_WIRE_HALF_h

#include <Arduino.h>
#include "FairyLights.h"

// these were fairly arbitrary picks
// it looked good to *our* eyes
#define TW_PWM_MIN  100
#define TW_PWM_MAX 1000

#define pwm_value(x) map(x, 0, 255, TW_PWM_MIN, TW_PWM_MAX)
// #define pwm_value(x) x

class ThreeWireStripHalf: public FairyLights {
  public:
    ThreeWireStripHalf(pin left, pin center, pin right, bool reversed);

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
    bool _reversed;

    pin _left_pin;
    pin _center_pin;
    pin _right_pin;

    unsigned long _brightness;
    
    // the underlying RGB values might get out of 
    // sync from the "color" - this is expected    
    fl_color _color;
    byte _red;
    byte _green;
    byte _blue;

    void displayBlack();

    void displayRed();
    void displayGreen();
    void displayBlue();
};

#endif
