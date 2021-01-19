#include "FourWireStrip.h"

FourWireStrip::FourWireStrip(pin red, pin green, pin blue, pin vcc=0)
{
  if (vcc > 0) {
    digitalWrite(vcc, HIGH);
  }
  
  _red_pin = red;
  _green_pin = green;
  _blue_pin = blue;

  _brightness = 255;  

  // set all to white
  _color = White;
  _red = 255;
  _green = 255;
  _blue = 255;
}

// overrides
void FourWireStrip::setBlack()
{
  _red = 0;
  _green = 0;
  _blue = 0;
}

void FourWireStrip::nextColor()
{
  fl_color color = (fl_color)((_color+1) % fl_color::ColorCount);
  if (color == Black) color = Red;
  setColor(color);
}

void FourWireStrip::setColor(fl_color value)
{
  if (value != ColorCount) {
    _color = value;
  }
  switch (value) {
    case Black:   setRGB(  0,   0,   0); break;
    case Red:     setRGB(255,   0,   0); break;
    case Green:   setRGB(  0, 255,   0); break;
    case Yellow:  setRGB(255, 255,   0); break;
    case Blue:    setRGB(  0,   0, 255); break;
    case Magenta: setRGB(255,   0, 255); break;
    case Cyan:    setRGB(  0, 255, 255); break;
    case White:   setRGB(255, 255, 255); break;
  }
}

void FourWireStrip::setRGB(byte red, byte green, byte blue)
{
  _red = red; _green = green; _blue = blue;
}

void FourWireStrip::setBrightness(byte value)
{
  _brightness = value;
}

void FourWireStrip::display()
{
  analogWrite(_red_pin, (255 - _red));
  analogWrite(_green_pin, (255 - _green));
  analogWrite(_blue_pin, (255 - _blue));
}

void FourWireStrip::display(int approxMs)
{
  unsigned long time = millis();

  while (millis()-time < approxMs) {
    display();
  }
}

void FourWireStrip::fade(fl_color fromColor, fl_color toColor) {

}
