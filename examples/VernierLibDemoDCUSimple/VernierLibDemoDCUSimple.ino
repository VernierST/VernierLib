/*
This sketch cycles through each of the possible states for
the Vernier Digital Control Unit (DCU) lines 1, 2, and 3. 
LEDs on the DCU indicate the on/off status of each digital line.

There are 16 possible output states of the DCU. The first 7 states
are for controlling DCU lines 1, 2, and 3. 

 - Connect the Vernier Arduino Interface Shield to a RedBoard, UNO R3 or R4.
 - Connect a Vernier DCU to DIGITAL 2
 - Upload the code
 - Watch the DCU LEDs for lines 1, 2, and 3 
 
*/

#include "VernierLib.h" 
VernierLib Vernier;

// Prepare the Serial Monitor
void setup()
{
  Serial.begin(9600);
  while (!Serial);
  delay(4000);    //Need time for the Serial Monitor to become available
}

// Cycle through output states 0 - 7
void loop()
{
   for (int DCUSetting=0; DCUSetting <= 7; DCUSetting++)
   {
      Serial.println(DCUSetting);
      Vernier.DCU(DCUSetting);
      delay(1000);
   } 
}