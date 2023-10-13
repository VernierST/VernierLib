/* VernierTutorialRotaryMotion (v2017)
 * This sketch monitors a Vernier Rotary Motion Sensor and 
 * returns angle readings every half second. The default 
 * mode is Normal resolution (1 deg angle changes), but you 
 * can switch to High resolution (0.25 deg angle changes).
 * 
 * Plug the Rotary Motion Sensor into the Digital 1 port on the 
 * Vernier Arduino Interface Shield or into a Digital Protoboard 
 * Adapter wired to Arduino pins 2, 3, 4, and 5.
 */

boolean highResOn = false; //create global variable for resolution mode (normal=false, high=true)
float angleChange; //create global variable for angle measurement 
const int encoderPinCCW = 2; //create global variable for pin assignment counterclockwise direction
const int encoderPinCW = 3; //create global variable for pin assignment clockwise direction
const int resPin = 5; //create global variable for pin assignment for resolution mode
volatile int encoderPos = 0; //create global variable for position (variables changed within interrupts are volatile)

void setup() {
  Serial.begin(9600);
  while (!Serial);
  delay(4000);   //Need time for the Serial Monitor to become available
  
  pinMode(encoderPinCCW, INPUT_PULLUP); //setup CCW pin
  pinMode(encoderPinCW, INPUT_PULLUP); //setup CW pin
  pinMode (resPin, OUTPUT); //setup pin for resolution mode
  if(highResOn) angleChange = 0.25; //check if high resolution is true (angle=0.25 deg)
  else angleChange = 1; //set normal resolution angle to 1 deg
  digitalWrite(resPin,highResOn); //initialize resolution mode
  digitalWrite(encoderPinCCW, LOW); //initialize CCW pin status
  digitalWrite(encoderPinCW, HIGH); //initialize CW pin status
  attachInterrupt(digitalPinToInterrupt(encoderPinCCW), doEncoderCCW, RISING); //trigger when pin goes from LOW to HIGH
  attachInterrupt(digitalPinToInterrupt(encoderPinCW), doEncoderCW, FALLING); //trigger when pin goes from HIGH to LOW
 }
 
void loop() {
  Serial.println(encoderPos*angleChange); //display angle in degrees                               
  delay(500); //wait half second
}

void doEncoderCCW() { //create function to measure CCW angle change
    encoderPos++; //count UP
}

void doEncoderCW() { //create function to measure CW angle change
    encoderPos--; //count DOWN 
}     

