//
// Created by abrighto on 2/12/20.
//

#include <stdio.h>
#include <libgen.h>
#include <zconf.h>
#include <stdlib.h>

#include "csw/csw.h"

/*
 * Note: This test assumes the following applications are running:
 *
 * CSW Services:
 *   csw-services start
 *
 * Test Assembly:
 *  cd testSupport
 *  sbt stage
 *  test-deploy/target/universal/stage/bin/test-container-cmd-app --local test-deploy/src/main/resources/TestContainer.conf
 *
 * Note: The test assembly subscribes to exactly the named events published by this test,
 * so if you change any event names, update the assembly code in TestAssemblyHandlers.
 */

static char *prefix = "CSW.TestPublisher";

// Tests publishing a simple event with multiple values
static void publishSimpleEvent(CswEventServiceContext publisher) {
    double ar1[] = {1.1, 2.2, 3.3};
    CswArrayValue values1 = {.values = ar1, .numValues = 3};
    CswParameter param1 = cswMakeParameter("DoubleValue", DoubleKey, values1, csw_unit_arcmin);

    const char* ar2[] = {"one", "two"};
    CswArrayValue values2 = {.values = ar2, .numValues = 2};
    CswParameter param2 = cswMakeParameter("StringValue", StringKey, values2, csw_unit_NoUnits);

    const char* ar3[] = {"choice1"};
    CswArrayValue values3 = {.values = ar3, .numValues = 1};
    CswParameter param3 = cswMakeParameter("ChoiceValue", ChoiceKey, values3, csw_unit_NoUnits);

    CswParameter params[] = {param1, param2, param3};
    CswParamSet paramSet = {.params = params, .numParams = 3};
    CswEvent event = cswMakeEvent(SystemEvent, prefix, "SimpleEvent", paramSet);
    cswEventPublish(publisher, event);
    cswFreeEvent(event);
}

// Tests publishing a simple event containing a UTCTime parameter
static void publishUtcTimeEvent(CswEventServiceContext publisher) {
//    CswUtcTime ar[] = {cswUtcTime()};
    // Use fixed date so that test comparison works
    CswUtcTime ar[] = {cswMakeUtcTime(1625066893, 372333847)};
    CswArrayValue values = {.values = ar, .numValues = 1};
    CswParameter param = cswMakeParameter("utcTimeValue", UTCTimeKey, values, csw_unit_NoUnits);
    CswParameter params[] = {param};
    CswParamSet paramSet = {.params = params, .numParams = 1};
    CswEvent event = cswMakeEvent(SystemEvent, prefix, "UtcTimeEvent", paramSet);
    cswEventPublish(publisher, event);
    cswFreeEvent(event);
}

// Tests publishing a simple event containing a UTCTime parameter
static void publishTaiTimeEvent(CswEventServiceContext publisher) {
//    CswTaiTime ar[] = {cswTaiTime()};
    // Use fixed date so that test comparison works
    CswTaiTime ar[] = {cswMakeTaiTime(1625066980, 763689367)};
    CswArrayValue values = {.values = ar, .numValues = 1};
    CswParameter param = cswMakeParameter("taiTimeValue", TAITimeKey, values, csw_unit_NoUnits);
    CswParameter params[] = {param};
    CswParamSet paramSet = {.params = params, .numParams = 1};
    CswEvent event = cswMakeEvent(SystemEvent, prefix, "TaiTimeEvent", paramSet);
    cswEventPublish(publisher, event);
    cswFreeEvent(event);
}

// Tests publishing array and matrix values

