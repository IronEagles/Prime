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

#include "configuration_test.h"
#define LEFT_DRIVE LeftDrive
#define RIGHT_DRIVE RightDrive

void turnLeft(float rate ,int speed = 100){
	if (speed > 100)
		speed = 100;

	if (rate > 1)
		rate = 1;

	motor[LEFT_DRIVE] = speed - speed*rate;
	motor[RIGHT_DRIVE] = speed;
}

void turnRight(float rate,int speed = 100){
	if (speed > 100)
		speed = 100;

	if (rate > 1)
		rate = 1;

	motor[LEFT_DRIVE] = speed;
	motor[RIGHT_DRIVE] = speed - speed*rate;
}

void moveForward(int speed = 100)
{
	motor[LEFT_DRIVE] = speed;
	motor[RIGHT_DRIVE] = speed;
}

void halt(){
	motor[RIGHT_DRIVE] = 0;
	motor[LEFT_DRIVE] = 0;
}

void resetEncoders(){
	nMotorEncoder[RIGHT_DRIVE] = 0;
	nMotorEncoder[LEFT_DRIVE] = 0;
}

void turnDegrees(int degrees, int speed){
	//int destination_heading = abs((currHeading + 360 + degrees) % 360);
  int count = 0;
	currHeading = 0.0;
  int direction;
	int low_degrees;
  int high_degrees;
  count ++;

	if (degrees<0){
		direction = 1;
	  high_degrees = 360+degrees;
		low_degrees = high_degrees - 20;
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
		count ++;
		if (currHeading >= low_degrees && currHeading < high_degrees) break;

		if (count > 800)
		{
			halt();
			wait1Msec(30000);

		} //Basic timer check.  Threshold changes based on distance turning and speed.  180 degrees * 70 speed / 5 = 2520ms.
	}
	halt();
	currHeading = 0.0;
	resetEncoders();


	// TODO: use destination heading to turn in the correct direction
	// TODO: negative degrees are CCW turns
	// TODO: positive degrees are CW turns
}

void drivedistance(int speed, float distance, int direction)
{
	resetEncoders();
	ClearTimer(T1);
	distance = distance * TICKS_PER_REVOLUTION;
	int count = 0;

	int rightEncoder = nMotorEncoder[RIGHT_DRIVE];
	int leftEncoder = nMotorEncoder[LEFT_DRIVE];
	moveForward(speed * direction);
	while(abs(nMotorEncoder[RIGHT_DRIVE]) < abs(direction * distance) && abs(nMotorEncoder[LEFT_DRIVE]) < abs(direction * distance))
	{
		/*if (time1[T1] > abs(distance*500/speed))
		{
			PlayTone(500,50);
			wait1Msec(50);
		//	break;
		}*/
		if (count >= 500)
		{
			if (abs(nMotorEncoder[RIGHT_DRIVE]) < abs(rightEncoder) + ENCODER_CHECK || abs(nMotorEncoder[LEFT_DRIVE]) < abs(leftEncoder) + ENCODER_CHECK)
			{
				halt();
				PlayTone(500,500);
				wait1Msec(30000);
			}
			rightEncoder = nMotorEncoder[RIGHT_DRIVE];
			leftEncoder = nMotorEncoder[LEFT_DRIVE];
			count = 0;
		}
		count++;
		wait1Msec(5);
	}
	halt();
	currHeading = 0.0;
	wait1Msec(100);
}

void runMotorForTime(tMotor runmotor, int speed, int time=1000){
	ClearTimer(T1);
	motor[runmotor] = speed;
	wait1Msec(time);

	motor[runmotor] = 0;

}

void tareHeading(){
	currHeading = 0;
	wait1Msec(100);
}

//MUX test code
bool MUXtest()
{
 byte status = 0;
// SetSensorType(S3, sensorLowSpeed);
 wait1Msec (100);

 status = HTSMUXreadStatus(HTSMUX);

 if(status & HTSMUX_STAT_BATT == HTSMUX_STAT_BATT)
  {
	  return false;
  }
	else
	{
		return true;
	}


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


// IR Wait Helpers
