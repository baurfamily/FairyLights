#ifndef FL_h
#define FL_h


#include <Arduino.h>

typedef int pin;

enum fl_type {
  M1359L,
  TwoWire,
  ThreeWire,
  TypeCount
};

// bad coupling: this order is important to
// the TwoWireStrip class, so keep it this way!
enum fl_color {
  Black,
  Red,
  Green,
  Yellow,
  Blue,
  Magenta,
  Cyan,
  White,
  ColorCount
};


class FairyLights
{
  public:
    //FairyLights(fl_type lightType, byte pins[]);
    // virtual ~FairyLights() { };
    
    virtual void setBlack() { };
    virtual void nextColor() { };

    // generally speaking, "named" colors will be more accurate
    virtual void setColor(fl_color value) { };
    // virtual void setRGB(byte red, byte green, byte blue);

    virtual void setBrightness(byte value) { };

    // depending on the type, this may be transient
    virtual void display() { };

    // this is the only guarented way to get a color
    virtual void display(int approxMs) { };

    // fades from one color to another
    virtual void fade(fl_color fromColor, fl_color toColor) { };
};

FairyLights* FairyLightsFactory(fl_type lightType, pin pins[]);

void pinOff(pin p);
void pinLow(pin p);
void pinHigh(pin p);
void pinHigh(pin p, byte val);

#endif
