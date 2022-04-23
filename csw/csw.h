#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// --- Parameters ---

// Note: if you update this, also update Parameter.c:_keyTypeNames!
typedef enum {
    ChoiceKey,
    StringKey,
    UTCTimeKey,
    TAITimeKey,
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
// Note: If you update this, also update Parameter.c:_unitNames!
typedef enum {
    // SI units
    csw_unit_angstrom, // "Angstrom", "angstrom"
    csw_unit_alpha, // "alpha", "alpha: fine structure constant"
    csw_unit_ampere, // "A", "ampere: unit of electric current"
    csw_unit_arcmin, // "arcmin", "arc minute; angular measurement"
    csw_unit_arcsec, // "arcsec", "arc second: angular measurement"
    csw_unit_bar, // "bar", "bar: metric ton of pressure"
    csw_unit_candela, // "candela ", "candela(lumen/sr)"
    csw_unit_day, // "d", "day"
    csw_unit_degree, // "deg", "degree: angular measurement 1/360 of full rotation"
    csw_unit_degC, // "degC", "Degree Celsius K"
    csw_unit_degF, // "degF", "Fahrenheit"
    csw_unit_elvolt, // "eV", "electron volt"
    csw_unit_gauss, // "gauss", "gauss"
    csw_unit_gram, // "g", "gram"
    csw_unit_hertz, // "Hz", "frequency"
    csw_unit_henry, // "henry", "Henry"
    csw_unit_hour, // "h", "hour"
    csw_unit_joule, // "J", "Joule: energy"
    csw_unit_kelvin, // "K", "Kelvin: temperature with a null point at absolute zero"
    csw_unit_kilogram, // "kg", "kilogram, base unit of mass in SI"
    csw_unit_kilometer, // "km", "kilometers"
    csw_unit_liter, // "l", "liter, metric unit of volume"
    csw_unit_lm, // "lm", "lumen"
    csw_unit_lsun, // "lsun", "solar luminosity"
    csw_unit_lx, // "lx", "lux(lm/m2)"
    csw_unit_mas, // "mas", "milli arc second"
    csw_unit_me, // "me", "me(electron_mass)"
    csw_unit_meter, // "m", "meter: base unit of length in SI"
    csw_unit_microarcsec, // "µas", "micro arcsec: angular measurement"
    csw_unit_millimeter, // "mm", "millimeters"
    csw_unit_millisecond, // "ms", "milliseconds"
    csw_unit_micron, // "µm", "micron: alias for micrometer"
    csw_unit_micrometer, // "µm", "micron"
    csw_unit_minute, // "min", "minute"
    csw_unit_MJD, // "MJD", "Mod. Julian Date"
    csw_unit_mol, // "mol", "mole- unit of substance"
    csw_unit_month, // "month", "Month name or number"
    csw_unit_mmyy, // "mmyy", "mmyy: Month/Year"
    csw_unit_mu0, // "mu0", "mu0: magnetic constant"
    csw_unit_muB, // "muB", "Bohr magneton"
    csw_unit_nanometer, // "nm", "nanometers"
    csw_unit_newton, // "N", "Newton: force"
    csw_unit_ohm, // "ohm", "Ohm"
    csw_unit_pascal, // "Pa", "Pascal: pressure"
    csw_unit_pi, // "pi", "pi"
    csw_unit_pc, // "pc", "parsec"
    csw_unit_ppm, // "ppm", "part per million"
    csw_unit_radian, // "rad", "radian: angular measurement of the ratio between the length of an arc and its radius"
    csw_unit_second, // "s", "second: base unit of time in SI"
    csw_unit_sday, // "sday", "sidereal day is the time of one rotation of the Earth"
    csw_unit_steradian, // "sr", "steradian: unit of solid angle in SI"
    csw_unit_volt, // "V", "Volt: electric potential or electromotive force"
    csw_unit_watt, // "W", "Watt: power"
    csw_unit_Wb, // "Wb", "Weber"
    csw_unit_week, // "wk", "week"
    csw_unit_year, // "yr", "year"

    // CGS units
    csw_unit_coulomb, // "C", "coulomb: electric charge"
    csw_unit_centimeter, // "cm", "centimeter"
    csw_unit_D, // "Debye", "Debye(dipole) A electric dipole moment "
    csw_unit_dyn, // "dyne", "dyne: Unit of force "
    csw_unit_erg, // "erg", "erg: CGS unit of energy"

    // Astropyhsics units
    csw_unit_au, // "AU", "astronomical unit: approximately the mean Earth-Sun distance"
    csw_unit_a0, // "a0","bohr radius: probable distance between the nucleus and the electron in a hydrogen atom in its ground state"
    csw_unit_c, // "c", "c: speed of light"
    csw_unit_cKayser, // "cKayser", "cKayser"
    csw_unit_crab, // "crab", "Crab: astrophotometrical unit for measurement of the intensity of Astrophysical X-ray sources"
    csw_unit_damas, // "d:m:s", "damas: degree arcminute arcsecond (sexagesimal angle from degree)"
    csw_unit_e, // "e", "electron charge"
    csw_unit_earth, // "earth", "earth (geo) unit"
    csw_unit_F, // "F", "Farad: F"
    csw_unit_G, // name = "G", "gravitation constant"
    csw_unit_geoMass, // "geoMass", "Earth Mass"
    csw_unit_hm, // "hm", "hour minutes (sexagesimal time from hours)"
    csw_unit_hms, // "hms", "hour minutes seconds (sexagesimal time from hours)"
    csw_unit_hhmmss, // "HH:MM:SS", "hour minutes seconds (sexagesimal time)"
    csw_unit_jansky, // "Jy", "Jansky: spectral flux density "
    csw_unit_jd, // "jd", "Julian Day"
    csw_unit_jovmass, // "jovMass", "Jupiter mass"
    csw_unit_lightyear, // "lyr", "light year"
    csw_unit_mag, // "mag", "stellar magnitude"
    csw_unit_mjup, // "Mjup", "Jupiter mass"
    csw_unit_mp, // "mp", "proton_mass"
    csw_unit_minsec, // "m:s", "minutes seconds (sexagesimal time from minutes)"
    csw_unit_msun, // "Msun", "solar mass"
    csw_unit_photon, // "photon", "photon"
    csw_unit_rgeo, // "Rgeo", "Earth radius (eq)"
    csw_unit_rjup, // "Rjup", "Jupiter Radius(eq)"
    csw_unit_rsun, // "Rsun", "solar radius"
    csw_unit_rydberg, // "Rydberg", "energy of the photon whose wavenumber is the Rydberg constant"
    csw_unit_seimens, // "seimens", "Seimens"
    csw_unit_tesla, // "tesla", "Tesla"
    csw_unit_u, // "u", "atomic mass unit"

    // Imperial units
    csw_unit_barn, // "barn", "barn: metric unit of area"
    csw_unit_cal, // "cal", "thermochemical calorie: pre-SI metric unit of energy"
    csw_unit_foot, // "ft", "international foot"
    csw_unit_inch, // "inch", "international inch"
    csw_unit_pound, // "lb", "international avoirdupois pound"
    csw_unit_mile, // "mi", "international mile"
    csw_unit_ounce, // "oz", "international avoirdupois ounce"
    csw_unit_yard, // "yd", "international yard"

    // Others - engineering
    csw_unit_NoUnits, // "none", "scalar - no units specified"
    csw_unit_bit, // "bit", "bit: binary value of 0 or 1"
    csw_unit_encoder, // "enc", "encoder counts"
    csw_unit_count, // "ct", "counts as for an encoder or detector"
    csw_unit_mmhg, // "mmHg", "millimetre of mercury is a manometric unit of pressure"
    csw_unit_percent, // "percent", "percentage"
    csw_unit_pix, // "pix", "pixel"

    // Datetime units
    csw_unit_tai, // "TAI", "TAI time unit"
    csw_unit_utc, // "UTC", "UTC time unit"
    csw_unit_date, // "date", "date"
    csw_unit_datetime  // "datetime", "date/time"
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

// Note: if you update this, also update Parameter.c:_solarSystemObjectNames!
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
        short *shortValues;
        float *floatValues;
        double *doubleValues;
        char **stringValues;
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


// A parameter set.
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
 * Closes and frees the CSW event publisher connection.
 * @param context the return value from cswEventPublisherInit()
 */
void cswEventPublisherClose(CswEventServiceContext context);

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
