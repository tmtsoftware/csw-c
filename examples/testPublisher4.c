//
// Created by abrighto on 8/15/19.
//

#include "csw/csw.h"

// Test publishing a CSW Struct to the event service
int main() {
    CswEventServiceContext publisher = cswEventPublisherInit();

    double ar1[] = {1.1, 2.2, 3.3};
    CswArrayValue values1 = {.values = ar1, .numValues = 3};
    CswParameter param1 = cswMakeParameter("doubleEventValues", DoubleKey, values1, "arcmin");

    int ar2[] = {1, 2, 3};
    CswArrayValue values2 = {.values = ar2, .numValues = 3};
    CswParameter param2 = cswMakeParameter("intEventValues", IntKey, values2, "arcmin");

    CswParameter params1[] = {param1, param2};
    CswParamSet paramSet1 = {.params = params1, .numParams = 2};

    CswParamSet ar[] = {paramSet1};
    CswArrayValue values = {.values = ar, .numValues = 1};
    CswParameter param = cswMakeParameter("assemblyEventValue2", StructKey, values, "NoUnits");

    CswParameter params[] = {param};
    CswParamSet paramSet = {.params = params, .numParams = 1};

    CswEvent event = cswMakeEvent(SystemEvent, "csw.assembly", "myAssemblyEvent", paramSet);

    cswEventPublish(publisher, event);
    cswFreeEvent(event);
}
