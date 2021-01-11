#include "FourWireStrip.h"

FourWireStrip::FourWireStrip(pin bypass, pin center, pin red, pin blue) {
  _bypass_pin = bypass;
  _center_pin = center;
  _red_pin = red;
  _blue_pin = blue;

  _brightness = 255;  

  // set all to white
  _color_odd = White;
  _red_odd = 255;
  _green_odd = 255;
  _blue_odd = 255;

  _color_even = White;
  _red_even = 255;
  _green_even = 255;
  _blue_even = 255;

  // why even configure it?
  digitalWrite(_bypass_pin, LOW);
  pinMode(_bypass_pin, INPUT);
}

// overrides
void FourWireStrip::setBlack() {
  _red_odd = 0;
  _green_odd = 0;
  _blue_odd = 0;
  _red_even = 0;
  _green_even = 0;
  _blue_even = 0;
}

void FourWireStrip::nextColor() {
  nextColorOdd();
  nextColorEven();
}

void FourWireStrip::nextColorOdd() {
  fl_color odd_color = (fl_color)((_color_odd+1) % fl_color::ColorCount);
  if (odd_color == Black) odd_color = Red;
  setColorOdd(odd_color);
}

void FourWireStrip::nextColorEven() {
  fl_color even_color = (fl_color)((_color_even+1) % fl_color::ColorCount);
  if (even_color == Black) even_color = Red;
  setColorEven(even_color);
}

void FourWireStrip::setColor(fl_color value) {
  setColorOdd(value);
  setColorEven(value);
}

void FourWireStrip::setColorOdd(fl_color value) {
  if (value != ColorCount) {
    _color_odd = value;
  }
  switch (value) {
    case Black:   setRGBOdd(  0,   0,   0); break;
    case Red:     setRGBOdd(255,   0,   0); break;
    case Green:   setRGBOdd(  0, 255,   0); break;
    case Yellow:  setRGBOdd(255, 255,   0); break;
    case Blue:    setRGBOdd(  0,   0, 255); break;
    case Magenta: setRGBOdd(255,   0, 255); break;
    case Cyan:    setRGBOdd(  0, 255, 255); break;
    case White:   setRGBOdd(255, 255, 255); break;
  }
}

void FourWireStrip::setColorEven(fl_color value) {
  if (value != ColorCount) {
    _color_even = value;
  }
  switch (value) {
    case Black:   setRGBEven(  0,   0,   0); break;
    case Red:     setRGBEven(255,   0,   0); break;
    case Green:   setRGBEven(  0, 255,   0); break;
    case Yellow:  setRGBEven(255, 255,   0); break;
    case Blue:    setRGBEven(  0,   0, 255); break;
    case Magenta: setRGBEven(255,   0, 255); break;
    case Cyan:    setRGBEven(  0, 255, 255); break;
    case White:   setRGBEven(255, 255, 255); break;
  }
}

void FourWireStrip::setRGB(byte red, byte green, byte blue) {
  setRGBOdd(red, green, blue);
  setRGBEven(red, green, blue);
}

void FourWireStrip::setRGBOdd(byte red, byte green, byte blue) {
  _red_odd = red; _green_odd = green; _blue_odd = blue;
}

void FourWireStrip::setRGBEven(byte red, byte green, byte blue) {
  _red_even = red; _green_even = green; _blue_even = blue;
}

void FourWireStrip::setBrightness(byte value) {
  _brightness = value;
}

void FourWireStrip::display() {
  displayRedOdd();
  delayMicroseconds(_red_odd);
  displayRedEven();
  delayMicroseconds(_red_even);
  
  displayGreenOdd();
  delayMicroseconds(_green_odd);
  displayGreenEven();
  delayMicroseconds(_green_even);
  
  displayBlueOdd();
  delayMicroseconds(_blue_odd);
  displayBlueEven();
  delayMicroseconds(_blue_even);
}

void FourWireStrip::displayRedOdd() {
  pinMode(_center_pin, OUTPUT);
  digitalWrite(_center_pin, HIGH);
  
  pinMode(_red_pin, OUTPUT);
  digitalWrite(_red_pin, LOW);
  
  digitalWrite(_blue_pin, LOW);
  pinMode(_blue_pin, INPUT);
}

void FourWireStrip::displayRedEven() {
  pinMode(_center_pin, OUTPUT);
  digitalWrite(_center_pin, LOW);
  
  pinMode(_red_pin, OUTPUT);
  digitalWrite(_red_pin, HIGH);
  
  digitalWrite(_blue_pin, LOW);
  pinMode(_blue_pin, INPUT);
}

void FourWireStrip::displayGreenOdd() {
  digitalWrite(_center_pin, LOW);
  pinMode(_center_pin, INPUT);
  
  pinMode(_red_pin, OUTPUT);
  digitalWrite(_red_pin, LOW);
  
  pinMode(_blue_pin, OUTPUT);
  digitalWrite(_blue_pin, HIGH);
}

void FourWireStrip::displayGreenEven() {
  digitalWrite(_center_pin, LOW);
  pinMode(_center_pin, INPUT);
  
  pinMode(_red_pin, OUTPUT);
  digitalWrite(_red_pin, HIGH);
  
  pinMode(_blue_pin, OUTPUT);
  digitalWrite(_blue_pin, LOW);
}

void FourWireStrip::displayBlueOdd() {
  pinMode(_center_pin, OUTPUT);
  digitalWrite(_center_pin, LOW);
  
  digitalWrite(_red_pin, LOW);
  pinMode(_red_pin, INPUT);
  
  pinMode(_blue_pin, OUTPUT);
  digitalWrite(_blue_pin, HIGH);  
}

void FourWireStrip::displayBlueEven() {
  pinMode(_center_pin, OUTPUT);
  digitalWrite(_center_pin, HIGH);
  
  digitalWrite(_red_pin, LOW);
  pinMode(_red_pin, INPUT);
  
  pinMode(_blue_pin, OUTPUT);
  digitalWrite(_blue_pin, LOW);
}

void FourWireStrip::display(int approxMs) {
  unsigned long time = micros();

  while (micros()-time < 1000*1000*approxMs) {
    display();
  }
}

void FourWireStrip::fade(fl_color fromColor, fl_color toColor) {

}
