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

//Include
#include "helpers_test.h"
#include "configuration.h"

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

int count =  0;
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

	// Initial drive foward
	while(nMotorEncoder[RightDrive] > direction * WAUTO_ITNITIAL_FOWARD)
  {
		moveForward(direction * DEFAULT_TRAVEL_SPEED);
	}

	turnDegrees(45, 50);

	if(HTIRS2readACDir(irsensor) >= WAUTO_BEACON_3and4_CHECK)
	{
		while(HTIRS2readACDir(irsensor) < 4 && nMotorEncoder[RightDrive] < WAUTO_34_score_dis)
			{
				moveForward(direction * WAUTO_34_score_dis);
				wait1Msec(5);
				count++;
				if( count > 1000)
				{
					halt();
					wait1Msec(30000);
				}
			}
			servoTarget[autoServo] = 150;
			wait1Msec(1000);
			servoTarget[autoServo] = 255;
			wait1Msec(500);

			while(nMotorEncoder[RightDrive] < WAUTO_34_score_dis)
			{
				moveForward(DEFAULT_TRAVEL_SPEED * direction);
				wait1Msec(5);
			}
			halt();

			tareHeading();
			count = 0;
			moveForward(DEFAULT_TRAVEL_SPEED * direction);
			turnDegrees(TURN_TO_RAMP_D, DEFAULT_TRAVEL_SPEED);

			halt();
			resetEncoders();
			wait1Msec(100);

			drivedistance(DEFAULT_TRAVEL_SPEED, DISTANCE_FROM_TURN_TO_RAMP, direction);
	}
	else
	{
		while(HTIRS2readACDir(irsensor) < 4 && nMotorEncoder[RightDrive] < WAUTO_12_score_dis)
			{
				moveForward(WAUTO_12_score_dis);
				wait1Msec(5);
				count++;
				if( count > 1000)
				{
					halt();
					wait1Msec(30000);
				}
			}
			servoTarget[autoServo] = 150;
			wait1Msec(1000);
			servoTarget[autoServo] = 255;
			wait1Msec(500);

			while(nMotorEncoder[RightDrive] < WAUTO_12_score_dis)
			{
				moveForward(DEFAULT_TRAVEL_SPEED);
				wait1Msec(5);
			}
			halt();

			tareHeading();
			count = 0;
			moveForward(DEFAULT_TRAVEL_SPEED);
			turnDegrees(TURN_TO_RAMP_D, DEFAULT_TRAVEL_SPEED * direction);

			halt();
			resetEncoders();
			wait1Msec(100);

			drivedistance(DEFAULT_TRAVEL_SPEED, DISTANCE_FROM_TURN_TO_RAMP, 1);
	}

}
