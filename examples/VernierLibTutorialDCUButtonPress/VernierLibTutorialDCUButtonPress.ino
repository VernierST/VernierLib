/* VernierLibTutorialDCUButtonPress (v2017)
 * This sketch turns on a DC electrical device connected to DCU 
 * line D1 when the general purpose button on the Vernier 
 * Arduino Interface Shield is pressed.
 * 
 * Plug the DCU into the Digital 2 port on the Vernier Arduino 
 * Interface Shield.
 */

#include "VernierLib.h" //include Vernier functions in this sketch
VernierLib Vernier; //create an instance of the VernierLib library

int button; //create a global variable for button state (LOW=button pressed, HIGH=button not pressed)
 
void setup() {
  pinMode(12,INPUT_PULLUP); //setup digital line 12 for button state
}

void loop() {
  button = digitalRead(12); //get button state
  if(button = LOW) //check if button pressed down
  {
    Vernier.DCU(1); //turn on DCU line D1
  }
  else //check if button not pressed
  {
    Vernier.DCU(0); //turn off all DCU lines
  }
  delay(500); //wait half second
}

