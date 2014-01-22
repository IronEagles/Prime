#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  HTMotor)
#pragma config(Hubs,  S2, HTMotor,  none,     none,     none)
#pragma config(Sensor, S3,     GYRO,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S4,     irsensor,       sensorHiTechnicIRSeeker1200)
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

// MACROS
#define BLUETAPE 35
#define SPEED -40

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

void halt(){
	motor[RightDrive] = 0;
	motor[LeftDrive] = 0;
}

void resetEncoders(){
	nMotorEncoder[RightDrive] = 0;
	nMotorEncoder[LeftDrive] = 0;
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
    	//delTime /= 1000;
	}
}

// ==================================================================================================

void initializeRobot()
{
  // Place code here to sinitialize servos to starting positions.
  // Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.
	//servoTarget[Wrist] = 255;

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
  waitForStart(); // Wait for the beginning of autonomous phase.



	// STEP 1: Drive straight until irsensor
	resetEncoders();
  while(SensorValue[irsensor] > 6 || SensorValue[irsensor] ==0){
			nxtDisplayCenteredTextLine(3, "IR: %d", SensorValue[irsensor]);
			moveForward(SPEED);
			wait1Msec(5);
	}
	halt();
	wait1Msec(500);

	// STEP 2: Deploy auto-scoring arm
	servoTarget[autoServo] = 200;
	wait1Msec(500);
	servoTarget[autoServo] = 255;
	wait1Msec(500);


	// STEP 3: long drive along wall with IR score
	while(nMotorEncoder[RightDrive] > -(4*360*4))
	{
		moveForward(SPEED);
	}
	halt();
	currHeading = 0.0;
	wait1Msec(500);


	//STEP 4: Turn 90 degrees first
	motor[LeftDrive] = 70;
	motor[RightDrive] = -70;
	while(true)
	{
		nxtDisplayCenteredTextLine(3, "Heading: %d", currHeading);
		wait1Msec(10);
		if (currHeading >= 60.0 && currHeading < 80.0) break;
	}
	halt();
	resetEncoders();
	wait1Msec(100);

	//STEP 5: Drive 2 feet before ramp turn
	while(nMotorEncoder[RightDrive] > -(4*360*2))
		moveForward(SPEED);
	halt();
	currHeading = 0.0;
	wait1Msec(100);


	//STEP 6: Second 90 degree turn
	motor[LeftDrive] = 70;
	motor[RightDrive] = -70;
	while(true)
	{
		nxtDisplayCenteredTextLine(3, "Heading: %d", currHeading);
		wait1Msec(10);
		if (currHeading >= 120.0 && currHeading < 140.0) break;
	}
	halt();
	resetEncoders();
	wait1Msec(100);


	//STEP 7: Drive onto ramp
	while(nMotorEncoder[RightDrive] >0-(4*360*4))
	{
		moveForward(-70);
	}
	halt();
	currHeading = 0.0;
	wait1Msec(100);
}