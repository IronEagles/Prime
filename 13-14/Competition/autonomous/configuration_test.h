#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  HTMotor)
#pragma config(Hubs,  S2, HTMotor,  none,     none,     none)
#pragma config(Sensor, S3,     GYRO,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S4,     HTSMUX,          sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     LeftDrive,     tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     RightDrive,    tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     scoreWrist,    tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     carWash,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     liftArm,       tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     scoreArm,      tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S2_C1_1,     pullUp,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_2,     flagSpinner,   tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    autoServo,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
// ==================================================================================================

// INCLUDES
#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "drivers/hitechnic-gyro.h"
#include "drivers/hitechnic-sensormux.h"
#include "drivers/hitechnic-irseeker-v2.h"
#include "drivers/lego-touch.h"

const tMUXSensor irsensor1 = msensor_S4_2;
const tMUXSensor topTouch = msensor_S4_1;
const tMUXSensor bottomTouch = msensor_S4_3;
const tMUXSensor irsensor2 = msensor_S4_4;
float currHeading = 0.0;

#define BLUETAPE 35
#define SPEED 40



const int TICKS_PER_REVOLUTION = 4*360;

// auto_quick_right.c variables
const float DISTANCE_TO_BASKET_FROM_INIT_R = 1.5;
const float DISTANCE_TO_BASKET_FROM_INIT_L = 0.5;
const float DISTANCE_FROM_BASKET_TO_TURN_R = 0.8;
const float DISTANCE_FROM_BASKET_TO_TURN_L = 1.65;
const int DEFAULT_TRAVEL_SPEED = 70;
const int AUTO_SCORING_ARM_DEPLOY_DISTANCE = 200;
const int AUTO_SCORING_ARM_HOME = 255;
const int WAIT_BEFORE_RETRACT_AUTO_SCORE_ARM_MS = 500;
const int TURN_TO_RAMP_D = 48;
const float DISTANCE_FROM_TURN_TO_RAMP = 4.4;
// WAIT IR CONSTANTS
const float WAUTO_ITNITIAL_FORWARD = 2.2;
const int WAUTO_BEACON_3and4_CHECK = 6;
const float WAUTO_34_score_disT = 1.9*TICKS_PER_REVOLUTION;
const float WAUTO_12_score_disT = 2.9;
const float WAUTO_34_score_disF = 1.4*TICKS_PER_REVOLUTION;
const float WAUTO_12_score_disF = 1.7;
const int DEFAULT_AUTO_SPEED = 50;
const int TURN_TO_RAMP_WR = 54;
const int TURN_TO_RAMP_WL = 49;
const int RAMP_SPEED = 100;
const float DISTANCE_FROM_TURN_TO_RAMP_W = 5.0;
const int WAIT_MENU_TIMEOUT = 20000;

const int ENCODER_CHECK = 360;

//Straight IR Right config
const float BASKET_1_R = 0.45;
const float BASKET_2_R = 0.6;
const float BASKET_3_R = 1.55;
const float BASKET_4_R = 0.72;
const float STRAIGHT_IR_FORWARD_AFTER_SCORE = 0.9;
const float STRAIGHT_IR_TURN_1_DEGREES = -36.5;
const float STRAIGHT_IR_FORWARD_RAMP_ALIGN = 3.0;
const float STRAIGHT_IR_TURN_2_DEGREES = -80;
const float STRAIGHT_IR_FORWARD_ON_RAMP = 4.0;

//Straight IR Left config
const float BASKET_1_L = 0.65;
const float BASKET_2_L = 1.6;
const float BASKET_3_L = 0.6;
const float BASKET_4_L = 1.23;
const float STRAIGHT_IR_FORWARD_AFTER_SCORE_L = 0.4;
const float STRAIGHT_IR_TURN_1_DEGREES_L = 34.5;
const float STRAIGHT_IR_FORWARD_RAMP_ALIGN_L = 2.8;
const float STRAIGHT_IR_TURN_2_DEGREES_L = 80;
const float STRAIGHT_IR_FORWARD_ON_RAMP_L = 5.1;
