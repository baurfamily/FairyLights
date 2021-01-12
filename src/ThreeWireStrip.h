#ifndef FOUR_WIRE_h
#define FOUR_WIRE_h

#include <Arduino.h>
#include "FairyLights.h"

// these were fairly arbitrary picks
// it looked good to *our* eyes
#define TW_PWM_MIN  100
#define TW_PWM_MAX 1000

#define pwm_value(x) map(x, 0, 255, TW_PWM_MIN, TW_PWM_MAX)
// #define pwm_value(x) x

class ThreeWireStrip: public FairyLights {
  public:
    ThreeWireStrip(pin center, pin red, pin blue);
    
    void reset();

    void nextColorOdd();
    void nextColorEven();

    void setColorOdd(fl_color value);
    void setColorEven(fl_color value);

    void setRGB(byte red, byte green, byte blue);
    void setRGBOdd(byte red, byte green, byte blue);
    void setRGBEven(byte red, byte green, byte blue);

    // overrides
    void setBlack();
    void nextColor();
    void setColor(fl_color value);
    void setBrightness(byte value);

    void display();
    void display(int approxMs);

    void fade(fl_color fromColor, fl_color toColor);

  private:
    pin _center_pin;
    pin _red_pin;
    pin _blue_pin;

    unsigned long _brightness;
    
    // the underlying RGB values might get out of 
    // sync from the "color" - this is expected    
    fl_color _color_odd;
    byte _red_odd;
    byte _green_odd;
    byte _blue_odd;

    fl_color _color_even;
    byte _red_even;
    byte _green_even;
    byte _blue_even;

    void displayBlackOdd();
    void displayBlackEven();

    void displayRedOdd();
    void displayRedEven();

    void displayGreenOdd();
    void displayGreenEven();

    void displayBlueOdd();
    void displayBlueEven();
};

#endif
