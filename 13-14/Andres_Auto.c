#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S3,     ultrasonic,     sensorSONAR)
#pragma config(Sensor, S4,     sensorLightActive, sensorLightActive)
#pragma config(Motor,  mtr_S1_C1_1,     motorLeft,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorRight,    tmotorTetrix, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int speed = 20;

task main()
{

int distance = 0;
bool done = false;

	while(!done)
	{
		distance = SensorValue[ultrasonic];


		if(distance < 30)
		{
			nxtDisplayCenteredTextLine(3, "TURN RIGHT");
			motor[motorLeft] = 20;
			motor[motorRight] = 15;
		}
		else if(distance >=150 )
		{
				nxtDisplayCenteredTextLine(3, "FINISH");
				motor[motorLeft] = 7;
				motor[motorRight] = speed;
				while(true)
					{
						nxtDisplayCenteredTextLine(3, "Sensor Value: %d", SensorValue[sensorLightActive]);
						if (SensorValue[sensorLightActive] > 30)
							{
								motor[motorLeft] = .2 * speed;
								motor[motorRight] = 1 * speed;
								wait1Msec(1);
								}
								else
									{
										motor[motorLeft] = 1 * speed;
										motor[motorRight] = .2 * speed;
										}
										}

		}
		else if(distance >= 30)
		{
			nxtDisplayCenteredTextLine(3, "TURN LEFT");
			motor[motorLeft] = 15;
			motor[motorRight] = 20;
		}
		wait1Msec(250);
	}

}
