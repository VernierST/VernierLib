/* VernierLibDemoAnalogThreshold (v2017)
 * This sketch reads a data point from a Vernier Analog (BTA) 
 * sensor and turns on an LED (pin D13) if the sensor reading
 * exceeds a threshold value.
 * 
 * Plug the sensor into the Analog 1 port on the Vernier Arduino 
 * Interface Shield or into an Analog Protoboard Adapter wired 
 * to Arduino pin A0.
 */

#include "VernierLib.h" //include Vernier functions in this sketch
VernierLib Vernier; //create an instance of the VernierLib library

float sensorReading; //create global variable to store sensor reading
float threshold=5; //set threshold value for sensor
 
void setup() {
  Vernier.autoID(); //identify sensor being used
  pinMode(13,OUTPUT); //setup digital line 13 for output
}

void loop() {
  sensorReading = Vernier.readSensor(); //read one data value
  if (sensorReading > threshold) //check if threshold exceeded
  {
    digitalWrite(13,HIGH); //turn LED on
  }
  else
  {
    digitalWrite(13,LOW); //turn LED off
  }
  delay(500); //wait half second
}