static void publishInts(CswEventServiceContext publisher) {
    // -- IntKey parameter contains one or more int values --
    int intValues[] = {42, 43};
    CswArrayValue arrayValues1 = {.values = intValues, .numValues = 2};
    CswParameter intParam = cswMakeParameter("IntValue", IntKey, arrayValues1, csw_unit_arcsec);

    // -- IntArrayKey parameter contains one or more int array values --
    int intArrayValues[2][4] = {
            {1, 2, 3, 4},
            {5, 6, 7, 8}
    };
    CswArrayValue intArrayHolder[2];
    CswParameter intArrayParam = cswMakeParameter(
            "IntArrayValue",
            IntArrayKey,
            makeArrayValues((void **) intArrayValues, 2, intArrayHolder, 4),
            csw_unit_arcsec);


    // -- IntMatrixKey parameter contains one or more int matrix values (Sorry, this gets ugly in C...) --
    int intMatrixValues[2][2][4] = {
            {
                    {1,  2,   3,  4},
                    {5,   6,  7,   8}
            },
            {
                    {11, -22, 33, -44},
                    {-55, 66, -77, 88}
            }
    };

//    CswArrayValue matrixValues = makeMatrixValues((void***)intMatrixValues, 2, 2, 4);

    CswArrayValue arrayHolder[2][2];
    CswArrayValue ar[] = {
            makeArrayValues((void **) intMatrixValues[0], 2, arrayHolder[0], 4),
            makeArrayValues((void **) intMatrixValues[1], 2, arrayHolder[1], 4),
    };
    CswArrayValue matrixValues = {.arrayValues = ar, .numValues = 2};

    CswParameter intMatrixParam = cswMakeParameter("IntMatrixValue", IntMatrixKey, matrixValues, csw_unit_arcsec);

    // -- ParamSet
    CswParameter params[] = {intParam, intArrayParam, intMatrixParam};
    CswParamSet paramSet = {.params = params, .numParams = 3};

    // -- Event --
    CswEvent event = cswMakeEvent(SystemEvent, prefix, "IntArrayMatrixEvent", paramSet);

    // -- Publish --
    cswEventPublish(publisher, event);

    // -- Cleanup --
    cswFreeEvent(event);
}

static void publishDoubles(CswEventServiceContext publisher) {
    // -- DoubleKey parameter contains one or more double values --
    double doubleValues[] = {42.1, 43.5};
    CswArrayValue arrayValues1 = {.values = doubleValues, .numValues = 2};
    CswParameter doubleParam = cswMakeParameter("DoubleValue", DoubleKey, arrayValues1, csw_unit_arcsec);

    // -- DoubleArrayKey parameter contains one or more double array values --
    double doubleArrayValues[2][4] = {
            {1.1, 2.2, 3.3, 4.4},
            {5.5, 6.6, 7.7, 8.8}
    };
    CswArrayValue doubleArrayHolder[2];
    CswParameter doubleArrayParam = cswMakeParameter(
            "DoubleArrayValue",
            DoubleArrayKey,
            makeArrayValues((void **) doubleArrayValues, 2, doubleArrayHolder, 4),
            csw_unit_arcsec);


    // -- DoubleMatrixKey parameter contains one or more double matrix values (Sorry, this gets ugly in C...) --
    double doubleMatrixValues[2][2][4] = {
            {
                    {1.3,  2.4,   3.5,  4.6},
                    {5.7,   6.8,  7.9,   8.0}
            },
            {
                    {11.1, -22.2, 33.3, -44.4},
                    {-55.5, 66.6, -77.7, 88.8}
            }
    };

//    CswArrayValue matrixValues = makeMatrixValues((void***)doubleMatrixValues, 2, 2, 4);

    CswArrayValue arrayHolder[2][2];
    CswArrayValue ar[] = {
            makeArrayValues((void **) doubleMatrixValues[0], 2, arrayHolder[0], 4),
            makeArrayValues((void **) doubleMatrixValues[1], 2, arrayHolder[1], 4),
    };
    CswArrayValue matrixValues = {.arrayValues = ar, .numValues = 2};

    CswParameter doubleMatrixParam = cswMakeParameter("DoubleMatrixValue", DoubleMatrixKey, matrixValues, csw_unit_arcsec);

    // -- ParamSet
    CswParameter params[] = {doubleParam, doubleArrayParam, doubleMatrixParam};
    CswParamSet paramSet = {.params = params, .numParams = 3};

    // -- Event --
    CswEvent event = cswMakeEvent(SystemEvent, prefix, "DoubleArrayMatrtixEvent", paramSet);

    // -- Publish --
    cswEventPublish(publisher, event);

    // -- Cleanup --
    cswFreeEvent(event);
}


