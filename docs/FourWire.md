# Four Wire Fairy Lights

(disclaimer: this is all about the ones we've poked at, if you have a strip that works different let us know!)

## Configuration (theory)

### The wires
The four wire strips work by having a red, green and blue all on the same strip, but with some sharing of pins.

Specifically, the red LED has one pin of it's own, and one shared with the green LED. Green shares the one with red, and the other with blue. the blue LED has one of it's own in addition to the one shared with green.

This means that you can easily light anyone of red/green/blue by driving one pin high and one to groud while leaving the other two pins "off" (high-impedence). For blue and red that's straight-forward, but it feels weird for green since you have to drive one of the blue pins high and one of the red pins low - and the others off.

This is my approximation of what's going on:

<iframe width="450" height="280" src="https://www.tinkercad.com/embed/hmdHKDVvpSH?editbtn=1" frameborder="0" marginwidth="0" marginheight="0" scrolling="no"></iframe>

### Other colors
Secondary (and other) colors can be accomplished by pulse width modulation (PWM) - lighting up the LEDs quickly and changing out which is lit. Some colors can be produced statically, but the join pins makes it hard to control as there are only a few combinations that are practical.

### Two color strips

The strips we've looked at can all display two colors at once. They do this by every "bulb" being configured backwards compared to the one in front of it. This means that a high/low signal for red (for example) will turn on every even bulb to red and then driving low/high on the same pins will turn on all the odd ones.

Some experimentation will be required to configure your strip correctly with this library.

## Configuration (in practice)

For the purposes of this discussion, we're going to ignore the difference between "even" and "odd" - just remember which pins were involved and you can aways switch which one is ground or VCC to get the other half of the strip to light up.

### Steps

1. Mark the wire that bypasses the LEDs
1. Mark the wire that is in the center of the LEDs
1. Mark one of the remaining wires "blue"
1. Mark the final wire "red"

Note: If you run into issues, coming back to this step and testing this out with an actual power source and probing the wires to see what lights up is a good idea. We expect power applied to the center wire and ground to the ones marked "red" and "blue" should light up the LEDs.... um, well... red and blue. (If you reverse ground and power you should get blue and red instead.)

### In Code

When initializing, you can use the factory method or instantiate the class directly. If you plan to use only the basic methods (and don't care about the "two color" capabilities of the strip) then the factory method is sufficient.

To use the even/odd functions, you'll need to create an instance directly or cast the result of the factory method to the right class.

#### Factory method

```
#include <FairyLights.h>
pin pins[4] = { BYPASS_PIN, CENTER_PIN, RED_PIN, BLUE_PIN };
FairyLights strip = FairyLightsFactory(FourWire, pins);
```

#### Direct method

```
#include <FairyLights.h>

FourWireStrip strip = FairyLightsFactory(BYPASS_PIN, CENTER_PIN, RED_PIN, BLUE_PIN);
```

###