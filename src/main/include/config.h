#define ID_PDP 0
#define PDP_TYPE PDP::ModuleType::kCTRE

#define JOYSTICK_PORT 0

// THESE ARE NOT REAL WAKE UP! (overwrite with actual CAN IDs)
#define ID_RMOTOR1 1
#define ID_RMOTOR2 2
#define ID_LMOTOR1 3
#define ID_LMOTOR2 4
#define MCONTROLLER_MODE VictorSPXControlMode::PercentOutput

// TODO: Add these sensitivities to an external config file. It should not be hard coded.
#define JOYSTICK_SENS 1.0

#define L_MOTOR_SENS 0.8
#define R_MOTOR_SENS 0.8

// TODO: Add these distances to a file so they can be ssh'd
#define FAR_SCORE_DIST 1.0
#define FAR_MOBILITY_DIST 1.0
#define MIDDLE_SCORE_DIST 1.0
#define MIDDLE_DOCK_DIST 2.0
#define MIDDLE_MOBILITY_DIST 0.8
#define STATIONADJ_SCORE_DIST 1.0
#define STATIONADJ_MOBILITY_DIST 3.0
#define MOBILITY_WAIT_TIME_SEC 1.0