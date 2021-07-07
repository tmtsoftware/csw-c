#pragma once

#ifdef __cplusplus
extern "C" {
#endif

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

// CswUnits for parameters
typedef enum {
    // SI units
    csw_unit_angstrom,  // "Angstrom", "10 -1 nm"
    csw_unit_arcmin,  // "arcmin", "arc minute; angular measurement"
    csw_unit_arcsec,  // "arcsec", "arc second: angular measurement"
    csw_unit_day,  // "d", "day - 24 hours"
    csw_unit_degree,  // "deg", "degree: agular measurement 1/360 of full rotation"
    csw_unit_elvolt,  // "eV", "electron volt 1.6022x10-19 J"
    csw_unit_gram,  // "g", "gram 10-3 kg"
    csw_unit_hour,  // "h", "hour 3.6x10+3 s"
    csw_unit_hertz,  // "Hz", "frequency"
    csw_unit_joule,  // "J", "Joule: energy N m"
    csw_unit_kelvin,  // "K", "Kelvin: temperature with a null point at absolute zero"
    csw_unit_kilogram,  // "kg", "kilogram, base unit of mass in SI"
    csw_unit_kilometer, // "km", "kilometers - 10+3 m"
    csw_unit_liter,  // "l", "liter, metric unit of volume 10+3 cm+3"
    csw_unit_meter,  // "m", "meter: base unit of length in SI"
    csw_unit_marcsec,  // "mas", "milli arc second: angular measurement 10-3 arcsec"
    csw_unit_millimeter, // "mm", "millimeters - 10-3 m"
    csw_unit_millisecond, // "ms", "milliseconds - 10-3 s"
    csw_unit_micron,  // "µm", "micron: alias for micrometer"
    csw_unit_micrometer, // "µm", "micron: 10-6 m"
    csw_unit_minute,  // "min", "minute 6x10+1 s"
    csw_unit_newton,  // "N", "Newton: force"
    csw_unit_pascal,  // "Pa", "Pascal: pressure"
    csw_unit_radian,  // "rad", "radian: angular measurement of the ratio between the length of an arc and its radius"
    csw_unit_second,  // "s", "second: base unit of time in SI"
    csw_unit_sday,  // "sday", "sidereal day is the time of one rotation of the Earth: 8.6164x10+4 s"
    csw_unit_steradian, // "sr", "steradian: unit of solid angle in SI - rad+2"
    csw_unit_microarcsec, // "µas", "micro arcsec: angular measurement"
    csw_unit_volt,  // "V", "Volt: electric potential or electromotive force"
    csw_unit_watt,  // "W", "Watt: power"
    csw_unit_week,  // "wk", "week - 7 d"
    csw_unit_year,  // "yr", "year - 3.6525x10+2 d"

    // CGS units
    csw_unit_coulomb,  // "C", "coulomb: electric charge"
    csw_unit_centimeter, // "cm", "centimeter"
    csw_unit_erg,  // "erg", "erg: CGS unit of energy"

    // Astropyhsics units
    csw_unit_au,  // "AU", "astronomical unit: approximately the mean Earth-Sun distance"
    csw_unit_jansky,  // "Jy", "Jansky: spectral flux density - 10-26 W/Hz m+2"
    csw_unit_lightyear, // "lyr", "light year - 9.4607x10+15 m"
    csw_unit_mag,  // "mag", "stellar magnitude"

    // Imperial units
    csw_unit_cal, // "cal", "thermochemical calorie: pre-SI metric unit of energy"
    csw_unit_foot, // "ft", "international foot - 1.2x10+1 inch"
    csw_unit_inch, // "inch", "international inch - 2.54 cm"
    csw_unit_pound, // "lb", "international avoirdupois pound - 1.6x10+1 oz"
    csw_unit_mile, // "mi", "international mile - 5.28x10+3 ft"
    csw_unit_ounce, // "oz", "international avoirdupois ounce"
    csw_unit_yard, // "yd", "international yard - 3 ft"

    // Others - engineering
    csw_unit_NoUnits, // "none", "scalar - no units specified"
    csw_unit_encoder, // "enc", "encoder counts"
    csw_unit_count, // "ct", "counts as for an encoder or detector"
    csw_unit_pix,  // "pix", "pixel"
} CswUnits;


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
    double epoch;
    CswAngle inclination;
    CswAngle longAscendingNode;
    CswAngle argOfPerihelion;
    double meanDistance;  // AU
    double eccentricity;
    CswAngle meanAnomaly;
} CswMinorPlanetCoord;

