/* VernierTutorialDCUServo (v 2017)
 * This sketch controls the arm on a servo motor in response
 * to the voltage from a Vernier analog (BTA)) sensor.
 *  
 * Connect the servo motor to the 3-pin connector on the DCU
 * labeled "Servo" (black lead to GND, white or yellow lead to
 * 4) or wire it to the DCU screw terminal. 
 * Plug the DCU into the Digital 2 port on the Vernier Arduino 
 * Interface Shield or into a Digital Protoboard Adapter wired 
 * to Arduino pins 6, 7, 8, and 9. 
 * Plug the sensor into the Analog 1 port on the Vernier
 * Arduino Interface Shield or into an Analog Protoboard Adapter 
 * wired to Arduino pin A0.
*/

#include <Servo.h> //include library functions fpr servo motor
Servo myservo; //create servo object to control a servo

int sensorPin=0; //initialize global variable for pin assignment to sensor
int sensorVoltage; //create global variable for the sensor reading

void setup() {
  myservo.attach(9); //attach the servo object to Arduino pin 9 
  pinMode(9,OUTPUT); //setup the servo
  pinMode(6, OUTPUT); //setup DCU line for a servo motor 
  pinMode(7, OUTPUT); //setup DCU line for a servo motor
  pinMode(8, OUTPUT); //setup DCU line for a servo motor
  digitalWrite(6, LOW); //turn off DCU line
  digitalWrite(7, LOW); //turn off DCU line
  digitalWrite(8, LOW); //turn off DCU line
}

void loop() {
  sensorVoltage = analogRead(sensorPin); //read raw voltage (value between 0 and 1023) 
  sensorVoltage = map(sensorVoltage, 0, 1023, 0, 179); //scale voltage to angle measure (value between 0 and 179) 
  myservo.write(sensorVoltage); //set servo position according to scaled value 
  delay(15); //wait 15 milliseconds for servo to reach position 
} 

