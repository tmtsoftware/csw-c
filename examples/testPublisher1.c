//
// Created by abrighto on 7/29/19.
//


#include "csw/csw.h"

int main() {
    CswEventServiceContext publisher = cswEventPublisherInit();

    double ar[] = {1.1, 2.2, 3.3};
    CswArrayValue values = {.values = ar, .numValues = 3};
    CswParameter param = cswMakeParameter("assemblyEventValue", DoubleKey, values, "arcmin");
    CswParameter params[] = {param};
    CswParamSet paramSet = {.params = params, .numParams = 1};
    CswEvent event = cswMakeEvent(SystemEvent, "csw.assembly", "myAssemblyEvent", paramSet);
    cswEventPublish(publisher, event);
    cswFreeEvent(event);
}
