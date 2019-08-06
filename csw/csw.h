//
// Created by abrighto on 8/6/19.
//

#ifndef CSW_C_CSW_H
#define CSW_C_CSW_H


// --- Parameters ---

typedef enum {
    ChoiceKey,
    StringKey,
    StructKey,
    UTCTimeKey,
    TAITimeKey,
    RaDecKey,
    EqCoordKey,
    SolarSystemCoordKey,
    MinorPlanetCoordKey,
    CometCoordKey,
    AltAzCoordKey,
    CoordKey,
    BooleanKey,
    CharKey,
    ByteKey,
    ShortKey,
    LongKey,
    IntKey,
    FloatKey,
    DoubleKey,
    ByteArrayKey,
    ShortArrayKey,
    LongArrayKey,
    IntArrayKey,
    FloatArrayKey,
    DoubleArrayKey,
    ByteMatrixKey,
    ShortMatrixKey,
    LongMatrixKey,
    IntMatrixKey,
    FloatMatrixKey,
    DoubleMatrixKey
} CswKeyType;


// --- Coordinate Types ----

// A tag is a label to indicate the use of the coordinate
typedef struct {
    const char *name;
} CswTag;

// A wrapper for Angle values (See the csw.params.core.models.Angle class).
// Normally Angle would be stored in double as radians, but this introduces rounding errors.
// This struct stores the value in microarc seconds to prevent rounding errors.
typedef struct {
    long uas;
} CswAngle;

typedef enum {
    ICRS,
    FK5
} CswEqFrame;

typedef struct {
    double pmx;
    double pmy;
} CswProperMotion;

typedef enum {
    Mercury,
    Venus,
    Moon,
    Mars,
    Jupiter,
    Saturn,
    Neptune,
    Uranus,
    Pluto
} CswSolarSystemObject;

// A subset of KeyType used for coordinate types
typedef enum {
    EqCoordKeyType = EqCoordKey,
    SolarSystemCoordKeyType = SolarSystemCoordKey,
    MinorPlanetCoordKeyType = MinorPlanetCoordKey,
    CometCoordKeyType = CometCoordKey,
    AltAzCoordKeyType = AltAzCoordKey,
} CswCoordKeyType;

// Common base type of coordinate types (Used to figure out which type of coordinate it is when key is CoordKey)
typedef struct {
    CswCoordKeyType keyType; // needed to determine "virtual" type of coord
    CswTag tag;
} CswCoordBase;

// Represents equatorial coordinates (mirrors class of same name in the CSW Scala code).
typedef struct {
    CswCoordKeyType keyType;
    CswTag tag;
    CswAngle ra;
    CswAngle dec;
    CswEqFrame frame;
    const char *catalogName;
    CswProperMotion pm;
} CswEqCoord;

// Represents Solar System Coordinates (mirrors class of same name in the CSW Scala code).
typedef struct {
    CswCoordKeyType keyType;
    CswTag tag;
    CswSolarSystemObject body;
} CswSolarSystemCoord;


// Represents Minor Planet Coordinates (mirrors class of same name in the CSW Scala code).
typedef struct {
    CswCoordKeyType keyType;
    CswTag tag;
    float epoch;
    CswAngle inclination;
    CswAngle longAscendingNode;
    CswAngle argOfPerihelion;
    float meanDistance;  // AU
    float eccentricity;
    CswAngle meanAnomaly;
} CswMinorPlanetCoord;

// Represents Comet Coordinates (mirrors class of same name in the CSW Scala code).
typedef struct {
    CswCoordKeyType keyType;
    CswTag tag;
    float epochOfPerihelion;
    CswAngle inclination;
    CswAngle longAscendingNode;
    CswAngle argOfPerihelion;
    float perihelionDistance;  // AU
    float eccentricity;
} CswCometCoord;

// Represents Alt-Az Coordinates (mirrors class of same name in the CSW Scala code).
typedef struct {
    CswCoordKeyType keyType;
    CswTag tag;
    CswAngle alt;
    CswAngle az;
} CswAltAzCoord;

