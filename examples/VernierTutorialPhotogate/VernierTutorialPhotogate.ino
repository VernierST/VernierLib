/* VernierTutorialPhotogate (v2017)
 * This sketch will send a status message to the Serial 
 * Monitor on whether the Photogate is blocked or unblocked.
 * It will also turn on the LED (pin D13) when the 
 * photogate is blocked.
 * 
 * Plug the Photogate into the Digital 1 port on the 
 * Vernier Arduino Interface Shield or into a Digital Protoboard 
 * Adapter wired to Arduino pins 2, 3, 4, and 5.
 */

int sensorPin = 2; //create global variable for pin assignment to sensor
int LEDpin = 13; //create global variable for pin assignment to LED
int photogateStatus; //create global variable for photogate status: LOW=blocked, HIGH=unblocked

void setup() {
  Serial.begin(9600); //setup communication to display
  pinMode(LEDpin, OUTPUT); //setup LED indicator
}
  
void loop() {
  photogateStatus = digitalRead(sensorPin); //get status of photogate
  if (photogateStatus == LOW) //check if photogate blocked
   { 
    digitalWrite(LEDpin, HIGH); //turn on LED 
    Serial.println("blocked"); //print status message
   }
   else 
   {
    digitalWrite(LEDpin, LOW); //turn off LED 
    Serial.println("unblocked"); //print status message   
   }
 }

