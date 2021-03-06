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
int direction = -1;

void initializeRobot()
{
	if (!MUXtest())
	{
		PlayTone(1200,500);
	}


	// Initialize encoders
  resetEncoders();

	// Spawn heading tracking thread
	StartTask(heading);
  wait1Msec(1000);

  return;
}

task main()
{

	int wait = timeinterface();

	initializeRobot();
	wait1Msec(2);
	waitForStart();
	wait1Msec(wait*1000);

	// Initial drive foward
	drivedistance(DEFAULT_AUTO_SPEED, WAUTO_ITNITIAL_FORWARD, direction);

	turnDegrees(-43, 50);
	halt();
	wait1Msec(100);
	resetEncoders();

	if(HTIRS2readACDir(irsensor) >= WAUTO_BEACON_3and4_CHECK || HTIRS2readACDir(irsensor) ==0)
	{
		while((HTIRS2readACDir(irsensor) >= 6 || HTIRS2readACDir(irsensor) == 0 )  && nMotorEncoder[RightDrive] > direction*WAUTO_34_score_disF)
			{
				moveForward(direction* DEFAULT_AUTO_SPEED);
				wait1Msec(5);
				count++;
				if( count > 1000)
				{
					halt();
					wait1Msec(30000);
				}
			}
			halt();
			wait1Msec(10);
			servoTarget[autoServo] = 150;
			wait1Msec(1000);
			servoTarget[autoServo] = 255;
			wait1Msec(500);

			while(nMotorEncoder[RightDrive] > direction*WAUTO_34_score_disT)
			{
				moveForward(DEFAULT_AUTO_SPEED * direction);
				wait1Msec(5);
			}
			halt();

			tareHeading();
			count = 0;
			//moveForward(DEFAULT_AUTO_SPEED * direction);
			turnDegrees(TURN_TO_RAMP_WR, DEFAULT_AUTO_SPEED);
			halt();
			wait1Msec(10);
			resetEncoders();

			drivedistance(DEFAULT_AUTO_SPEED, 4.0, direction);
			halt();
			wait1Msec(10);

			tareHeading();
			turnDegrees(90, 65);
			halt();
			wait1Msec(10);
			resetEncoders();



			halt();
			resetEncoders();
			wait1Msec(100);

			drivedistance(RAMP_SPEED, DISTANCE_FROM_TURN_TO_RAMP_W, direction);
			halt();
	}
	else
	{
		resetEncoders();
		while((HTIRS2readACDir(irsensor) <= 4) && nMotorEncoder[RightDrive] < WAUTO_12_score_disF*TICKS_PER_REVOLUTION)
			{
				moveForward((-1*direction)* DEFAULT_AUTO_SPEED);
				wait1Msec(5);
				count++;
				if( count > 1000)
				{
					halt();
					wait1Msec(30000);
				}
			}
			halt();

			int currEncoder = nMotorEncoder[RightDrive];

			while(nMotorEncoder[RightDrive] < currEncoder+(0.2*TICKS_PER_REVOLUTION))
				{
					moveForward((-1*direction)*DEFAULT_AUTO_SPEED);
				}
			halt();
			wait1Msec(10);
			servoTarget[autoServo] = 150;
			wait1Msec(1000);
			servoTarget[autoServo] = 255;
			wait1Msec(500);


			while(nMotorEncoder[RightDrive] < WAUTO_12_score_disT*TICKS_PER_REVOLUTION)
				{
					moveForward((-1*direction)*DEFAULT_AUTO_SPEED);
				}

			halt();
			wait1Msec(50);

			tareHeading();
			count = 0;
			//moveForward(DEFAULT_AUTO_SPEED * direction);
			turnDegrees(-1*TURN_TO_RAMP_WL, DEFAULT_AUTO_SPEED);
			halt();
			wait1Msec(10);
			resetEncoders();

			drivedistance(DEFAULT_AUTO_SPEED, 2.8, (-1*direction));
			halt();
			wait1Msec(10);

			tareHeading();
			turnDegrees(65, DEFAULT_AUTO_SPEED);
			halt();
			wait1Msec(10);
			resetEncoders();



			halt();
			resetEncoders();
			wait1Msec(100);

			drivedistance(RAMP_SPEED, 4.2, direction);
			halt();
	}

}
