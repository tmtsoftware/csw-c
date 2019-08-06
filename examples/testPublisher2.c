//
// Created by abrighto on 8/1/19.
//

#include "csw/csw.h"


static void publishInts(CswEventServiceContext publisher) {
    // -- IntKey parameter contains one or more int values --
    int intValues[] = {42, 43};
    CswArrayValue arrayValues1 = {.values = intValues, .numValues = 2};
    CswParameter intParam = cswMakeParameter("IntValue", IntKey, arrayValues1, "arcsec");

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
            "arcsec");


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

    CswParameter intMatrixParam = cswMakeParameter("IntMatrixValue", IntMatrixKey, matrixValues, "arcsec");

    // -- ParamSet
    CswParameter params[] = {intParam, intArrayParam, intMatrixParam};
    CswParamSet paramSet = {.params = params, .numParams = 3};

    // -- Event --
    CswEvent event = cswMakeEvent(SystemEvent, "csw.assembly", "myAssemblyEvent", paramSet);

    // -- Publish --
    cswEventPublish(publisher, event);

    // -- Cleanup --
    cswFreeEvent(event);
}

static void publishDoubles(CswEventServiceContext publisher) {
    // -- DoubleKey parameter contains one or more double values --
    double doubleValues[] = {42.1, 43.5};
    CswArrayValue arrayValues1 = {.values = doubleValues, .numValues = 2};
    CswParameter doubleParam = cswMakeParameter("DoubleValue", DoubleKey, arrayValues1, "arcsec");

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
            "arcsec");


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

    CswParameter doubleMatrixParam = cswMakeParameter("DoubleMatrixValue", DoubleMatrixKey, matrixValues, "arcsec");

    // -- ParamSet
    CswParameter params[] = {doubleParam, doubleArrayParam, doubleMatrixParam};
    CswParamSet paramSet = {.params = params, .numParams = 3};

    // -- Event --
    CswEvent event = cswMakeEvent(SystemEvent, "csw.assembly", "myAssemblyEvent", paramSet);

    // -- Publish --
    cswEventPublish(publisher, event);

    // -- Cleanup --
    cswFreeEvent(event);
}

int main() {
    CswEventServiceContext publisher = cswEventPublisherInit();

    publishInts(publisher);
    publishDoubles(publisher);
    // TODO: publish other types...
}