// Represents Comet Coordinates (mirrors class of same name in the CSW Scala code).
typedef struct {
    CswCoordKeyType keyType;
    CswTag tag;
    double epochOfPerihelion;
    CswAngle inclination;
    CswAngle longAscendingNode;
    CswAngle argOfPerihelion;
    double perihelionDistance;  // AU
    double eccentricity;
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
        int *intValues;
        struct CswArrayValue *arrayValues;
        CswCoord *coordValues;
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

    // CswUnits: enum type corresponding to the defined CSW units
    CswUnits units;
} CswParameter;


// A parameter set (also the type of each values when key is "StructKey").
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
    long nanos;
} CswEventTime;

// These parameter time value types have the same structure as event time
typedef CswEventTime CswUtcTime;
typedef CswEventTime CswTaiTime;

/**
 * Returns an instance containing the current UTC time
 */
CswUtcTime cswUtcTime();

/**
 * Returns an instance containing the current TAI time
 */
CswUtcTime cswTaiTime();

/**
 * Constructor for UTC Time
 */
CswUtcTime cswMakeUtcTime(long seconds, int nanos);

/**
 * Constructor for TAI Time
 */
CswUtcTime cswMakeTaiTime(long seconds, int nanos);

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
    const char *source;

    // the name of event
    const char *eventName;

    // list of CswParameter (keys with values)
    CswParameter *paramSet;

    // Number of parameters in the paramSet (not encoded)
    int numParams;

    // the time the event was created (defaults to current time)
    CswEventTime eventTime;

    // event id (optional: Should leave empty unless received from event service)
    char *eventId;
} CswEvent;

// Public type of context for event service (publishing)
typedef void *CswEventServiceContext;

// Public type of context for event subscribing
typedef void *CswEventSubscriberContext;


// --- Public API ---

// --- Events ---

// Event constructor
CswEvent cswMakeEvent(CswEventType eventType, const char *source, const char *eventName, CswParamSet paramSet);

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

CswArrayValue makeArrayValues(void **values, int numArrays, CswArrayValue arrayValues[], int arraySize);

CswParameter cswMakeParameter(const char *keyName, CswKeyType keyType, CswArrayValue values, CswUnits units);

// Free any allocated memory for the parameter
void cswFreeParameter(CswParameter param);


// --- Coordinates ---

CswEqCoord cswMakeEqCoord(const char *tag, long raInUas, long decInUas, CswEqFrame frame, const char *catalogName,
                          double pmx, double pmy);

CswSolarSystemCoord cswMakeSolarSystemCoord(const char *tag, CswSolarSystemObject body);

CswMinorPlanetCoord cswMakeMinorPlanetCoord(const char *tag, double epoch, long inclinationInUas,
                                            long longAscendingNodeInUas, long argOfPerihelionInUas, double meanDistance,
                                            double eccentricity,
                                            long meanAnomalyInUas);

CswCometCoord cswMakeCometCoord(const char *tag, double epochOfPerihelion, long inclinationInUas,
                                long longAscendingNodeInUas, long argOfPerihelionInUas, double perihelionDistance,
                                double eccentricity);

CswAltAzCoord cswMakeAltAzCoord(const char *tag, long altInUas, long azInUas);

#ifdef __cplusplus
}
#endif
