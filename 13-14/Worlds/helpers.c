
#include "configuration.h"


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

int turnDegrees(int degrees, int currHeading=0){
	int destination_heading = abs((currHeading + 360 + degrees) % 360)
	// TODO: use destination heading to turn in the correct direction
	// TODO: negative degrees are CCW turns
	// TODO: positive degrees are CW turns
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
