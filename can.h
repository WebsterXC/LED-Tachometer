//This file defines PID codes for the CAN protocol to gather engine data.

/* Will Burgin (waburgin), 2015.
 * If you find my files helpful, please give credit!
 */

// 8-Byte format: {0x02}{0x01}{PID}{0x00}{0x00}{0x00}{0x00}{0x00}
//                 Mode |Form|Code|Empty|Empty|Empty|Empty|Empty|
#ifndef CAN_HEADERS
#define CAN_HEADERS

#define NUM_PARAMS 25

//Engine Data
#define ENGINE_LOAD           0x04
#define THROTTLE_LOAD         0x11
#define TIMING_ADVANCE        0x0E

//Fuel Trims
#define STFT1                 0x06
#define STFT2                 0x08
#define INJECTION_TIMING      0x5D
#define ENGINE_FUEL_RATE      0x5E

//Engine
#define ENGINE_RPM            0x0C
#define ENGINE_SPEED          0x0D

//Barometrics
#define PRESSURE_BAROMETRIC   0x33
#define PRESSURE_FUEL         0x0A
#define PRESSURE_FUEL_RAIL    0x23
#define PRESSURE_EVAP_VAPOR   0x32
#define PRESSURE_INTAKE_MAN   0x0B
#define FLOW_RATE_MAF         0x10
#define PRESSURE_EXHAUST      0x73

//Temperatures
#define TEMP_COOLANT          0x05
#define TEMP_OIL              0x5C
#define INTAKE_AIR_TEMP       0x0F

//Forced-Induction Engines
#define TURBO_INLET_PRESSURE  0x6F
#define TURBO_BOOST_CONTROL   0x70
#define TURBO_WASTEGATE       0x72
#define TURBO_RPM             0x74
#define TURBO_TEMP_0          0x75
#define TURBO_TEMP_1          0x76

/*Define modeset for OBDII devices*/
#define MODE_REALTIME         0x01
#define MODE_FREEZE           0x02
#define MODE_DTC              0x03
#define MODE_CLEAR_DTC        0x04
#define MODE_VINFO            0x09

#endif
