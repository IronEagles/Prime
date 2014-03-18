#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  HTMotor)
#pragma config(Hubs,  S2, HTMotor,  none,     none,     none)
#pragma config(Sensor, S4,     HTSMUX,          sensorI2CCustom)
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
#include "drivers/hitechnic-sensormux.h"
#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "drivers/hitechnic-irseeker-v2.h"
#include "drivers/lego-touch.h"

//const tMUXSensor irsensor = msensor_S3_2;
const tMUXSensor topTouch = msensor_S4_1;
const tMUXSensor bottomTouch = msensor_S4_3;
//const tMUXSensor downTouch = msensor_S3_2;

void initializeRobot()
{
  // Place code here to sinitialize servos to starting positions.
  // Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.


  return;
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


task main()
{
	initializeRobot();
	wait1Msec(2);
	getJoystickSettings(joystick);
	bool armRaising = false;
	bool armLowering = false;
	waitForStart();   // wait for start of tele-op phase

	int armStop = 0;
	int speed_divisor_c1 = 0;
	int speed_divisor_c2 = 0;
	int speed_divisor_arm = 0;
	int threshold = 10;
	string mux="";

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
			speed_divisor_arm = 100;

	if (abs(joystick.joy2_y2) < 10) {
      motor[scoreWrist] = 0;

  } else {

    motor[scoreWrist] = ( joystick.joy2_y2) * 100 / speed_divisor_c2;
  }


// scoreArm code!!!
  if (abs(joystick.joy2_y1) <= 15 && !armRaising && !armLowering && joy2Btn(6) != 1 && joy2Btn(8) != 1)
 		{
  		motor[scoreArm] = 0;
  	}
  	else if (joystick.joy2_y1 < -10 && TSreadState(bottomTouch) == false)
  	{
  		armLowering = false;
  		armRaising = false;
  		motor[scoreArm] = (( -joystick.joy2_y1) * 100) / speed_divisor_arm;
  	}
  	else if (joystick.joy2_y1 > 10 && TSreadState(topTouch) == false)
  	{
  		armRaising = false;
  		armLowering=false;
  		motor[scoreArm] = (( -joystick.joy2_y1) * 100) / speed_divisor_arm;
  	}
  	else if (joystick.joy2_y1 < -10 && TSreadState(bottomTouch) == true)
  	{
  		armLowering = false;
  		armRaising = false;
  		motor[scoreArm] = 0;
  	}
  	else if (joystick.joy2_y1 > 10 && TSreadState(topTouch) == true)
  	{
  		armRaising = false;
  		armLowering=false;
  		motor[scoreArm] = 0;
  		motor[scoreWrist] = ( joystick.joy2_y2) * 100 / speed_divisor_c2;
  	}
  	else if (joy2Btn(6) == 1 || armRaising)
		{
			armLowering=false;
			if (TSreadState(topTouch) == false)
			{
				motor[scoreArm] = -100;
				armRaising = true;
			}
			else if (TSreadState(topTouch) == true)
			{
				motor[scoreArm] = 0;
				armRaising = false;
			}
		}
		else if (joy2Btn(8) == 1 || armLowering)
		{
			armRaising=false;
			if (TSreadState(bottomTouch) == false)
			{
				motor[scoreArm] = 100;
				armLowering = true;
			}
			else if (TSreadState(bottomTouch) == true)
			{
				motor[scoreArm] = 0;
				armLowering = false;
			}
		}

		/*if ( MUXtest() ){
			mux = "ok";
		}else{
			mux = "bad";
		}*/
		//nxtDisplayTextLine(7, "Arm Power: %d, %s", motor[scoreArm], mux);



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
				motor[carWash] = -50;
			}
		else
			{
				motor[carWash] = 0;
			}


wait1Msec(5);
}//while loop brace



}//task main
