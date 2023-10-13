/*
This sketch will use the Vernier Digital Control Unit (DCU)
to make a stepper motor rotate one complete rotation clockwise, 
stop for half a second, and then rotate one complete rotation 
counterclockwise.

 - Connect the Vernier Arduino Interface Shield to a RedBoard, UNO R3 or R4.
 - Connect a Vernier DCU to DIGITAL 2
 - Connect the stepper motor to DCU line D1, D2, D3, and D4.
 - Upload the code
 - If you do not have a stepper motor connected, watch the DCU 
      LEDs for lines 1, 2, 3, and 4 
 
*/

#include "VernierLib.h" 
VernierLib Vernier;
int stepDelay = 30;  //step time in ms. Controls the speed of rotation
int stepCount = 48;   //number of steps. Assumes 48 steps for one complete rotation
int stepDirection = 0;   //direction 0 = CW, 1 = CCW

void setup() {
}

void loop()
{
  Vernier.DCUStep(stepCount, stepDirection, stepDelay);
  Vernier.DCU(0);   // turn off all lines
  delay(500);   //delay a half second
  stepDirection ++;   //increment the step direction
  if (stepDirection > 1) 
  {
    stepDirection = 0;   //if finished CCW, reset to CW
  }
}