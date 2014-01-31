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

void turnDegrees(int degrees, int currHeading=0){
	int destination_heading = abs((currHeading + 360 + degrees) % 360);
	// TODO: use destination heading to turn in the correct direction
	// TODO: negative degrees are CCW turns
	// TODO: positive degrees are CW turns
}

void drivedistance(int speed, int distance, int direction)
{
	while(nMotorEncoder[RightDrive] > direction * distance)
	{
		moveForward(speed);
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
