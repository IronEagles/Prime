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

#include "configuration.h"
#include "helpers_test.h"


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

task main()
{
	int direction = -1;
<<<<<<< HEAD
	initializeRobot();
{
=======

>>>>>>> test_program
	// Initialize encoders
  resetEncoders();

	// Spawn heading tracking thread
	StartTask(heading);
  wait1Msec(1000);

<<<<<<< HEAD
  return;
}

//Move forward
drivedistance(DEFAULT_TRAVEL_SPEED, TICKS_PER_REVOLUTION * 2, 1);
//Move Backward
drivedistance(DEFAULT_TRAVEL_SPEED, TICKS_PER_REVOLUTION * 2, direction);
//Turn Right and back to center
turnDegrees(45, 0);
//Turn Left
turnDegrees(315, 0);
=======
  drivedistance(DEFAULT_TRAVEL_SPEED, TICKS_PER_REVOLUTION * 2, 1);
	//Move Backward
	drivedistance(DEFAULT_TRAVEL_SPEED, TICKS_PER_REVOLUTION * 2, direction);
	//Turn Right and back to center
	turnDegrees(180, 70);
	//Turn Left
	turnDegrees(-180, 70);


	//Raise and lower arm

	while (true){
			if (TSreadState(topTouch) == false)
			{
				motor[scoreArm] = -100;
			}
			else if (TSreadState(topTouch) == true)
			{
				motor[scoreArm] = 0;
				break;
			}
	}

	//Lower
	while (true){
			if (TSreadState(bottomTouch) == false)
			{
				motor[scoreArm] = 100;
			}
			else if (TSreadState(bottomTouch) == true)
			{
				motor[scoreArm] = 0;
				break;
			}
	}

		// STEP 2: Deploy auto-scoring arm
	servoTarget[autoServo] = AUTO_SCORING_ARM_DEPLOY_DISTANCE;
	wait1Msec(WAIT_BEFORE_RETRACT_AUTO_SCORE_ARM_MS);
	servoTarget[autoServo] = AUTO_SCORING_ARM_HOME;
	wait1Msec(500);

	runMotorForTime(carWash, 50, 1000);
	runMotorForTime(carWash, -50, 1000);

	runMotorForTime(flagSpinner, 50, 1000);
	runMotorForTime(flagSpinner, -50, 1000);

>>>>>>> test_program

}
