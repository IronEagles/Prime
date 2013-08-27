#pragma config(Hubs,  S1, HTServo,  none,     none,     none)
#pragma config(Hubs,  S2, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S3,     HTSMUX,              sensorI2CCustom)
#pragma config(Motor,  mtr_S2_C1_1,     ArmMotor,      tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S2_C1_2,     empty,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_1,     LeftDrive,     tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S2_C2_2,     RightDrive,    tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S2_C3_1,     Scissor,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S2_C3_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C1_1,    Wrist,                tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    RightWrist,           tServoStandard)


#include "drivers/hitechnic-sensormux.h"
#include "drivers/hitechnic-irseeker-v2.h"
#include "drivers/lego-touch.h"

const tMUXSensor irsensor1 = msensor_S3_3;
const tMUXSensor irsensor2 = msensor_S3_4;
const tMUXSensor upTouch = msensor_S3_1;
const tMUXSensor downTouch = msensor_S3_2;

task main()
{
while(true)	{
	if(TSreadState(downTouch) == false && TSreadState(upTouch) == false) {

		if(nNxtButtonPressed == 1)
		{
			motor[Scissor] = 100;
		}

		if(nNxtButtonPressed == 2)
		{
			motor[Scissor] = -100;
		}
		if(nNxtButtonPressed == -1)
		{
		motor[Scissor] =0;
		}
	}

	if(TSreadState(downTouch) == true  && TSreadState(upTouch) == false) {
		if(nNxtButtonPressed == 1)
		{
			motor[Scissor] = 100;
		}

		if(nNxtButtonPressed == 2)
		{
			motor[Scissor] = 0;
		}
		if(nNxtButtonPressed == -1)
		{
		motor[Scissor] =0;
		}
	}

	if(TSreadState(downTouch) == false  && TSreadState(upTouch) == true) {
		if(nNxtButtonPressed == 1)
		{
			motor[Scissor] = 0;
		}

		if(nNxtButtonPressed == 2)
		{
			motor[Scissor] = -100;
		}
		if(nNxtButtonPressed == -1)
		{
		motor[Scissor] =0;
		}
	}

	if(nNxtButtonPressed == 3)
	{
		while(TSreadState(downTouch) == false && nNxtButtonPressed != 1 && nNxtButtonPressed != 2 )
		{
			motor[Scissor] = -100;
		}
			motor[Scissor] = 0;
	}


}


}
