
#include "TwoWireStrip.h"

TwoWireStrip::TwoWireStrip(pin vcc_pin)
{
  _vcc_pin = vcc_pin;
  _brightness = 255;
  _color = Black;

  // init our output pings
  pinMode(_vcc_pin, OUTPUT);

  // set power on
  digitalWrite(_vcc_pin, HIGH);

  // this sets us one past White (default 'on'), to Black
  // without this, other offsets are weird
  pulse();
}

void TwoWireStrip::pulse()
{
  delayMicroseconds(M1359L_PACKET_DELAY);
  digitalWrite(_vcc_pin, LOW);
  delayMicroseconds(M1359L_PACKET_DELAY);
  digitalWrite(_vcc_pin, HIGH);
}

void TwoWireStrip::pulse(int count)
{
  for (int i = 0; i < count; i++)
  {
    pulse();
  }
}

// confusingly, this works different than the other pulse functions
// this one will remove voltate on a 1, and return it on a 0
// repeated values will *leave* the voltage were it was at
// there is no artificial delay, which means it should be about 3-4 MHz (I think)
void TwoWireStrip::quickPulse(byte pattern[], int len, int delayMuSec)
{
  for (int i = 0; i < len; i++)
  {
    switch (pattern[i])
    {
    case 0:
      digitalWrite(_vcc_pin, HIGH);
      break;
    case 1:
      digitalWrite(_vcc_pin, LOW);
      break;
      // no default
    }
    delayMicroseconds(delayMuSec);
  }
  // we do restore the high, though
  digitalWrite(_vcc_pin, HIGH);
}

// not sure if we need this one...
void TwoWireStrip::pulse8(byte pattern[])
{

  for (int i = 0; i < 8; i++)
  {
    delayMicroseconds(M1359L_PACKET_DELAY);
    if (pattern[i] == 1)
    {
      digitalWrite(_vcc_pin, LOW);
    }
    digitalWrite(_vcc_pin, HIGH);
  }
  digitalWrite(_vcc_pin, HIGH);
}

void TwoWireStrip::setBlack()
{
  pulse(fl_color::ColorCount - _color);
  _color = Black;
}

// this method skips over black/off
void TwoWireStrip::nextColor()
{
  pulse();
  _color = (_color + 1) % fl_color::ColorCount;
  if (_color == 0)
  {
    nextColor();
  }
}

void TwoWireStrip::setColor(fl_color value)
{
  setBlack();
  _color = value;
  pulse(_color);
}

void TwoWireStrip::setBrightness(uint8_t value)
{
  _brightness = map(value, 0, 255, FL_PWM_MIN, FL_PWM_MAX);
}

// may be borked - originally between 10-20 ms delay
void TwoWireStrip::reset()
{
  delayMicroseconds(M1359L_PACKET_DELAY);
  digitalWrite(_vcc_pin, LOW);
  delay(50);
  digitalWrite(_vcc_pin, HIGH);
  pulse();
  pulse(_color);
}

void TwoWireStrip::display()
{
  // can't use the analogWrite method, it looks like pulses
  // to the ICs in the strip and they freak out
  if (_brightness != FL_PWM_MAX)
  {
    pulse(fl_color::ColorCount - _color);
  }
  delayMicroseconds(FL_PWM_MAX - _brightness);
  
  if (_brightness != FL_PWM_MAX)
  {
    pulse(_color);
  }
  delayMicroseconds(_brightness);
}

void TwoWireStrip::display(int approxMs)
{
  unsigned long time = millis();

  while (millis()-time < approxMs)
  {
    display();
  }
}

void TwoWireStrip::fade(fl_color fromColor, fl_color toColor)
{
  reset();

  int distance = toColor - fromColor;
  if (distance < 0)
  {
    distance = fl_color::ColorCount - distance;
  }

  //this may be backwards...
  for (int i = 0; i <= 255;)
  {
    int fadeVal = map(i, 0, 255, FL_PWM_MIN, FL_PWM_MAX);

    // start at initial color
    pulse(fromColor);
    delayMicroseconds(fadeVal);

    // get to next color, may have to wrap
    pulse(distance);
    delayMicroseconds(FL_PWM_MAX - _brightness);

    // back to black (ie: effective reset)s
    pulse(fl_color::ColorCount - toColor);
  }
}
