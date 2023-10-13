/* VernierLibTutorialAnalogGraph (v2017)
 * This sketch reads a data point from a Vernier Analog (BTA) 
 * sensor once every half second and graphs the sensor data 
 * to the Serial Plotter.
 * 
 * Plug the sensor into the Analog 1 port on the Vernier Arduino 
 * Interface Shield or into an Analog Protoboard Adapter wired 
 * to Arduino pin A0. Open the Serial Plotter from the Tools
 * menu.
 */

#include "VernierLib.h" //include Vernier functions in this sketch
VernierLib Vernier; //create an instance of the VernierLib library

float sensorReading; //create global variable to store sensor reading
 
void setup() {
  Serial.begin(9600);
  while (!Serial);
  delay(4000);    //Need time for the Serial Monitor to become available
  Vernier.autoID(); //identify the sensor being used
}

void loop() {
  sensorReading = Vernier.readSensor(); //read one data value
  Serial.println(sensorReading); //graph data point 
  //Serial.println(0); //optional command to create a filled-in plot
  delay(500); //wait half second
}

