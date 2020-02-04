//
// Created by abrighto on 8/1/19.
//

#include "csw/csw.h"

// Tests publishing coordinate values

static void publishAltAzCoord(CswEventServiceContext publisher) {
    CswAltAzCoord altAzCoord1 = cswMakeAltAzCoord("BASE", 1083600000000, 153000000000);
    CswCoord values[1];
    values[0].altAzCoord = altAzCoord1;
    CswArrayValue arrayValues = {.values = values, .numValues = 1};
    CswParameter coordParam = cswMakeParameter("CoordParam", CoordKey, arrayValues, "NoUnits");

    // -- ParamSet
    CswParameter params[] = {coordParam};
    CswParamSet paramSet = {.params = params, .numParams = 1};

    // -- Event --
    CswEvent event = cswMakeEvent(SystemEvent, "CSW.testassembly", "myAssemblyEvent", paramSet);

    // -- Publish --
    cswEventPublish(publisher, event);

    // -- Cleanup --
    cswFreeEvent(event);
}

static void publishCometCoord(CswEventServiceContext publisher) {
    CswCometCoord cometCoord1 = cswMakeCometCoord("BASE", 2000.0, 324000000000, 7200000000, 360000000000, 1.4, 0.234);
    CswCoord values[1];
    values[0].cometCoord = cometCoord1;
    CswArrayValue arrayValues = {.values = values, .numValues = 1};
    CswParameter coordParam = cswMakeParameter("CoordParam", CoordKey, arrayValues, "NoUnits");

    // -- ParamSet
    CswParameter params[] = {coordParam};
    CswParamSet paramSet = {.params = params, .numParams = 1};

    // -- Event --
    CswEvent event = cswMakeEvent(SystemEvent, "CSW.testassembly", "myAssemblyEvent", paramSet);

    // -- Publish --
    cswEventPublish(publisher, event);

    // -- Cleanup --
    cswFreeEvent(event);
}

static void publishMinorPlanetCoord(CswEventServiceContext publisher) {
    CswMinorPlanetCoord minorPlanetCoord1 = cswMakeMinorPlanetCoord("GUIDER1", 2000, 324000000000, 7200000000,
                                                                    360000000000, 1.4, 0.234, 792000000000);
    CswCoord values[1];
    values[0].minorPlanetCoord = minorPlanetCoord1;
    CswArrayValue arrayValues = {.values = values, .numValues = 1};
    CswParameter coordParam = cswMakeParameter("CoordParam", CoordKey, arrayValues, "NoUnits");

    // -- ParamSet
    CswParameter params[] = {coordParam};
    CswParamSet paramSet = {.params = params, .numParams = 1};

    // -- Event --
    CswEvent event = cswMakeEvent(SystemEvent, "CSW.testassembly", "myAssemblyEvent", paramSet);

    // -- Publish --
    cswEventPublish(publisher, event);

    // -- Cleanup --
    cswFreeEvent(event);
}

static void publishSolarSystemCoords(CswEventServiceContext publisher) {
    CswSolarSystemCoord solarSystemCoord1 = cswMakeSolarSystemCoord("BASE", Venus);
    CswSolarSystemCoord solarSystemCoord2 = cswMakeSolarSystemCoord("TARGET", Venus);
    CswCoord values[2];
    values[0].solarSystemCoord = solarSystemCoord1;
    values[1].solarSystemCoord = solarSystemCoord2;
    CswArrayValue arrayValues = {.values = values, .numValues = 2};
    CswParameter coordParam = cswMakeParameter("CoordParam", CoordKey, arrayValues, "NoUnits");

    // -- ParamSet
    CswParameter params[] = {coordParam};
    CswParamSet paramSet = {.params = params, .numParams = 1};

    // -- Event --
    CswEvent event = cswMakeEvent(SystemEvent, "CSW.testassembly", "myAssemblyEvent", paramSet);

    // -- Publish --
    cswEventPublish(publisher, event);

    // -- Cleanup --
    cswFreeEvent(event);
}

static void publishEqCoords(CswEventServiceContext publisher) {
    CswEqCoord eqCoord1 = cswMakeEqCoord("BASE", 659912250000, -109892300000, FK5, "none", 0.5f, 2.33f);
    CswEqCoord eqCoord2 = cswMakeEqCoord("TARGET", 649912250000, -129892300000, FK5, "none", 0.4f, 2.1f);
    CswCoord values[2];
    values[0].eqCoord = eqCoord1;
    values[1].eqCoord = eqCoord2;
    CswArrayValue arrayValues = {.values = values, .numValues = 2};
    CswParameter coordParam = cswMakeParameter("CoordParam", CoordKey, arrayValues, "NoUnits");

    // -- ParamSet
    CswParameter params[] = {coordParam};
    CswParamSet paramSet = {.params = params, .numParams = 1};

    // -- Event --
    CswEvent event = cswMakeEvent(SystemEvent, "CSW.testassembly", "myAssemblyEvent", paramSet);

    // -- Publish --
    cswEventPublish(publisher, event);

    // -- Cleanup --
    cswFreeEvent(event);
}


int main() {
    CswEventServiceContext publisher = cswEventPublisherInit();
    publishEqCoords(publisher);
    publishSolarSystemCoords(publisher);
    publishMinorPlanetCoord(publisher);
    publishCometCoord(publisher);
    publishAltAzCoord(publisher);
}
