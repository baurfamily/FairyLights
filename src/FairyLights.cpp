
#include "FairyLights.h"
#include "TwoWireStrip.h"

FairyLights FairyLightsFactory(fl_type lightType, pin pins[]) {
  switch(lightType) {
    case M1359L:
    case TwoWire:
      return TwoWireStrip( pins[0] );
  }

  //cheating for now...
  return TwoWireStrip( pins[0] );
}