// -- Tests publishing coordinate values --
static void publishAltAzCoord(CswEventServiceContext publisher) {
    CswAltAzCoord altAzCoord1 = cswMakeAltAzCoord("BASE", 1083600000000, 153000000000);
    CswCoord values[1];
    values[0].altAzCoord = altAzCoord1;
    CswArrayValue arrayValues = {.values = values, .numValues = 1};
    CswParameter coordParam = cswMakeParameter("CoordParam", CoordKey, arrayValues, csw_unit_NoUnits);

    // -- ParamSet
    CswParameter params[] = {coordParam};
    CswParamSet paramSet = {.params = params, .numParams = 1};

    // -- Event --
    CswEvent event = cswMakeEvent(SystemEvent, prefix, "AltAzCoordEvent", paramSet);

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
    CswParameter coordParam = cswMakeParameter("CoordParam", CoordKey, arrayValues, csw_unit_NoUnits);

    // -- ParamSet
    CswParameter params[] = {coordParam};
    CswParamSet paramSet = {.params = params, .numParams = 1};

    // -- Event --
    CswEvent event = cswMakeEvent(SystemEvent, prefix, "CometCoordEvent", paramSet);

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
    CswParameter coordParam = cswMakeParameter("CoordParam", CoordKey, arrayValues, csw_unit_NoUnits);

    // -- ParamSet
    CswParameter params[] = {coordParam};
    CswParamSet paramSet = {.params = params, .numParams = 1};

    // -- Event --
    CswEvent event = cswMakeEvent(SystemEvent, prefix, "MinorPlanetCoordEvent", paramSet);

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
    CswParameter coordParam = cswMakeParameter("CoordParam", CoordKey, arrayValues, csw_unit_NoUnits);

    // -- ParamSet
    CswParameter params[] = {coordParam};
    CswParamSet paramSet = {.params = params, .numParams = 1};

    // -- Event --
    CswEvent event = cswMakeEvent(SystemEvent, prefix, "SolarSystemCoordsEvent", paramSet);

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
    CswParameter coordParam = cswMakeParameter("CoordParam", CoordKey, arrayValues, csw_unit_NoUnits);

    // -- ParamSet
    CswParameter params[] = {coordParam};
    CswParamSet paramSet = {.params = params, .numParams = 1};

    // -- Event --
    CswEvent event = cswMakeEvent(SystemEvent, prefix, "EqCoordsEvent", paramSet);

    // -- Publish --
    cswEventPublish(publisher, event);

    // -- Cleanup --
    cswFreeEvent(event);
}

static void publishStruct(CswEventServiceContext publisher) {
    // Double parameter
    double ar1[] = {1.1, 2.2, 3.3};
    CswArrayValue values1 = {.values = ar1, .numValues = 3};
    CswParameter param1 = cswMakeParameter("doubleEventValues", DoubleKey, values1, csw_unit_arcmin);

    // Int parameter
    int ar2[] = {1, 2, 3};
    CswArrayValue values2 = {.values = ar2, .numValues = 3};
    CswParameter param2 = cswMakeParameter("intEventValues", IntKey, values2, csw_unit_arcmin);

    // Struct parameter containing two fields (the two above parameters)
    CswParameter params1[] = {param1, param2};
    CswParamSet paramSet1 = {.params = params1, .numParams = 2};
    CswParamSet ar[] = {paramSet1};
    CswArrayValue values = {.values = ar, .numValues = 1};
    CswParameter param = cswMakeParameter("structEventValues", StructKey, values, csw_unit_NoUnits);

    // Param set for the event
    CswParameter params[] = {param};
    CswParamSet paramSet = {.params = params, .numParams = 1};

    CswEvent event = cswMakeEvent(SystemEvent, prefix, "StructEvent", paramSet);

    cswEventPublish(publisher, event);

    cswFreeEvent(event);
}


#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedParameter"
int main(int argc, char **argv) {
    CswEventServiceContext publisher = cswEventPublisherInit();

    publishSimpleEvent(publisher);

    publishUtcTimeEvent(publisher);
    publishTaiTimeEvent(publisher);

    publishInts(publisher);
    publishDoubles(publisher);

    publishEqCoords(publisher);
    publishSolarSystemCoords(publisher);
    publishMinorPlanetCoord(publisher);
    publishCometCoord(publisher);
    publishAltAzCoord(publisher);

    publishStruct(publisher);

    // Give the assembly time to receive the events and write the file
    sleep(3);

    char *dir = dirname(argv[0]);
    char cmd[PATH_MAX];
    sprintf(cmd, "cmp %s/TestAssemblyHandlers.out /tmp/TestAssemblyHandlers.out", dir);
    printf("%s\n", cmd);
    int status = system(cmd);
    if (status == 0)
        printf("All tests passed.\n");
    else
        printf("Test Failed\n");

    return status;
}
#pragma clang diagnostic pop

