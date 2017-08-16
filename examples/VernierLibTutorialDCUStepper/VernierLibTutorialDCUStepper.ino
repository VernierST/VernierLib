/* VernierLibTutorialDCUStepper (v2017)
 * This sketch will make a stepper motor rotate one complete
 * rotation clockwise, stop for half a second, and then rotate
 * one complete rotation counterclockwise.
 * 
 * Connect the stepper motor to DCU line D1, D2, D3, and D4.
 * Plug the DCU into the Digital 2 port on the Vernier Arduino
 * Interface Shield or into a Digital Protoboard Adapter wired
 * to Arduino pins 6, 7, 8, and 9.
 */

#include "VernierLib.h" //include Vernier functions in this sketch
VernierLib Vernier; //create an instance of the VernierLib library

int stepCount=48; //create global variable for number of steps; modify if not making one complete rotation
int stepDirection=0;//create global variable for direction 0 = CW, 1 = CCW
int stepDelay=30; //create global variable for step time in ms; modify to change the speed of rotation

void setup() {
}

void loop() {
  Vernier.DCUStep(stepCount,stepDirection, stepDelay); //rotate the motor
  Vernier.DCU(0); //turn off all DCU lines
  delay(500); //wait half second
  stepDirection ++; //increment the step direction
  if (stepDirection > 1) stepDirection=0; //if finished CCW, reset to CW
}

