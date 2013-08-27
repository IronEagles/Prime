#pragma config(Hubs,  S1, HTServo,  none,     none,     none)
#pragma config(Hubs,  S2, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Motor,  mtr_S2_C1_1,     ArmMotor,      tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S2_C1_2,     empty,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_1,     LeftDrive,     tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S2_C2_2,     RightDrive,    tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S2_C3_1,     Scissor,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C3_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C1_1,    Wrist,                tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    Forearm,              tServoStandard)
#pragma config(Servo,  srvo_S1_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)





task main()
{
while(true)	{
	if(nNxtButtonPressed == 1)
	{
		motor[ArmMotor] = 30;
	}

	if(nNxtButtonPressed == 2)
	{
		motor[ArmMotor] = -30;
	}
	if(nNxtButtonPressed == -1)
	{
	motor[ArmMotor] =0;
	}
}


}
