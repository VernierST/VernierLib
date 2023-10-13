/*
Turn on lines 1, 2, and 3 of the Digitial Control Unit (DCU)
when a LabQuest sensor reading goes above a threshold value.

 - Connect the Vernier Arduino Interface Shield to a RedBoard, UNO R3 or R4.
 - Connect a Vernier LabQuest sensor to ANALOG 1
 - Connect a Vernier DCU to DIGITAL 2
 - Modify the threshold value, if needed
 - Upload the code
 - When the sensor reading goes above the threshold value the DCU
    lines should turn on

*/

#include "VernierLib.h" 
VernierLib Vernier;
byte DCUSetting;
float threshold = 5.0;   //Modify this value as needed


// Prepare the Serial Monitor and Identify the LabQuest sensor
void setup()
{
  Serial.begin(9600);
  while (!Serial);
  delay(4000);    //Need time for the Serial Monitor to become available
  Vernier.autoID();    // automatically identify the LabQuest sensor
}

// Compare the sensor reading to the threshold to determine if the
// DCU lines are turned on or off.
void loop()
{
  float sensorReading = Vernier.readSensor();
  Serial.print(sensorReading);
  Serial.print(" ");
  Serial.println(Vernier.sensorUnits());
  if (sensorReading > threshold)
  {
    DCUSetting = 7;   // Sending a 7 turns lines 1, 2, and 3 on
  }
  else 
  {
    DCUSetting = 0;   // Sending a 0 turns all DCU lines off
  }
  Vernier.DCU(DCUSetting);
  delay(500);                            
}
