
int speed_divisor

task main()
{
	  while (true)
  {
  	getJoystickSettings(joystick);

		//This is the driving code.  Two stick steering
  	//The old speed divisor variable should set us to full speed

  	if (joy1Btn(?)== 1)
  	{
  		speed_divisor = 200;
  	}
 		else
  	{
  			speed_divisor = 300;
  	}
  		if (abs(joystick.joy1_y1) < 10 & abs(joystick.joy1_x2) < 10)
  	{
     	motor[LeftDrive] = 0;
   		motor[RightDrive] = 0;
   	}
   	else
   	{
     	motor[LeftDrive] = (- joystick.joy1_y1 + joystick.joy1_x2) * 100 / speed_divisor;
     	motor[RightDrive] = (- joystick.joy1_y1 - joystick.joy1_x2) * 100 / speed_divisor;
    }

}
