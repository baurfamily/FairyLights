#include "ThreeWireStrip.h"

ThreeWireStrip::ThreeWireStrip(pin left, pin center, pin right)
{
  _odd_strip = new ThreeWireStripHalf(left, center, right, false);
  _even_strip = new ThreeWireStripHalf(left, center, right, true);
}

ThreeWireStripHalf* ThreeWireStrip::oddNodes()
{
  return _odd_strip;
}

ThreeWireStripHalf* ThreeWireStrip::evenNodes()
{
  return _even_strip;
}

// overrides
void ThreeWireStrip::setBlack()
{
  _odd_strip->setBlack();
  _even_strip->setBlack();
}

void ThreeWireStrip::nextColor()
{
  _odd_strip->nextColor();
  _even_strip->nextColor();
}

void ThreeWireStrip::setColor(fl_color value)
{
  _odd_strip->setColor(value);
  _even_strip->setColor(value);
}

void ThreeWireStrip::setRGB(byte red, byte green, byte blue)
{
  _odd_strip->setRGB(red, green, blue);
  _even_strip->setRGB(red, green, blue);
}

void ThreeWireStrip::setBrightness(byte value)
{
  _odd_strip->setBrightness(value);
  _even_strip->setBrightness(value);
}

void ThreeWireStrip::display()
{
  _odd_strip->display();
  _even_strip->display();
}

void ThreeWireStrip::display(int approxMs)
{
  unsigned long time = millis();

  while (millis()-time < approxMs) {
    _odd_strip->display();
    _even_strip->display();
  }
}

void ThreeWireStrip::fade(fl_color fromColor, fl_color toColor, int approxMs)
{

}
