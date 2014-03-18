#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  HTMotor)
#pragma config(Hubs,  S2, HTMotor,  none,     none,     none)
#pragma config(Sensor, S3,     GYRO,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S4,     HTSMUX,          sensorI2CCustom)5
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
#include "configuration_test.h"

// GLOBALS

//Tasks

int timeinterface ()
{
	int yourtime = 0;

	ClearTimer(T1);

	until(nNxtButtonPressed == 3 || time1[T1]>WAIT_MENU_TIMEOUT)
	{
		eraseDisplay();
		nxtDisplayBigTextLine(3, "Wait?");
		nxtDisplayBigTextLine(5, "-> %d", yourtime);

		if(nNxtButtonPressed == 2)
		{
			yourtime -= 5;
			wait1Msec(400);
		}
		if(nNxtButtonPressed == 1)
		{
			yourtime += 5;
			wait1Msec(400);
		}

	}
	return yourtime;
}

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
int direction = 1;

void initializeRobot()
{
	if (!MUXtest())
	{
		PlayTone(1200,500);
	}


	// Initialize encoders
  resetEncoders();

  return;
}

task main()
{

	int wait = timeinterface();

	bool irscored = false;

	initializeRobot();
	wait1Msec(2);
	waitForStart();
	// Spawn heading tracking thread
	StartTask(heading);
  wait1Msec(wait*1000);

	// Initial drive foward
	drivedistance(DEFAULT_AUTO_SPEED, BASKET_1_R, direction);
	//halt();

	//Check and score
	if(HTIRS2readACDir(irsensor) == 5 && !irscored)
	{
			halt();
			wait1Msec(10);
			servoTarget[autoServo] = AUTO_SCORING_ARM_DEPLOY_DISTANCE;
			wait1Msec(WAIT_BEFORE_RETRACT_AUTO_SCORE_ARM_MS);
			servoTarget[autoServo] = 255;
			wait1Msec(500);
			irscored=true;
	}


	drivedistance(DEFAULT_AUTO_SPEED, BASKET_2_R, direction);
	//halt();

	//Check and score
	if(HTIRS2readACDir(irsensor) == 5 && !irscored)
	{
			halt();
			wait1Msec(10);
			servoTarget[autoServo] = AUTO_SCORING_ARM_DEPLOY_DISTANCE;
			wait1Msec(WAIT_BEFORE_RETRACT_AUTO_SCORE_ARM_MS);
			servoTarget[autoServo] = 255;
			wait1Msec(500);
			irscored=true;
	}

	drivedistance(DEFAULT_AUTO_SPEED, BASKET_3_R, direction);
	//halt();

	//Check and score
	if(HTIRS2readACDir(irsensor) == 5 && !irscored)
	{
			halt();
			wait1Msec(10);
			servoTarget[autoServo] = AUTO_SCORING_ARM_DEPLOY_DISTANCE;
			wait1Msec(WAIT_BEFORE_RETRACT_AUTO_SCORE_ARM_MS);
			servoTarget[autoServo] = 255;
			wait1Msec(500);
			irscored=true;
	}

	drivedistance(DEFAULT_AUTO_SPEED, BASKET_4_R, direction);
	//halt();

	//Check and score
	if(!irscored)
	{
			halt();
			wait1Msec(10);
			servoTarget[autoServo] = AUTO_SCORING_ARM_DEPLOY_DISTANCE;
			wait1Msec(WAIT_BEFORE_RETRACT_AUTO_SCORE_ARM_MS);
			servoTarget[autoServo] = 255;
			wait1Msec(500);
			irscored=true;
	}

	drivedistance(DEFAULT_AUTO_SPEED, STRAIGHT_IR_FORWARD_AFTER_SCORE, direction);

	turnDegrees(STRAIGHT_IR_TURN_1_DEGREES, DEFAULT_AUTO_SPEED);

	drivedistance(DEFAULT_AUTO_SPEED, STRAIGHT_IR_FORWARD_RAMP_ALIGN, direction);

  turnDegrees(STRAIGHT_IR_TURN_2_DEGREES, DEFAULT_AUTO_SPEED);
	drivedistance(DEFAULT_AUTO_SPEED, STRAIGHT_IR_FORWARD_ON_RAMP, direction);

}
