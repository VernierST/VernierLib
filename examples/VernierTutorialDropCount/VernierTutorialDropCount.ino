/* VernierTutorialDropCount (v2017)
 * This sketch counts the number of drops that fall through 
 * a Vernier Drop Counter or Photogate during a 10 second
 * time period. The number of counts that occured during the 10 s
 * period are printed to the Serial Monitor.
 * 
 * Plug the Drop Counter or Photogate into the Digital 1 port 
 * on the Vernier Arduino Interface Shield or into a Digital 
 * Protoboard Adapter wired to Arduino pins 2, 3, 4, and 5.
 */

int sensorPin = 2; //create global variable for pin assignment to sensor
unsigned long timeStart; //create global variable for start time

void setup() {
  Serial.begin(9600);
  while (!Serial);
  delay(4000);    //Need time for the Serial Monitor to become available
}

void loop () {
  int dropCount = 0; //initialize local variable for number of drops
  
  timeStart = millis(); //set start time to current time
  while ((millis()-timeStart) <= 10000) //do while current time minus start time is less than 10 seconds
  {
    if (digitalRead(sensorPin)==LOW) //check if drop is blocking sensor
    { 
      dropCount ++; //increment number of drops
      while(digitalRead(sensorPin)==LOW); //pause until drop passes through, then continue
     }
  }
Serial.println(dropCount); //print total number of drops 
}

