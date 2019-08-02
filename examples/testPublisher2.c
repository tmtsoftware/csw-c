//
// Created by abrighto on 8/1/19.
//

#include "csw/Event.h"
#include "csw/EventPublisher.h"
#include "csw/Parameter.h"

int main() {
    CswEventPublisherContext publisher = cswEventPublisherInit();

    // -- IntKey parameter contains one or more int values --
    int values1[] = {42};
    CswArrayValue arrayValues1 = {.values = values1, .numValues = 1};
    CswParameter intParam = cswMakeParameter("IntValue", IntKey, arrayValues1, "arcsec");

    // -- IntArrayKey parameter contains one or more int array values --
    int values2[2][4] = {
            {1,2,3,4},
            {5,6,7,8}
    };
    CswArrayValue a1 = {.values = values2[0], .numValues = 4};
    CswArrayValue a2 = {.values = values2[1], .numValues = 4};
    CswArrayValue aa[] = {a1, a2};
    CswArrayValue arrayValues2 = {.values = aa, .numValues = 2};
    CswParameter intArrayParam = cswMakeParameter("IntArrayValue", IntArrayKey, arrayValues2, "arcsec");

    // -- IntMatrixKey parameter contains one or more int matrix values (Sorry, this gets ugly in C...) --

    int values3[2][4] = {
            {11,-22,33,-44},
            {-55,66,-77,88}
    };
    CswArrayValue b1 = {.values = values3[0], .numValues = 4};
    CswArrayValue b2 = {.values = values3[1], .numValues = 4};
    CswArrayValue ba[] = {b1, b2};
    CswArrayValue arrayValues3 = {.values = ba, .numValues = 2};
    CswArrayValue ma[] = {arrayValues2, arrayValues3};

    CswArrayValue matrixValues = {.values = ma, .numValues = 2};
    CswParameter intMatrixParam = cswMakeParameter("IntMatrixValue", IntMatrixKey, matrixValues, "arcsec");

    // -- ParamSet
    CswParameter params[] = {intParam, intArrayParam, intMatrixParam};
    CswParamSet paramSet = {.params = params, .numParams = 3};

    // -- Event --
    CswEvent event = cswMakeEvent(SystemEvent, "test.assembly", "myAssemblyEvent", paramSet);

    // -- Publish --
    cswEventPublisherPublish(publisher, event);

    // -- Cleanup --
    cswFreeEvent(event);
}
