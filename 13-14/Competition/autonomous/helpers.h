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

#include "configuration.h"
#define LEFT_DRIVE LeftDrive
#define RIGHT_DRIVE RightDrive

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

<<<<<<< HEAD
void turnDegrees(int degrees, int currHeading=0){
	int destination_heading = abs((currHeading + 360 + degrees) % 360);
=======
void turnDegrees(int degrees, int speed){
	//int destination_heading = abs((currHeading + 360 + degrees) % 360);
  ClearTimer(T1);

  int direction;
	int low_degrees;
  int high_degrees;

	if (degrees<0){
		direction = 1;
	  high_degrees = 360-degrees;
		low_degrees = degrees - 20;
	}else{
		direction = -1;
		low_degrees = degrees;
		high_degrees = degrees + 20;
	}

	motor[LEFT_DRIVE] = speed*direction*-1;
	motor[RIGHT_DRIVE] = speed*direction;

	while(true)
	{
		wait1Msec(10);
		if (currHeading >= low_degrees && currHeading < high_degrees) break;

		if (time1[T1] > abs(speed*degrees/5)) break; //Basic timer check.  Threshold changes based on distance turning and speed.  180 degrees * 70 speed / 5 = 2520ms.
	}
	halt();
	currHeading = 0.0;
	resetEncoders();


>>>>>>> test_program
	// TODO: use destination heading to turn in the correct direction
	// TODO: negative degrees are CCW turns
	// TODO: positive degrees are CW turns
}

void drivedistance(int speed, int distance, int direction)
{
<<<<<<< HEAD
	while(nMotorEncoder[RightDrive] > direction * distance)
	{
		moveForward(speed);
=======
	resetEncoders();
	ClearTimer(T1);

	moveForward(speed);
	while(nMotorEncoder[RIGHT_DRIVE] > direction * distance)
	{
		if (time1[T1] > abs(distance*50/speed)) break;
>>>>>>> test_program
	}
	halt();
	currHeading = 0.0;
	wait1Msec(100);
}


/* task heading()
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
*/
