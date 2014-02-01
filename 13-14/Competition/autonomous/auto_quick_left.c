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

// Filename: auto_quick_right.c
// Description: Quickly score autonomous block in closest end basket and immediately turn left onto the ramp.
// Last Modified: 2/1/14



#include "configuration.h"
//#include "helpers.h"
#include "helpers_test.h"


// GLOBALS

//Tasks
task heading()
{
	float delTime = 0.0;
	float prevHeading = 0.0;
	float curRate = 0.0;
	HTGYROstartCal(GYRO);
   while (true) {
   	time1[T1] = 0;
    	curRate = HTGYROreadRot(GYRO);
    	if (abs(curRate) > 3) {
      	prevHeading = currHeading;
      	currHeading = prevHeading + (curRate * delTime);
      	if (currHeading > 360) currHeading -= 360;
      	else if (currHeading < 0) currHeading += 360;
    		}
    nxtDisplayTextLine(4, "Curr = %f", currHeading);
   	wait1Msec(5);
    	delTime = ((float)time1[T1]) / 1000;
    	//delTime /= 1000;
	}

}

int direction = -1;

void initializeRobot()
{
	// Initialize encoders
  resetEncoders();

	// Spawn heading tracking thread
	StartTask(heading);
  wait1Msec(1000);

  return;
}

task main()
{
	initializeRobot();
	wait1Msec(2);
	waitForStart();

	// STEP 1: Move forward to the end basket
	while(nMotorEncoder[RightDrive] > direction * DISTANCE_TO_BASKET_FROM_INIT)
  {
		moveForward(direction * DEFAULT_TRAVEL_SPEED);
	}

	// STEP 2: Deploy auto-scoring arm
	servoTarget[autoServo] = AUTO_SCORING_ARM_DEPLOY_DISTANCE;
	wait1Msec(WAIT_BEFORE_RETRACT_AUTO_SCORE_ARM_MS);
	servoTarget[autoServo] = AUTO_SCORING_ARM_HOME;
	wait1Msec(500);

	while(nMotorEncoder[LeftDrive] > direction * DISTANCE_FROM_BASKET_TO_TURN)
	{
		moveForward(direction * DEFAULT_TRAVEL_SPEED);
	}

	motor[RightDrive] = DEFAULT_TRAVEL_SPEED;
	motor[LeftDrive] = direction * DEFAULT_TRAVEL_SPEED;


	while(true)
	{
		wait1Msec(10);
		//if (currHeading >= 45 && currHeading < 70) break;
		turnDegrees(TURN_TO_RAMP_D, DEFAULT_TRAVEL_SPEED);
	}
	halt();
	resetEncoders();
	wait1Msec(100);

		//STEP 7: Drive onto ramp
	drivedistance(DEFAULT_TRAVEL_SPEED, DISTANCE_FROM_TURN_TO_RAMP, direction);

}
