/*
 Measure the position of an object from the Vernier Motion
 Detector and display the results to the Serial Monitor.

 - Connect the Vernier Arduino Interface Shield to a RedBoard, UNO R3 or R4.
 - Connect a Vernier Motion Detector to DIGITAL 1
 - Place the object in the Motion Detector's working field of vision
 - Upload the code and view the output in the Serial Monitor
 
*/

#include "VernierLib.h" 
VernierLib Vernier;
float distance;   // distance in cm 


// Prepare the Serial Monitor
void setup()
{
  Serial.begin(9600);
  while (!Serial);
  delay(4000);    //Need time for the Serial Monitor to become available
  Serial.print("Motion Detector reading...");
}

// Take position readings (distance from detector in centimeters)
void loop()
{
  distance = Vernier.readMotionDetector();   //read one data value
  Serial.print(distance);
  Serial.println(" cm");
  delay(100);   //delay a tenth of a second
}