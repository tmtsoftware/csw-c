//
// Created by abrighto on 7/29/19.
//


#include "csw/Event.h"
#include "csw/EventPublisher.h"
#include "csw/Parameter.h"

int main() {
    CswEventPublisherContext publisher = cswEventPublisherInit();

    double ar[] = {1.1, 2.2, 3.3};
    CswArrayValue values = {.values = ar, .numValues = 3};
    CswParameter param = cswMakeParameter(DoubleKey, "assemblyEventValue", values, "arcmin");
    CswParameter params[] = {param};
    CswParamSet paramSet = {.params = params, .numParams = 1};
    CswEvent event = cswMakeEvent(SystemEvent, "test.assembly", "myAssemblyEvent", paramSet);

    cswEventPublisherPublish(publisher, event);
}
