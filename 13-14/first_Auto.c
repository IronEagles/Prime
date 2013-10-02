#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     IRsensor,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     motorLeft,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorRight,    tmotorTetrix, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	nMotorEncoder[motorRight] = 0;
	nMotorEncoder[motorLeft] = 0;
	motor[motorLeft] = 20;
	motor[motorRight] = 20;
	while ( SensorValue[IRsensor] != 6)
	{
		wait1Msec(10);
		nxtDisplayCenteredTextLine(3, "Sensor Value: %d", SensorValue[IRsensor]);

	}

		motor[motorLeft] = 0;
		motor[motorRight] = 0;
		PlayTone(736, 50);
		wait1Msec(1000);

		//Now go for x amount of encoder counts//

		motor[motorLeft] = 20;
		motor[motorRight] = 20;
		while ( nMotorEncoder[motorLeft] < (360 * 4 * 9.5))
		{
			wait10Msec(1);
		}

		motor[motorLeft] = 0;
		motor[motorRight] = 0;
		PlayTone(736, 50);
		wait1Msec(1000);

}
