/*
 * Motors.cpp
 *
 *  Created on: 25.09.2017
 *      Author: anonymous
 */

#include <Arduino.h>
#include "defines.h"
#include "globals.h"
#include "Wire.h"

// Set speed of Stepper Motor1
// tspeed could be positive or negative (reverse)
void setMotorSpeed(int16_t tspeed_M1, int16_t tspeed_M2)
{
  long timer_period;
  byte myArray[4];

  // Limit max speed?

  // WE LIMIT MAX ACCELERATION of the motors
  if ((speed_M1 - tspeed_M1) > MAX_ACCEL)
    speed_M1 -= MAX_ACCEL;
  else if ((speed_M1 - tspeed_M1) < -MAX_ACCEL)
    speed_M1 += MAX_ACCEL;
  else
    speed_M1 = tspeed_M1;

  // Limit max speed?

  // WE LIMIT MAX ACCELERATION of the motors
  if ((speed_M2 - tspeed_M2) > MAX_ACCEL)
    speed_M2 -= MAX_ACCEL;
  else if ((speed_M2 - tspeed_M2) < -MAX_ACCEL)
    speed_M2 += MAX_ACCEL;
  else
    speed_M2 = tspeed_M2;

  // Sending speeds to Hoverboard over i2c
  // -------------------------------------
  myArray[0] = (speed_M1 >> 8) & 0xFF;
  myArray[1] = speed_M1 & 0xFF;

  myArray[2] = (speed_M2 >> 8) & 0xFF;
  myArray[3] = speed_M2 & 0xFF;

  Serial.print(myArray[0], HEX);
  Serial.print("  ");
  Serial.println(myArray[1], HEX);

  Wire.beginTransmission(HOVERBOARDI2CADDR); // transmit to device #8
  Wire.write(myArray, 4);              // sends 4 bytes
  Wire.endTransmission();    // stop transmitting
}

