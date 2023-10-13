/* VernierLibTutorialDCUThreshold (v2017)
 * This sketch turns on a DC electrical device connected to DCU
 * line D1 when a Vernier Analog (BTA) sensor exceeds a
 * threshold value.
 * 
 * Plug the DCU into the Digital 2 port on the Vernier Arduino 
 * Interface Shield or into a Digital Protoboard Adapter wired 
 * to Arduino pins 6, 7, 8, and 9. Plug the sensor into the 
 * Analog 1 port on the Vernier Arduino Interface Shield or 
 * into an Analog Protoboard Adapter wired to Arduino pin A0.
 */

#include "VernierLib.h" //include Vernier functions in this sketch
VernierLib Vernier; //create an instance of the VernierLib library

float sensorReading; //create global variable to store sensor reading
float threshold = 5.0; //set threshold value for a Dual-Range Force Sensor
 
void setup() {
  Vernier.autoID(); //identify the sensor
}

void loop() {
  sensorReading = Vernier.readSensor(); //get one data point
  if(sensorReading > threshold) //check if threshold exceeded
  {
    Vernier.DCU(1); //turn on DCU line D1
  }
  else
  {
    Vernier.DCU(0); //turn off all DCU lines
  }
  delay(500); //wait half second
}

