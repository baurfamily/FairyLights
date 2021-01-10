
#include "TwoWireStrip.h"

TwoWireStrip::TwoWireStrip(pin vcc_pin) {
  _vcc_pin = vcc_pin;
  _brightness = 255;
  _color = 0;
  
  // init our output pings
  pinMode(_vcc_pin, OUTPUT);
  
  // set power on
  digitalWrite(_vcc_pin, HIGH);

  // this sets us one past white (default 'on'), too "black"
  // without this, other offsets are weird
  pulse();
}

void TwoWireStrip::pulse() {
  delayMicroseconds(TWO_WIRE_PACKET_DELAY);
  digitalWrite(_vcc_pin, LOW);
  delayMicroseconds(TWO_WIRE_PACKET_DELAY);
  digitalWrite(_vcc_pin, HIGH);
}

void TwoWireStrip::pulse(int count) {
  for(int i=0; i<count; i++) {
    pulse();
  }
}

// confusingly, this works different than the other pulse functions
// this one will remove voltate on a 1, and return it on a 0
// repeated values will *leave* the voltage were it was at
// there is no artificial delay, which means it should be about 3-4 MHz (I think)
void TwoWireStrip::quickPulse(byte pattern[], int len, int delayMuSec) {
  for (int i=0; i<len; i++) {
    switch (pattern[i]) {
      case 0: digitalWrite(_vcc_pin, HIGH); break;
      case 1: digitalWrite(_vcc_pin, LOW); break;
      // no default
    }
    delayMicroseconds(delayMuSec);
  }
  // we do restore the high, though
  digitalWrite(_vcc_pin, HIGH);
}

// not sure if we need this one...
void TwoWireStrip::pulse8(byte pattern[]) {
  
  for (int i=0; i<8; i++) {
    delayMicroseconds(TWO_WIRE_PACKET_DELAY);
    if (pattern[i] == 1) {
      digitalWrite(_vcc_pin, LOW);
    }
    digitalWrite(_vcc_pin, HIGH);
  }
  digitalWrite(_vcc_pin, HIGH);
}

void TwoWireStrip::setBlack() {
  pulse(TWO_WIRE_COLOR_COUNT-_color);
  _color = Black;
}

// this method skips over black/off
void TwoWireStrip::nextColor() {
  pulse();
  _color = (_color+1) % 8;
  if (_color == 0) {
    nextColor();
  }
}

void TwoWireStrip::setColor(fl_color value) {
  setBlack();
  pulse(_color);
  _color = value;
}

void TwoWireStrip::setBrightness(uint8_t value) {
  _brightness = map( value, 0, 255, TWO_WIRE_PWM_MIN, TWO_WIRE_PWM_MAX);
}

// may be borked - originally between 10-20 ms delay
void TwoWireStrip::reset() {
  digitalWrite(_vcc_pin, LOW);
  delay(50);
  digitalWrite(_vcc_pin, HIGH);
  pulse();
  pulse(_color);
}

void TwoWireStrip::display() {
  //uses PWM to set brightness (this may be "too fast")
//  analogWrite(_vcc_pin, (255*_brightness)/M1359_PWM_MAX);
  pulse(TWO_WIRE_COLOR_COUNT - _color);
  delayMicroseconds(TWO_WIRE_PWM_MAX - _brightness);
  pulse(_color);
  delayMicroseconds(_brightness);
}

void TwoWireStrip::display(int approxMs) {
  int loops = (1000 * approxMs) / TWO_WIRE_PWM_MAX;
  reset();
  for(int i=0; i<loops; i++) {
    display();
  }
}

void TwoWireStrip::fade(fl_color fromColor, fl_color toColor) {
  reset();

  int distance = toColor - fromColor;
  if (distance < 0) {
    distance = TWO_WIRE_COLOR_COUNT - distance;
  }

  //this may be backwards...
  for(int i=0; i<=255; ) {
    int fadeVal = map( i, 0, 255, TWO_WIRE_PWM_MIN, TWO_WIRE_PWM_MAX);

    // start at initial color
    pulse(fromColor);
    delayMicroseconds(fadeVal);
    
    // get to next color, may have to wrap
    pulse(distance);
    delayMicroseconds(TWO_WIRE_PWM_MAX - _brightness);
    
    // back to black (ie: effective reset)s
    pulse(TWO_WIRE_COLOR_COUNT - toColor);
  }
}
