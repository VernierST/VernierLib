/* VernierTutorialPhotogate (v2018)
 * This sketch will send a status message to the Serial 
 * Monitor on whether the Photogate is blocked or unblocked.
 * It lists the time that the photogate is blocked in microseconds since the program started running or
 * since the last time the counter overflowed.
 * It will also turn on the LED (pin D13) when the 
 * photogate is blocked.
 * 
 * Plug the Photogate into the Digital 1 port on the 
 * Vernier Arduino Interface Shield or into a Digital Protoboard 
 * Adapter wired to Arduino pins 2, 3, 4, and 5.
 */

int photogatePin = 2; //create global variable for pin assignment to sensor
int LEDpin = 13; //create global variable for pin assignment to LED
int photogateStatus; //create global variable for photogate status: LOW=blocked, HIGH=unblocked
int oldStatus = HIGH;
unsigned long timeus = 0; //Time in us

void setup() 
  {
   Serial.begin(9600);           // set up Serial library at 9600 bps
    pinMode(LEDpin, OUTPUT);
    Serial.println("Vernier Format 2");
    Serial.println("Photogate blocked times taken using Ardunio");
    Serial.print("Time");
    Serial.print("us");
  };// end of setup

void loop ()
{
  photogateStatus = digitalRead(photogatePin);//low when blocked
   if (photogateStatus == LOW)
   { 
    digitalWrite(LEDpin, HIGH);// turn on LED
        if (oldStatus == HIGH)
          {
          timeus = micros();
          Serial.println(timeus);
           }
   }
   else digitalWrite(LEDpin, LOW);// turn off LED
   oldStatus = photogateStatus;
 } ;// end of loop



