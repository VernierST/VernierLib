/* VernierLibTutorialMotionDetector (v2017)
 * This sketch reads the distance to an object and displays the
 * results to the Serial Monitor or Serial Plotter.
 * 
 * Plug the Motion Detector into the Digital 1 port on the 
 * Vernier Arduino Interface Shield or into a Digital Protoboard 
 * Adapter wired to Arduino pins 2, 3, 4, and 5.
 */

#include "VernierLib.h" //include Vernier functions in this sketch
VernierLib Vernier; //create an instance of the VernierLib library

float distance; //create global variable to store sensor reading
 
void setup() {
  Serial.begin(9600);
  while (!Serial);
  delay(4000);    //Need time for the Serial Monitor to become available
}

void loop() {
  distance = Vernier.readMotionDetector(); //read one data value
  Serial.print(distance); //display data value 
  Serial.println(" cm"); //print units
  delay(100); //wait a tenth of a second
}

