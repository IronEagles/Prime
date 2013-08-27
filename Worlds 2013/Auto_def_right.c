#pragma config(Hubs,  S1, HTServo,  none,     none,     none)
#pragma config(Hubs,  S2, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S3,     scissorTouch,   sensorTouch)
#pragma config(Motor,  mtr_S2_C1_1,     ArmMotor,      tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S2_C1_2,     empty,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S2_C2_1,     LeftDrive,     tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S2_C2_2,     RightDrive,    tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S2_C3_1,     Scissor,       tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S2_C3_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C1_1,    Wrist,                tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Autonomous Mode Code Template
//
// This file contains a template for simplified creation of an autonomous program for an Tetrix robot
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of autonomous mode, you may want to perform some initialization on your robot.
// Things that might be performed during initialization include:
//   1. Move motors and servos to a preset position.
//   2. Some sensor types take a short while to reach stable values during which time it is best that
//      robot is not moving. For example, gyro sensor needs a few seconds to obtain the background
//      "bias" value.
//
// In many cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeRobot()
{
  // Place code here to sinitialize servos to starting positions.
  // Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.
	//servoTarget[Wrist] = 255;

  return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the autonomous robot operation. Customize as appropriate for
// your specific robot.
//
// The types of things you might do during the autonomous phase (for the 2008-9 FTC competition)
// are:
//
//   1. Have the robot follow a line on the game field until it reaches one of the puck storage
//      areas.
//   2. Load pucks into the robot from the storage bin.
//   3. Stop the robot and wait for autonomous phase to end.
//
// This simple template does nothing except play a periodic tone every few seconds.
//
// At the end of the autonomous period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

task main()
{
	int count = 0;


  initializeRobot();

  waitForStart(); // Wait for the beginning of autonomous phase.

  eraseDisplay();
  	nMotorEncoder[LeftDrive] = 0 ;
  	nMotorEncoder[RightDrive] = 0 ;
  	nMotorEncoder[ArmMotor] = 0 ;
  	wait1Msec(100);

  	motor[RightDrive] = 74;
  	motor[LeftDrive] = 90;
  	while(nMotorEncoder[RightDrive] < (1440*4.25))
  	{
  		eraseDisplay();
      nxtDisplayTextLine(1, "%d", nMotorEncoder[ArmMotor]);



   		if(count++ > 2000){break;}

   		wait10Msec(1);
  	}



  	count=0;

	nMotorEncoder[RightDrive] = 0;
    	nMotorEncoder[LeftDrive] = 0;

    	wait1Msec(250);

    	motor[RightDrive] = -20;
    	motor[LeftDrive] = 55;
    	while (nMotorEncoder[LeftDrive] < (1440*2.2))
    {
    		 eraseDisplay();
      nxtDisplayTextLine(1, "%d", nMotorEncoder[RightDrive]);



   		if(count++ > 2000){break;}

   		wait1Msec(1);


   		}
   		nMotorEncoder[RightDrive] = 0;
   		nMotorEncoder[LeftDrive] = 0;
   		wait1Msec(100);

   		count = 0;
  	motor[RightDrive] = 30;
  	motor[LeftDrive] = 32;
  	while (nMotorEncoder[RightDrive] <(1440*2))
  	{
  		eraseDisplay();
      nxtDisplayTextLine(1, "%d", nMotorEncoder[RightDrive]);



   		if(count++ > 3000){break;}

   		wait1Msec(1);

  	}


  	//int direction =1;

  	//while (true)
  	//{
			//count = 0;
  	//	nMotorEncoder[RightDrive] = 0;
  	//	nMotorEncoder[LeftDrive] = 0;

  	//	wait1Msec(100);

  	//	motor[RightDrive] = 50*direction;
  	//	motor[LeftDrive] = 55*direction;
  	//	while(abs (nMotorEncoder[LeftDrive])< (1440*2))
  	//	{
  	//			eraseDisplay();
   //   nxtDisplayTextLine(1, "%d", nMotorEncoder[ArmMotor]);

   //		if(count++ > 2000){break;}
			//	wait1Msec(1);
  	//	}

   //		direction = direction*-1;


  	//}




}