// Used as the type when key is CoordKey, since an array of these can contain different coord types
typedef union {
    CswCoordBase coordBase;
    CswEqCoord eqCoord;
    CswSolarSystemCoord solarSystemCoord;
    CswMinorPlanetCoord minorPlanetCoord;
    CswCometCoord cometCoord;
    CswAltAzCoord altAzCoord;
} CswCoord;

// ---

typedef struct CswArrayValue {
    // An array of primitive values, or an array of CSwArrayValue for array and matrix types or the csw "struct" type.
    union {
        void *values;
        int* intValues;
        struct CswArrayValue *arrayValues;
        CswCoord* coordValues;
    };

    // The number of values in the above array
    int numValues;
} CswArrayValue;

// A Parameter (keys with values, units).
typedef struct {

    // The name of the key
    const char *keyName;

    // Enum type of param key
    CswKeyType keyType;

    // Contains an Array of values of the given type
    CswArrayValue values;

    // See https://tmtsoftware.github.io/csw/0.7.0-RC1/messages/units.html for list of unit names.
    const char *units;
} CswParameter;


// A parameter set (also the value when key is "StructKey").
typedef struct {
    // a list of Parameters
    CswParameter *params;

    // The number of parameters in this param set
    int numParams;
} CswParamSet;



// --- Events ----

// An EventTime containing seconds since the epoch (1970) and the offset from seconds in nanoseconds
typedef struct {
    long seconds;
    int nanos;
} CswEventTime;

typedef enum {
    SystemEvent,
    ObserveEvent
} CswEventType;

/**
 * An Event that can be published to the event service
 */
typedef struct {
    // SystemEvent or ObserveEvent (not encoded)
    CswEventType eventType;

    // prefix representing source of the event
    const char* source;

    // the name of event
    const char* eventName;

    // list of CswParameter (keys with values)
    CswParameter* paramSet;

    // Number of parameters in the paramSet (not encoded)
    int numParams;

    // the time the event was created (defaults to current time)
    CswEventTime eventTime;

    // event id (optional: Should leave empty unless received from event service)
    char* eventId;
} CswEvent;

// Public type of context for event service (publishing)
typedef void* CswEventServiceContext;

// Public type of context for event subscribing
typedef void* CswEventSubscriberContext;


// --- Public API ---

// --- Events ---

// Event constructor
CswEvent cswMakeEvent(CswEventType eventType, const char* source, const char* eventName, CswParamSet paramSet);

// Free any allocated memory for the event
void cswFreeEvent(CswEvent event);

/**
 * Returns an instance containing the current time
 */
CswEventTime cswEventTime();

/**
 * Constructor for Event Time
 */
CswEventTime cswMakeEventTime(long seconds, int nanos);

/**
 * Initializes the event publisher
 * @return context to be used on subsequent calls
 */
CswEventServiceContext cswEventPublisherInit();

/**
 * Publishes an event to the Event Service
 *
 * @param context return value from cswEventPublisherInit()
 * @param event Event event: Event to be published
 * @return 0 if OK, otherwise a non-zero value
 */
int cswEventPublish(CswEventServiceContext context, CswEvent event);


// --- Parameters ---

CswArrayValue makeArrayValues(void** values, int numArrays, CswArrayValue arrayValues[numArrays], int arraySize);
//CswArrayValue makeMatrixValues(void*** values, int numMatrices, int numRows, int numCols);

CswParameter cswMakeParameter(const char *keyName, CswKeyType keyType, CswArrayValue values, const char *units);

// Free any allocated memory for the parameter
void cswFreeParameter(CswParameter param);


// --- Coordinates ---

CswEqCoord cswMakeEqCoord(const char* tag, long raInUas, long decInUas, CswEqFrame frame, const char *catalogName, double pmx, double pmy);


#endif //CSW_C_CSW_H
