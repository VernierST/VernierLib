/* VernierTutorialRadiation (v2017)
 * This sketch monitors a Vernier Radiation Sensor and 
 * counts the number of radiation events that occur every
 * second.
 * 
 * Plug the Radiation Sensor into the Digital 1 port on the 
 * Vernier Arduino Interface Shield or into a Digital Protoboard 
 * Adapter wired to Arduino pins 2, 3, 4, and 5.
 */

int sensorPin = 2; //create global variable for pin assignment to sensor
unsigned long timeStart; //create global variable for start time

void setup() {
  Serial.begin(9600);
  while (!Serial);
  delay(4000);   //Need time for the Serial Monitor to become available
}

void loop ()
{
  int radCount = 0; //initialize local variable for number of radiation events
  
  timeStart = millis(); //set start time to current time
  while ((millis()-timeStart) <= 1000) //do while current time minus start time is less than 1 second
  {
    if (digitalRead(sensorPin)==HIGH) //check if radiation event detected
    { 
      radCount ++; //increment number of radiation events
     }
  }
Serial.println(radCount); //print total number of radiation events
} 

