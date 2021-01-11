
#include "FairyLights.h"
#include "TwoWireStrip.h"
#include "FourWireStrip.h"

FairyLights FairyLightsFactory(fl_type lightType, pin pins[]) {
  switch(lightType) {
    case M1359L:
    case TwoWire:
      return TwoWireStrip( pins[0] );
    case FourWire:
      return FourWireStrip( pins[0], pins[1], pins[2], pins[3] );
  }

  //cheating for now...
  return TwoWireStrip( pins[0] );
}
