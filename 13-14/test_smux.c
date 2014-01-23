#pragma config(Sensor, S3,     HTSMUX,          sensorI2CCustom)


#include "drivers/hitechnic-sensormux.h"


task main () {
 byte status = 0;
// SetSensorType(S3, sensorLowSpeed);
 wait1Msec (100);

 while (true) {
 eraseDisplay();
 status = HTSMUXreadStatus(HTSMUX);
 nxtDisplayTextLine(1, "Status: %d", status);
 if(status & HTSMUX_STAT_BATT == HTSMUX_STAT_BATT)
 nxtDisplayTextLine (3, "No battery");
 wait1Msec (100);
 }
}
