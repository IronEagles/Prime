#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  HTMotor)
#pragma config(Hubs,  S2, HTMotor,  none,     none,     none)
#pragma config(Sensor, S3,     touch,          sensorTouch)
#pragma config(Motor,  mtr_S1_C1_1,     LeftDrive,     tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     RightDrive,    tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     scoreWrist,    tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     carWash,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     liftArm,       tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     scoreArm,      tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S2_C1_1,     pullUp,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C1_2,     flagSpinner,   tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C3_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
Controls list
Joy 1 sticks = driving

*/

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

void initializeRobot()
{
  // Place code here to sinitialize servos to starting positions.
  // Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.


  return;
}


task main()
{
	initializeRobot();
	getJoystickSettings(joystick);
	waitForStart();   // wait for start of tele-op phase

	int armStop = 0;
	int speed_divisor_c1 = 0;
	int speed_divisor_c2 = 0;
	int threshold = 10;

while(true)
{
//turbo code
	if (joy1Btn(7)== 1){
  	speed_divisor_c1 = 100;
	}else{
  	speed_divisor_c1 = 200;
  }
//drive code
  if (abs(joystick.joy1_y1) < 10 & abs(joystick.joy1_x2) < 10) {
      motor[LeftDrive] = 0;
     motor[RightDrive] = 0;

  } else {
       motor[LeftDrive] = (- joystick.joy1_x2 - joystick.joy1_y1) * 100 / speed_divisor_c1;
       motor[RightDrive] = (- joystick.joy1_x2 + joystick.joy1_y1) * 100 / speed_divisor_c1;
  }
//up down lift arm code
		if(joy2Btn(4) == 1)
			{
				motor[liftArm] = -40; //up
			}
		else if (joy2Btn(2) == 1)
			{
				motor[liftArm] = 40; //down
			}
		else
			{
				motor[liftArm] = 0;
			}

//pull up motor code
		if (joy2Btn(3)==1)
			{
				motor[pullUp] = 100;
			}
		else if (joy2Btn(1)==1)
			{
				motor[pullUp] = -100;
			}
		else
			{
				motor[pullUp] = 0;
			}

//second controller code
//joystick code

			speed_divisor_c2 = 200;

	if (abs(joystick.joy2_y2) < 10) {
      motor[scoreWrist] = 0;

  } else {

    motor[scoreWrist] = ( joystick.joy2_y2) * 100 / speed_divisor_c2;
  }

  if (abs(joystick.joy2_y1) < 10 || SensorValue[touch] == 1)
 		{
  		motor[scoreArm] = 0;
  	}
  else
  {
  	motor[scoreArm] = (( -joystick.joy2_y1) * 100) / speed_divisor_c2;
  }

//flag spinner code
  if (joy1Btn(4)==1)
			{
				motor[flagSpinner] = 100;
			}
		else if (joy1Btn(2)==1)
			{
				motor[flagSpinner] = -100;
			}
		else
			{
				motor[flagSpinner] = 0;
			}
//car wash code
	if (joy1Btn(5)==1)
			{
				motor[carWash] = 100;
			}
		else if (joy1Btn(6)==1)
			{
				motor[carWash] = -70;
			}
		else
			{
				motor[carWash] = 0;
			}


wait1Msec(5);
}//while loop brace



}//task main
