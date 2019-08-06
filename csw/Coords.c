//
// Created by abrighto on 8/6/19.
//

#include "csw.h"
#include "cswImpl.h"

CswEqCoord cswMakeEqCoord(const char* tag, long raInUas, long decInUas, CswEqFrame frame, const char *catalogName, double pmx, double pmy) {
    CswTag cswTag = {.name = tag};
    CswAngle ra = {.uas = raInUas};
    CswAngle dec = {.uas = decInUas};
    CswProperMotion pm = {.pmx = pmx, .pmy = pmy};
    CswEqCoord c = {
            .keyType = EqCoordKeyType,
            .tag  = cswTag,
            .ra = ra,
            .dec = dec,
            .frame = frame,
            .catalogName = catalogName,
            .pm = pm
    };
    return c;
}