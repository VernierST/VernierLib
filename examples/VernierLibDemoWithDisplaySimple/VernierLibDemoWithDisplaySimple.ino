/*
Take readings and print the sensor measurements to the Serial Monitor
and LCD display.

 - Connect the Vernier Arduino Interface Shield to a RedBoard, UNO R3 or R4.
 - Connect a Vernier LabQuest sensor to ANALOG 1
 - Connect a Vernier Digital Control Unit (DCU) to DIGITAL 2
 - Connect the LCD pins RX, GND, VDD to DCU lines D4, GND, XP, respectively.
 - Upload the code and then view the output on the LCD display or Serial Monitor

*/

#include <SoftwareSerial.h> //library used in printing to display
#include "VernierLib.h" 
VernierLib Vernier;
SoftwareSerial mySerial(3,9); //for display, pin 9 = TX, pin 3 = RX (unused)


void setup()
{
  Serial.begin(9600);
  while (!Serial);
  delay(4000);   //Need time for the Serial Monitor to become available
  Vernier.autoID();// this is the routine to do the autoID
  
  mySerial.begin(9600); // for sending characters to display
  delay(500); // wait for display to boot up
  mySerial.write(124); // adjust backlight brightness of display
  mySerial.write(150); //max=157, 150=73%, 130=40%,128=off
  delay(500); // wait for display to start
  mySerial.write(254);
  mySerial.write(1); //clear display
  mySerial.print(Vernier.shortName()); // display Short Name
  mySerial.write(254); // cursor to middle of bottom line
  mySerial.write(200);
  mySerial.print(Vernier.sensorUnits()); // display Units
}

void loop()
{
  float sensorReading = Vernier.readSensor();
  Serial.print(sensorReading);
  Serial.print(" ");
  Serial.println(Vernier.sensorUnits());

  mySerial.write(254); // command character
  mySerial.write(192); // move to line 2, position 0,
  mySerial.print(sensorReading);
  delay(1000);// a second
} 


 
