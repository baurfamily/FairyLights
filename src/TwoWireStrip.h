#ifndef M1359L_h
#define M1359L_h

#include <Arduino.h>

#include "FairyLights.h"


// these were fairly arbitrary picks
// it looked good to *our* eyes
#define TW_PWM_MIN  1000
#define TW_PWM_MAX 15000

#define M1359L_PACKET_SIZE 8
#define M1359L_PACKET_DELAY 20

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
    byte _color; // actually, 3 bits

    unsigned long _brightness;
    
    void pulse();
    void pulse(int count);
};

#endif
