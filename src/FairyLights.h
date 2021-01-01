#ifndef FL_h
#define FL_h

#include <Arduino.h>

#define M1359L_PACKET_SIZE 8
#define M1359L_PACKET_DELAY 20

// these were fairly arbitrary picks
// it looked good to *our* eyes
#define M1359L_PWM_MIN 0
#define M1359L_PWM_MAX 15000

#define FL_OFF 0
#define FL_RED 1
#define FL_GREEN 2
#define FL_YELLOW 3
#define FL_BLUE 4
#define FL_PURPLE 5
#define FL_CYAN 6
#define FL_WHITE 7

#define FL_COLOR_COUNT 8

typedef int pin;

enum fl_type { M1359L };

enum fl_color {
  Black,
  Red,
  Green,
  Yellow,
  Blue,
  Purple,
  Cyan,
  White
};

class FairyLights
{
  public:
    FairyLights(fl_type lightType, pin vcc);
    
    void pulse8(byte pattern[]);
    void quickPulse(byte pattern[], int len, int delayMuSec);

    void reset();
    void setBlack();
    void nextColor();
    void setColor(fl_color value);
    void setBrightness(uint8_t value);

    void display();
    void display(int approxMs);

    void fade(fl_color fromColor, fl_color toColor);

  private:
    int _vcc_pin;
    int _brightness;
    uint8_t _color; // actually, 3 bits

    void pulse();
    void pulse(int count);
};

#endif
