//
// Created by abrighto on 8/1/19.
//

#include "csw/csw.h"

static void publishCoords(CswEventServiceContext publisher) {

    CswEqCoord eqCoord = cswMakeEqCoord("BASE", 659912250000, -109892300000, FK5, "none", 0.5f, 2.33f);
    CswCoord values[1];
    values[0].eqCoord = eqCoord;
    CswArrayValue arrayValues = {.values = values, .numValues = 1};
    CswParameter coordParam = cswMakeParameter("CoordParam", CoordKey, arrayValues, "NoUnits");

    // -- ParamSet
    CswParameter params[] = {coordParam};
    CswParamSet paramSet = {.params = params, .numParams = 1};

    // -- Event --
    CswEvent event = cswMakeEvent(SystemEvent, "csw.assembly", "myAssemblyEvent", paramSet);

    // -- Publish --
    cswEventPublish(publisher, event);

    // -- Cleanup --
    cswFreeEvent(event);
}


int main() {
    CswEventServiceContext publisher = cswEventPublisherInit();

    publishCoords(publisher);
}
