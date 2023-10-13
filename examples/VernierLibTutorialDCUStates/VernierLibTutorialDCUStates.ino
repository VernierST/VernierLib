/* VernierLibDemoDCUStates (v2017)
 * This sketch cycles through each of the 16 possible states 
 * for the Vernier DCU once each second. LEDs on the DCU
 * indicate the on/off status of each digital line.
 * 
 * Plug the DCU into the Digital 2 port on the Vernier Arduino 
 * Interface Shield or into a Digital Protoboard Adapter wired 
 * to Arduino pins 6, 7, 8, and 9.
 */

#include "VernierLib.h" //include Vernier functions in this sketch
VernierLib Vernier; //create an instance of the VernierLib library

int DCUSetting; //create global variable for DCU state (0-15)
 
void setup() {
}

void loop() {
  for (DCUSetting=0; DCUSetting <= 15; DCUSetting++) //cycle through all 16 DCU states
  {
    Vernier.DCU(DCUSetting); //turn on DCU lines for each state
    delay(1000); //wait one second
  }
}

