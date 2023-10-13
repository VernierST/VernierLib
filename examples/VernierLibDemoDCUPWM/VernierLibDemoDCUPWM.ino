/*
Line 4 of the Digitial Control Unit (DCU) has the ability to 
perform Pulse Width Modulation (PWM) output. Demonstrate PWM
output while also reading from a LabQuest sensor. 

 - Connect the Vernier Arduino Interface Shield to a RedBoard, UNO R3 or R4.
 - Connect a Vernier LabQuest sensor to ANALOG 1
 - Connect a Vernier DCU to DIGITAL 2
 - Upload the code
 - Watch the LED of line 4 of the DCU, it should fade on and off

*/

#include "VernierLib.h" 
VernierLib Vernier;
byte PWMSetting;


// Prepare the Serial Monitor and Identify the LabQuest sensor
void setup()
{
  Serial.begin(9600);
  while (!Serial);
  delay(4000);    //Need time for the Serial Monitor to become available
  Vernier.autoID();    // automatically identify the LabQuest sensor
}

// Take a sensor reading and then control the brightness of
// DCU line 4 using this line's ability to perform PWM
void loop()
{
  float sensorReading = Vernier.readSensor();
  Serial.print(sensorReading);
  Serial.print(" ");
  Serial.println(Vernier.sensorUnits());

  // demononstrate PWM by fade in from min to max in increments of 5 points:
  for(int PWMSetting = 0 ; PWMSetting <= 255; PWMSetting +=5) 
  { 
    // sets the value (range from 0 to 255):
    Vernier.DCUPWM(PWMSetting);   //set PWM level    
    delay(30);                            
  } 
  // fade out from max to min in increments of 5 points:
  for(int PWMSetting = 255 ; PWMSetting >= 0; PWMSetting -=5) 
  { 
    // sets the value (range from 255 to 0):
    Vernier.DCUPWM(PWMSetting);   //set PWM level        
    delay(30);                            
  } 
}
   
