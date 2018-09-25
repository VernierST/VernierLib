/* VernierLibTutorialDCUPWM (v2018)
 * This sketch uses pulse-width modulation (PWM) to control
 * the speed of a DC motor connected to a Vernier DCU. The 
 * motor will slowly increase its speed from 0 to max and 
 * then slowly decrease its speed from max to 0.
 * 
 * Plug the DCU into the Digital 2 port on the Vernier Arduino 
 * Interface Shield or into a Digital Protoboard Adapter wired 
 * to Arduino pins 6, 7, 8, and 9. Connect the DC motor to DCU
 * lines D4 and GND.
 */

#include "VernierLib.h" //include Vernier functions in this sketch
VernierLib Vernier; //create an instance of the VernierLib library

int PWMSetting; //create global variable for level of PWM

void setup() {
}

void loop() {
    // demononstrate PWM by fade in from 0 to max in increments of 5 points
    for(int PWMSetting = 0 ; PWMSetting <= 255; PWMSetting +=5) 
    { 
      Vernier.DCUPWM(PWMSetting); //turn on motor to PWM level 
      delay(30); //wait 30 milliseconds to see timing effect                           
    } 
     // fade out from max to 0 in increments of 5 points
     for(int PWMSetting = 255 ; PWMSetting >= 0; PWMSetting -=5) 
     { 
       Vernier.DCUPWM(PWMSetting); //turn on motor to PWM level    
       delay(30); //wait 30 milliseconds to see timing effect                           
      } 
     delay(1000); //wait 1 sec before repeating
   }

