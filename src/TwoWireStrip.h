#ifndef TWO_WIRE_h
#define TWO_WIRE_h

#include <Arduino.h>

#include "FairyLights.h"

#define TWO_WIRE_PACKET_SIZE 8
#define TWO_WIRE_PACKET_DELAY 20

// these were fairly arbitrary picks
// it looked good to *our* eyes
#define TWO_WIRE_PWM_MIN 0
#define TWO_WIRE_PWM_MAX 15000

class TwoWireStrip: public FairyLights {
  public:
    TwoWireStrip(pin vcc);
    
    void pulse8(byte pattern[]);
    void quickPulse(byte pattern[], int len, int delayMuSec);

    // overrides
    void reset();
    void setBlack();
    void nextColor();
    void setColor(fl_color value);
    void setBrightness(byte value);

    void display();
    void display(int approxMs);

    void fade(fl_color fromColor, fl_color toColor);

  private:
    byte _vcc_pin;
    byte _brightness;
    byte _color; // actually, 3 bits

    void pulse();
    void pulse(int count);
};

#endif
