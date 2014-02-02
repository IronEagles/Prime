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
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// ==================================================================================================

// INCLUDES
#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "drivers/hitechnic-gyro.h"
#include "drivers/hitechnic-sensormux.h"
#include "drivers/hitechnic-irseeker-v2.h"
#include "drivers/lego-touch.h"

const tMUXSensor irsensor = msensor_S4_2;
const tMUXSensor topTouch = msensor_S4_1;
const tMUXSensor bottomTouch = msensor_S4_3;
//const tMUXSensor downTouch = msensor_S3_2;

// MACROS
#define BLUETAPE 35
#define SPEED 40

// GLOBALS
float currHeading = 0.0;

// ==================================================================================================

// HELPERS
void turnLeft(float rate ,int speed = 100){
	if (speed > 100)
		speed = 100;

	if (rate > 1)
		rate = 1;

	motor[LeftDrive] = speed - speed*rate;
	motor[RightDrive] = speed;
}

void turnRight(float rate,int speed = 100){
	if (speed > 100)
		speed = 100;

	if (rate > 1)
		rate = 1;

	motor[LeftDrive] = speed;
	motor[RightDrive] = speed - speed*rate;
}

void moveForward(int speed = 100)
{
	motor[LeftDrive] = speed;
	motor[RightDrive] = speed;
}

void moveBackward(int speed = 100)
{
	motor[LeftDrive] = -1 * speed;
	motor[RightDrive] = -1 * speed;
}

void halt(){
	motor[RightDrive] = 0;
	motor[LeftDrive] = 0;
}

void resetEncoders(){
	nMotorEncoder[RightDrive] = 0;
	nMotorEncoder[LeftDrive] = 0;
	wait1Msec(100);
}

void tareHeading(){
	currHeading = 0;
	wait1Msec(100);
}

// ==================================================================================================

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
	}
}

// ==================================================================================================

void initializeRobot()
{
  // Place code here to sinitialize servos to starting positions.
  // Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.

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
	resetEncoders();
  waitForStart(); // Wait for the beginning of autonomous phase.
  int count = 0;


	count = 0;
	while(nMotorEncoder[RightDrive] < 4*360*0.25)
	{
		moveForward(SPEED);
		wait1Msec(5);
			count++;
			if( count > 500)

				halt();
				wait1Msec(30000);
			}
	}
	// STEP 1: Drive straight until irsensor
  while(HTIRS2readACDir(irsensor) < 4 && nMotorEncoder[RightDrive] < 4*360*3.7){
			nxtDisplayCenteredTextLine(3, "IR: %d", HTIRS2readACDir(irsensor));
			moveForward(SPEED);
			wait1Msec(5);
			count++;
			if( count > 1000)
			{
				halt();
				wait1Msec(30000);
			}
	}
	moveForward(SPEED);
	//halt(); Disabled. We're going to try and deposit the block without stopping
	wait1Msec (500);
	motor[LeftDrive] = 0;
	motor[RightDrive] = 0;

	// STEP 2: Deploy auto-scoring arm
	servoTarget[autoServo] = 150;
	wait1Msec(1000);
	servoTarget[autoServo] = 255;
	wait1Msec(500);


	// STEP 3: Go backwards until encoder=0
	 while(nMotorEncoder[RightDrive] > 500){
			moveBackward(SPEED);
			wait1Msec(5);
	}
	halt();


	// STEP 4: Turn 45 degrees Left
	tareHeading();
	count = 0;
	motor[LeftDrive] = 70;
	motor[RightDrive] = -70;
	while(true)
	{
		nxtDisplayCenteredTextLine(3, "Heading: %d", currHeading);
		//wait1Msec(10);
		if (currHeading >= 45.0 && currHeading < 50.0) break;

		wait1Msec(5);
			count++;
			if( count > 650)
			{
				halt();
				wait1Msec(30000);
			}
	}
	halt();
	resetEncoders();

	//Sep 5: Move Three Feet
	count = 0;
	while(nMotorEncoder[RightDrive] > -4*360*3.0)
	{
		moveForward(-1*SPEED);
		wait1Msec(5);
			count++;
			if( count > 1000)
			{
				PlayTone(220, 150);
				halt();
				wait1Msec(30000);
			}
	}
	halt();
	wait1Msec(100);
	tareHeading();
	PlayTone(220, 150);

	//Step 6: Turn Right
	count = 0;
	motor[LeftDrive] = -70;
	motor[RightDrive] = 70;
	while(true)
	{
		nxtDisplayCenteredTextLine(3, "Heading: %d", currHeading);
		//wait1Msec(10);
		if (currHeading <= 280.0 && currHeading > 260.0) break;

		PlayTone(440, 150);
		wait1Msec(5);
			count++;
			if( count > 500)
			{

				halt();
				wait1Msec(30000);
			}
	}
	halt();
	resetEncoders();

	//Step 7: Drive onto ramp
	count = 0;
	while(nMotorEncoder[RightDrive] < 4*360*4.0)
	{
		moveForward(70);
		wait1Msec(5);
			count++;
			if( count > 1000)
			{
				halt();
				wait1Msec(30000);
			}
	}
	halt();
	tareHeading();

}
