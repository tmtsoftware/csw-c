//
// Created by abrighto on 8/6/19.
//

#include "csw.h"

CswEqCoord cswMakeEqCoord(const char *tag, long raInUas, long decInUas, CswEqFrame frame,
                          const char *catalogName, double pmx, double pmy) {
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

CswSolarSystemCoord cswMakeSolarSystemCoord(const char *tag, CswSolarSystemObject body) {
    CswTag cswTag = {.name = tag};
    CswSolarSystemCoord c = {
            .keyType = SolarSystemCoordKeyType,
            .tag  = cswTag,
            .body = body,
    };
    return c;
}

CswMinorPlanetCoord cswMakeMinorPlanetCoord(const char *tag, double epoch, long inclinationInUas,
                                            long longAscendingNodeInUas, long argOfPerihelionInUas, double meanDistance,
                                            double eccentricity,
                                            long meanAnomalyInUas) {
    CswTag cswTag = {.name = tag};
    CswAngle inclination = {.uas = inclinationInUas};
    CswAngle longAscendingNode = {.uas = longAscendingNodeInUas};
    CswAngle argOfPerihelion = {.uas = argOfPerihelionInUas};
    CswAngle meanAnomaly = {.uas = meanAnomalyInUas};
    CswMinorPlanetCoord c = {
            .keyType = MinorPlanetCoordKeyType,
            .tag  = cswTag,
            .epoch = epoch,
            .inclination = inclination,
            .longAscendingNode = longAscendingNode,
            .argOfPerihelion = argOfPerihelion,
            .meanDistance = meanDistance,
            .eccentricity = eccentricity,
            .meanAnomaly = meanAnomaly
    };
    return c;
}

CswCometCoord cswMakeCometCoord(const char *tag, double epochOfPerihelion, long inclinationInUas,
                                long longAscendingNodeInUas, long argOfPerihelionInUas, double perihelionDistance,
                                double eccentricity) {
    CswTag cswTag = {.name = tag};
    CswAngle inclination = {.uas = inclinationInUas};
    CswAngle longAscendingNode = {.uas = longAscendingNodeInUas};
    CswAngle argOfPerihelion = {.uas = argOfPerihelionInUas};
    CswCometCoord c = {
            .keyType = CometCoordKeyType,
            .tag  = cswTag,
            .epochOfPerihelion = epochOfPerihelion,
            .inclination = inclination,
            .longAscendingNode = longAscendingNode,
            .argOfPerihelion = argOfPerihelion,
            .perihelionDistance = perihelionDistance,
            .eccentricity = eccentricity,
    };
    return c;
}

CswAltAzCoord cswMakeAltAzCoord(const char *tag, long altInUas, long azInUas) {
    CswTag cswTag = {.name = tag};
    CswAngle alt = {.uas = altInUas};
    CswAngle az = {.uas = azInUas};
    CswAltAzCoord c = {
            .keyType = AltAzCoordKeyType,
            .tag  = cswTag,
            .alt = alt,
            .az = az,
    };
    return c;
}
