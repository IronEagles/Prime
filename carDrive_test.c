#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     test,          tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	int power = 100;
	while(1==1)
	{
		if(nNxtButtonPressed == 3)
		{
			power = -1*power;
		}
		motor[test]= power;
		// if the current pressed button is 1 (the Right Arrow):

	}

}