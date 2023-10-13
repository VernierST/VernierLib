/*
Read the information that is stored on a Vernier LabQuest sensor
and prints it to the Serial Monitor, and then take readings at 
2 samples/second (0.5 seconds/sample) and print the sensor 
measurements to the Serial Monitor.

 - Connect the Vernier Arduino Interface Shield to a RedBoard, UNO R3 or R4.
 - Connect a Vernier LabQuest sensor to ANALOG 1
 - Upload the code and then view the output in the Serial Monitor

*/

#include "VernierLib.h" 
VernierLib Vernier;


// Read the sensor information in the 'setup()'
void setup()
{
  Serial.begin(9600);
  while (!Serial);
  delay(4000);   //Need time for the Serial Monitor to become available

  Serial.println("begin Auto ID");
  Vernier.autoID();    // automatically identify the LabQuest sensor
  printSensorInfo();
  Serial.println();
}

// Read sensor measurments continuously in the 'loop()'
void loop()
{
  float sensorReading = Vernier.readSensor();
  Serial.print(sensorReading);
  Serial.print(" ");
  Serial.println(Vernier.sensorUnits());
  delay(500);   //half a second delay between readings
} 

// function to get the sensor's stored information
void printSensorInfo()
{
  // print out information about the sensor found:
  Serial.println("Sensor Information:"); 
  Serial.print("Sensor ID number: "); 
  Serial.print("\t");
  Serial.println(Vernier.sensorNumber());
  Serial.print("Sensor Name: ");
  Serial.print("\t");
  Serial.println(Vernier.sensorName());
  Serial.print("Short Name: "); 
  Serial.print("\t");
  Serial.println(Vernier.shortName()); 
  Serial.print("Units: "); 
  Serial.print("\t");
  Serial.println(Vernier.sensorUnits());
  Serial.print("ID voltage level: "); 
  Serial.print("\t");
  Serial.println(Vernier.voltageID());
  Serial.print("Page: ");  
  Serial.print("\t");
  Serial.println(Vernier.page());
  Serial.print("slope: ");
  Serial.print("\t");
  Serial.println(Vernier.slope());
  Serial.print("intercept: ");
  Serial.print("\t");
  Serial.println(Vernier.intercept());
  Serial.print("cFactor:");
  Serial.print("\t");
  Serial.println(Vernier.cFactor());
  Serial.print("calEquationType: ");
  Serial.print("\t");
  Serial.println(Vernier.calEquationType());
}