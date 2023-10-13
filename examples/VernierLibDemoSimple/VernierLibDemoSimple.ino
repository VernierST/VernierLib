/*
Read sensor measurements from a Vernier LabQuest sensor
and print the values to the Serial Monitor.

 - Connect the Vernier Arduino Interface Shield to a RedBoard, UNO R3 or R4.
 - Connect a Vernier LabQuest sensor to ANALOG 1
 - Upload the code and then view the output in the Serial Monitor

*/

#include "VernierLib.h" 
VernierLib Vernier;


// Configure the Serial Monitor and identify the LabQuest sensor
void setup()
{
  Serial.begin(9600);
  while (!Serial);
  delay(4000);    //Need time for the Serial Monitor to become available
  Vernier.autoID();   // automatically identify the LabQuest sensor
}

// Take sensor readings at 2 samples/second (0.5 seconds/sample)
void loop()
{
  float sensorReading = Vernier.readSensor();   //read one sensor measurement
  Serial.print(sensorReading);  //print the sensor measurement
  Serial.print(" ");
  Serial.println(Vernier.sensorUnits());   //print the sensor's units
  delay(500);   //half a second delay between readings
} 