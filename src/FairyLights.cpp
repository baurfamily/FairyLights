
#include "FairyLights.h"

FairyLights::FairyLights(FLType lightType, pin vcc_pin) {
  _vcc_pin = vcc_pin;
  _brightness = 255;
  _color = 0;
  
  // init our output pings
  pinMode(_vcc_pin, OUTPUT);
  
  // set power on
  digitalWrite(_vcc_pin, HIGH);

  // this sets us one past white (default 'on'), too "black"
  // without this, other offsets are weird
  pulseOnce();
  _lit = false;
}

void FairyLights::pulseOnce() {
  delayMicroseconds(M1359L_PACKET_DELAY);
  digitalWrite(_vcc_pin, LOW);
  delayMicroseconds(M1359L_PACKET_DELAY);
  digitalWrite(_vcc_pin, HIGH);
}

void FairyLights::pulse(int count) {
  for(int i=0; i<count; i++) {
    pulseOnce();
  }
}

// confusingly, this works different than the other pulse functions
// this one will remove voltate on a 1, and return it on a 0
// repeated values will *leave* the voltage were it was at
// there is no artificial delay, which means it should be about 3-4 MHz (I think)
void FairyLights::quickPulse(byte pattern[], int len, int delayMuSec) {
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


void FairyLights::pulse8(int pattern[]) {
  
  for (int i=0; i<8; i++) {
    delayMicroseconds(M1359L_PACKET_DELAY);
    if (pattern[i] == 1) {
      digitalWrite(_vcc_pin, LOW);
    }
    digitalWrite(_vcc_pin, HIGH);
  }
  digitalWrite(_vcc_pin, HIGH);
}

void FairyLights::setColor(FLColor value) {
  pulse(FL_COLOR_COUNT-_color);
  _color = value;
  if (_lit) {
    // pulses to _color
    pulse(_color);
  }
}

void FairyLights::setBrightness(uint8_t value) {
  _brightness = map( value, 0, 255, M1359L_PWM_MIN, M1359L_PWM_MAX);;
}

// may be borked - originally between 10-20 ms delay
void FairyLights::reset() {
  digitalWrite(_vcc_pin, LOW);
  delay(20);
  digitalWrite(_vcc_pin, HIGH);
  pulseOnce();
  pulse(_color);
  _lit = true;
}

void FairyLights::on() {
  if (_lit) {
    return;
  }
  pulse(_color);
  _lit = true;
}

void FairyLights::off() {
  // this is probably slower than incrementing to 0
  // but more predictable if we start fading between colors
  reset();
  pulseOnce();
  _lit = false;
}

void FairyLights::display() {
  //uses PWM to set brightness (this may be "too fast")
//  analogWrite(_vcc_pin, (255*_brightness)/M1359_PWM_MAX);
  on();
  pulse(FL_COLOR_COUNT - _color);
  delayMicroseconds(M1359L_PWM_MAX - _brightness);
  pulse(_color);
  delayMicroseconds(_brightness);
}

void FairyLights::display(int approxMs) {
  int loops = (1000 * approxMs) / M1359L_PWM_MAX;
  reset();
  for(int i=0; i<loops; i++) {
    display();
  }
}

void FairyLights::fade(FLColor fromColor, FLColor toColor) {
  reset();

  int distance = toColor - fromColor;
  if (distance < 0) {
    distance = FL_COLOR_COUNT - distance;
  }

  //this may be backwards...
  for(int i=0; i<=255; ) {
    int fadeVal = map( i, 0, 255, M1359L_PWM_MIN, M1359L_PWM_MAX);

    // start at initial color
    pulse(fromColor);
    delayMicroseconds(fadeVal);
    
    // get to next color, may have to wrap
    pulse(distance);
    delayMicroseconds(M1359L_PWM_MAX - _brightness);
    
    // back to black (ie: effective reset)s
    pulse(FL_COLOR_COUNT - toColor);
  }
}
