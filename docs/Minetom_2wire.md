# Minetom 2 wire w/bypass

*Note: these observations are not from any insider knowledge, but from a very inexperienced person writing about what they've figured out or been told my more experienced people.*

## Physical structure

This strip is built with 2 wires passing through each LED "node" (VCC and GND) and a third wire that is twisted in with the other two, but bypasses all the nodes and is tied in at the end of the strip to the ground wire.

Within each bulb / node there is an IC controlling the displayed color and three LEDs (red, green, blue).

## Setting the color

The IC on board in each node is in charge of driving the individual LEDs at the correct values to display the primary and secondary colors. These seem to be all it can display (on/off) and intermediary colors beyond the primary/secondary that can be displayed with the three LEDs.

When you first put power to the string, all LEDs will be powered and it will display as white.  You can cycle through the colors by "pulsing" the VCC line by setting to low and then back to high within about 20 microsecond (this range seems pretty wide, actually... maybe 5-500 or more, too much and it sets back to white).

Each pulse will forward the color one:
* White
* Black (off)
* Red
* Green
* Yellow
* Blue
* Magenta
* Cyan

In the library, when we init the string we pulse once to get it from white to black. From there, we pulse base on which color we want (in code we have the color as an enum with Black being 0 and white 7).

## Fading / Brightness

In order to fade from one color to anohter (or set the brighness by "fading" to black) we use pulse width modulation. Unfortunately, while built in functions of the arduino like `analogWrite` will do PWM, they do it at a frequency that is interpreted by the light nodes as being color set pulses, so it will cycle very quickly through all the colors instead of fading correctly. For this reason, we had to implemnt our own PWM style code.

## Multiple Colors / Individual Control

This strip does not have a "controllable" way to set different LEDs to different colors, however we have found that we can touch the bypass wire quickly to the VCC wire and it will set the lights somewhat randomly. After this, you can fade or go to the "next" color and they will stay consistently out of sync. We're still looking for a way to do this programatically, but havent found a way yet.

