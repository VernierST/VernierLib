/* VernierLibTutorialAnalogLCD (v2018)
 * This sketch reads a data point from a Vernier Analog (BTA) 
 * sensor once every half second and prints the sensor name 
 * and sensor reading with units to an LCD screen connected
 * to the Vernier DCU.
 * 
 * Plug the sensor into the Analog 1 port on the Vernier Arduino 
 * Interface Shield or into an Analog Protoboard Adapter wired 
 * to Arduino pin A0. 
 * Plug the DCU into the Digital 2 port on the shield or into a
 * Digital Protoboard Adapter wired to Arduino pins 6, 7, 8, 9. 
 * Connect the LCD pins RX, GND, VDD to DCU lines 
 * D4, GND, XP respectively.
 * Make sure you connect the DCU to a 5-volt power supply.
 */

#include "VernierLib.h" //include Vernier functions in this sketch
VernierLib Vernier; //create an instance of the VernierLib library
#include <SoftwareSerial.h> //access commands for LCD display
SoftwareSerial mySerial(3,9); //attach the LCD RX line to Arduino pin 9


void setup() {
  Vernier.autoID(); //identify the sensor being used
  mySerial.begin(9600); //setup communication to display
  delay(500); //wait half second for display to boot up
  mySerial.write(124); //send command to adjust backlight brightness of display
  mySerial.write(150); //send number between 157 (max) to 128 (off) to designate brightness
  delay(500); //wait half second for display to start
}

void loop() {
  float sensorReading = Vernier.readSensor(); //read one data value
  mySerial.write(254); //send command to move cursor
  mySerial.write(128); //move cursor to beginning of first line
  mySerial.print(Vernier.shortName()); //display sensor name
  mySerial.write(254); //send command to move cursor
  mySerial.write(138); //move cursor to middle of first line
  mySerial.print(Vernier.sensorUnits()); //display units
  mySerial.write(254); //send command to move cursor
  mySerial.write(192); //move cursor to beginning of second line
  mySerial.print(sensorReading); //display data value
  delay(1000); //wait one second
}

