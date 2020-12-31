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
typedef uint8_t FLColor;

enum FLType { M1359L };

class FairyLights
{
  public:
    FairyLights(FLType lightType, pin vcc);
    void pulseOnce();
    void pulse(int count);
    
    //  static int redFromReset[PACKET_SIZE] = { 1, 1, 0, 0, 0, 0, 0, 0 };
    //  static int resetFromRed[PACKET_SIZE] = { 1, 1, 1, 1, 1, 1, 0, 0 };
    void pulse8(int pattern[]);
    void quickPulse(byte pattern[], int len, int delayMuSec);

    void setColor(FLColor value);
    void setBrightness(uint8_t value);

    void on();
    void off();
    void reset();
    void display();
    void display(int approxMs);

    void fade(FLColor fromColor, FLColor toColor);

  private:
    int _vcc_pin;
    int _brightness;
    uint8_t _color; // actually, 3 bits
    bool _lit;
};

#endif
