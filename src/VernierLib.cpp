
#ifndef VernierLib_h
#define VernierLib_h
#include <math.h>
#define VERNIERLIB_LIB_VERSION "1.05" // displayed automatically

/* This is a library to make using Vernier sensors and the Digital Control Unit (DCU)
 with a Vernier/Sparkfun Interface Shield easier. There are several useful functions:
 AutoID: reads information about the sensor, including calibration information
 readSensor:  uses the calibration information and return calibrated values from the sensor
 readMotionDetector: returns the distance reading from a Vernier Motion Detector in Digital 2
 DCU:  allows you to control the output of a Vernier Digital Control Unit (DCU)
 DCUStep:  allows you to easily control a stepper motor connected to the DCU
 DCUPWM: allows you to control the voltage to a DC motor connected to the DCU
 
 Version 1.0.5 fixes a minor problem with the calibration for mV with ion-selective electrodes
 */
class VernierLib
{
public:
    VernierLib();
    
    void autoID();//this is the function for the autoID code
    // it returns calibration information
    int channel()       { return _channel; };
    float voltageID()   { return _voltageID; };
    int sensorNumber()  { return _sensorNumber;};
    // Jenny suggests this change:
    char* sensorName()   { return _sensorName ;};
    char* shortName()    { return _shortName  ;};
    char* sensorUnits()  { return _sensorUnits;};
    float slope()        { return _slope; };
    float intercept()    { return _intercept; };
    float cFactor()      { return _cFactor; };
    int calEquationType(){ return _calEquationType; };
    int page()           { return _page; };
    
    float readSensor();//This function converts count to sensor reading
    float sensorReading()     { return _sensorReading; };
    
    void DCUPWM(int PWMSetting); //function to control PWM via the DCU, line 4 (Arduino line 9)
    
    void DCU (int DCUSetting); //function for controlling a DCU
    
    void DCUStep(int stepCount, int stepDirection, int stepDelay); //function for stepper motors
    
    float readMotionDetector();//function for Motion Detectors
    float distance()     { return _distance; };
    
protected://  also known as local
    
    float _voltageID;
    int  _channel;
    int _sensorNumber;
    char _sensorName[16];
    char _shortName[12];// 11 char + terminator
    char _sensorUnits[7];
    float _slope;
    float _sum;
    float _intercept;
    float _cFactor;
    int _calEquationType;
    int _page;
    float _sensorReading;
    float _distance;
    // this misc. variable is used many places
    int _i;
};
#endif

// END OF FILE




/* This is a library to make using Vernier sensors and the Digital Control Unit (DCU)
with a Vernier/Sparkfun Interface Shield easier. There are several useful functions:
AutoID: reads information about the sensor, including calibration information
readSensor:  uses the calibration information and return calibrated values from the sensor
readMotionDetector: returns the distance reading from a Vernier Motion Detector in Digital 2
DCU:  allows you to control the output of a Vernier Digital Control Unit (DCU)
DCUStep:  allows you to easily control a stepper motor connected to the DCU
DCUPWM: allows you to control the voltage to a DC motor connected to the DCU

Version 1.0.5 fixes a minor problem with the calibration for mV with ion-selective electrodes
*/

//#define DEBUG1 // add for print statements
//single channel version
#include "VernierLib.h"
#include "Arduino.h"
#include <Wire.h>// used for I2C communication

VernierLib::VernierLib()
{
  pinMode(2, INPUT); //Echo pin; this is the pin that goes high when an echo is received 
  pinMode(3, OUTPUT);//Trigger Pin used for Motion Detector
  pinMode(6, OUTPUT);// set up DCU lines, assuming it is on Digital 2
 /
    
    /
    on DCU
  pinMode (13, OUTPUT); //LED on shield
 }

void VernierLib::autoID()
{
  _channel =1;//this is the Analog 1 only version of the library\  
  _sensorNumber=0;
  _voltageID = 0;
  _slope  = 1;
  _intercept = 0;
  _cFactor = 0;
  _page = 0; //calibration storage page (always 0 for resistor ID sensors)
  _calEquationType = 1; // for all resisto-ID sensrs, but thermistors and some I2C sensors; it will be changed in that case below
  const int _device = 0x50; //used for I2C autoID
  byte _floatbyte[5];
  byte _sensorData [128];
  for (_i = 0; _i < 128; _i++) // clear our digital ID sensor data
  {
      _sensorData[_i] = 0;
  }

  byte _resistorIDInfo[][32] =
  {
    {78, 97, 109, 101, 32, 48, 32, 32, 32, 32, 32, 32, 32, 32,          83, 104, 111, 114, 116, 78, 97, 109, 101, 32,   85, 110, 105, 116, 115, 32, 32, 0}, ///nothing*
    {84, 72, 101, 114, 109, 111, 99, 111, 117, 112, 108, 101, 32, 32,    84, 101, 109, 112, 32, 32, , 101, 110, 32, 32, 32, 32, 32, 32, 32, 32,       79, 50, 32, 32, 32, 32, 32, 32, 32, 32,        37, 32, 32, 32, 32, 32, 32, 0} //O2*};
  };
  
  _sensorName[16]="1234567890123456"; // I am using 16 characters here, plus terminator.
  _shortName[12]="shortName   ";//12 characters on name, plus terminator.
  _sensorUnits[7]="Units  ";//7 characters units, plus terminator.
  _sensorName[17]='\0'; // THESE MAY NOT BE NECESSARY
  _shortName[13]='\0';
  _sensorUnits[8]='\0';
  //set multiplexer to match channel: NOTE THIS IS GETTING READY FOR A 2-CHANNEL VERSION
  if (_channel == 1 )
    {
      digitalWrite(10, LOW); //set multiplexer for BTA1  
    } 
  else
    {
      digitalWrite(10, HIGH); //set multiplexer for BTA2   
    }
   digitalWrite(11, LOW);//

  #if defined DEBUG1
        Serial.print("_resistorIDInfo array: ");  //only if "#define" is in the code
        for (_i = 0; _i < 33; _i++)//display whole line of array as numbers
        {
            Serial.print(_resistorIDInfo [_sensorNumber][_i]);
            Serial.print(",");
        }
        Serial.println("}");
        Serial.println("_resistorIDInfo array as char: ");  //only if "#define" is in the code
        for (_i = 0; _i < 33; _i++)//display whole line of array as characters
        {
            Serial.print(char(_resistorIDInfo[_sensorNumber][_i]));
        }
        Serial.println("}");
  #endif  //DEBUG1

  //Read BTA1 Sensor with resistor ID:
  _voltageID = analogRead(A5) / 1024.0 * 5.00; // convert from count to voltage could use Vcc!!!
  if (_voltageID > 0.86 & _voltageID < 0.95) _sensorNumber = 1; //Thermocouple
  if (_voltageID > 3.72 & _voltageID < 3.86) _sensorNumber = 2; // voltage +/-10 V
    } // end of switch case
  }// end of if a resistor ID sensor is found


 
if (_sensorNumber == 0) // no resistor ID sensor found; check I2C
{
    pinMode(A4, OUTPUT); //Turn on the I2C communication!!! this can cause problems!!!
    pinMode(A5, OUTPUT);

    // check for digital ID sensor:
    Wire.begin(); // join i2c bus (address optional for master) 
    //Reading _device first time... ;
    Wire.beginTransmission(_device); // Now we're going to read it back
    Wire.write(0x0); // Sending address 0, so it knows where we'll want
    Wire.endTransmission();
    int _x = Wire.requestFrom(_device, 32);  // Start new transmission and keep reading for 32 bytes
    // note: the default buffer size for Arduino is 23 bytes. You can change it to larger. It would be
    // desirable to change it to 128 bytes and read all the data in one read. That is the way all Vernier
    //interfaces do it. is done as follows:  add#define SERIAL_BUFFER_SIZE 128 
    //check it in your sketch with:
    // Serial.print(SERIAL_BUFFER_SIZE);
    _i = 1;
    while (_x > 1)
    {
      _x = Wire.available();
      byte _c = Wire.read();    // Read a byte and write it out to the Serial port
      _sensorData [_i] = _c;
      _i++;
    }
    //Reading device second time... ;
    Wire.beginTransmission(_device); // Now we're going to read it back
    Wire.write(0x20);               // Sending address 0, so it knows where we'll want
    Wire.endTransmission();       // to read from
    _x = Wire.requestFrom(_device, 32);  // Start new transmission and keep reading for 128 bytes
    _i = 1;
    while (_x > 1)
    {
      _x = Wire.available();
      byte _c = Wire.read();    // Read a byte and write it out to the Serial port
      _sensorData [_i + 32] = _c;
      _i++;
    }
    //Reading device third time... ;
    Wire.beginTransmission(_device); // Now we're going to read it back
    Wire.write(0x40);               // Sending address 0, so it knows where we'll want
    Wire.endTransmission();       // to read from
    _x = Wire.requestFrom(_device, 32);  // Start new transmission and keep reading for 128 bytes
    _i = 1;
    while (_x > 1)
    {
      _x = Wire.available();
      byte _c = Wire.read();    // Read a byte and write it out to the Serial port
      _sensorData [_i + 64] = _c;
      _i++;
    }
    //Reading device a forth time... ;
    Wire.beginTransmission(_device); // Now we're going to read it back
    Wire.write(0x60);               // Sending address 0, so it knows where we'll want
    Wire.endTransmission();       // to read from
    _x = Wire.requestFrom(_device, 32);  // Start new transmission and keep reading for 128 bytes
    _i = 1;
    while (_x > 1)
    {
      _x = Wire.available();
      byte _c = Wire.read();    // Read a byte and write it out to the Serial port
      _sensorData [_i + 96] = _c;
      _i++;
    }
    _voltageID = -1; /// flags a I2C sensor
    ;//Determines the  sensorNumber:
    _sensorNumber= _sensorData[2];

    //Determine the calibration equation type:
    _calEquationType = _sensorData[57];

    //Determines the  calibration page:
    _page = _sensorData[70];
    // the code below uses the calibration page set:
    // Intercept starts at 71 for page 1, 90 for p2, and 109 for p3

    //Determines intercept:
    for (_i = 0; _i < 4; _i++)
    {
      _floatbyte[_i] = _sensorData[_i + 71 + (_page) * 19];
    }
    float _j = *(float*) &_floatbyte;
    _intercept = _j;

    //Determines slope:
    // slope starts at 75 for page 1, 94 for p2, and 113 for p3
    for (_i = 0; _i < 4; _i++)
    {
      _floatbyte[_i] = _sensorData[_i + 75 + (_page * 19)];
    }
    float _y = *(float*) &_floatbyte;
    _slope = _y;

    pinMode(A4, INPUT); //Turn off the I2C communication!!! this can cause problems!!!
    pinMode(A5, INPUT);

} // end of if I2C autoID


// Determine the sensor name:
for (_i = 0; _i < 16; _i++)
        {
          char _c =  _sensorData[_i + 9];
          _sensorName[_i] = _c;
        }
      _sensorName[16] = '\0';

  //Determine the short name:
for (_i = 0; _i < 11; _i++)
      {
        char _c =  _sensorData[_i + 29];  // changed from 28 to 29
        _shortName[_i] = _c;
      }
_shortName[11] = '\0';

  //determine the Units:
  // units start at 83 for page 1, 102 for p2, and 121 for p3
for (_i = 0; _i < 7; _i++)
      {
        char _c =  _sensorData[_i + 83+(_page)* 19];
        _sensorUnits[_i] = _c;
      }
_sensorUnits[7] = '\0'; //add terminating character
// Special handling for ISEs, CA, NH4, NO3, or Cl
if  (_sensorNumber > 37 && _sensorNumber < 42) strncpy(_sensorUnits, "mV     ", 7);
//Special calibration for Potasium ISE:
if  (_sensorNumber == 113) strncpy(_sensorUnits, "mV      ",7); // assign name based on sensor number

#if defined DEBUG1
     Serial.print("_voltageID ");// use this line, if you want to check the autoID voltage
     Serial.println(_voltageID);// use this line, if you want to check the autoID voltage/*

     Serial.print("sensorData array: ");  //only if "#define" is in the code
        for (_i = 0; _i < 129; _i++)//display whole array 
        {
            Serial.print (_i);
            Serial.print (" ");
            Serial.print(_sensorData[_i]);
            Serial.print (" ");
            Serial.println(char(_sensorData[_i]));
        }
#endif  //DEBUG1
 //!!!        Serial.print("calEquationType ");//!!!
 //!!!         Serial.println(calEquationType );
}// end of AutoID function

float VernierLib::readSensor()//This function converts count to sensor reading
{
  int _numberAveraged = 10; //number of readings averaged for reading reported
  int _count;
  int _sum = 0;
  float _voltage;
  byte _buttonState=0;//condition of button
  //better code for reading voltage:
  if  (_sensorNumber == 2 || _sensorNumber == 11) // one of two sensors using the +/- 10 volt line
 = _intercept + _voltage * _slope + _cFactor * _voltage * _voltage;
  //Special quadratic calibration for New (Oct. 2016 Thermocouple(123));
  if (_sensorNumber == 10) //if thermistor:
  {
  
    return _sensorReading;
 
}// END OF Read Sensor


void VernierLib::DCUPWM (int PWMSetting)
{

 // range 0 to 255
}

void VernierLib::DCUStep(int stepCount, int stepDirection, int stepDelay)
{
  int DCUStepPattern[4]; //pattern used to drive step motor
  
    };//end of for
}// end of PWM

void VernierLib::DCU(int DCUSetting)
{

switch (DCUSetting) 
  {
 
  }
}//end of DCU 

  float VernierLib::readMotionDetector()  //This function reads Motion Detector
{
    /*
VernierMotionDetector 
Takes data from a Vernier Motion Detector connected to the Digital 1 connector.

This sketch measures the time taken for the ultrasound to return (in microseconds)
 
     #ifndef VernierLib_h
     #define VernierLib_h
     #include <math.h>
     #define VERNIERLIB_LIB_VERSION "1.05" // displayed automatically
     
     /* This is a library to make using Vernier sensors and the Digital Control Unit (DCU)
     with a Vernier/Sparkfun Interface Shield easier. There are several useful functions:
     AutoID: reads information about the sensor, including calibration information
     readSensor:  uses the calibration information and return calibrated values from the sensor
     readMotionDetector: returns the distance reading from a Vernier Motion Detector in Digital 2
     DCU:  allows you to control the output of a Vernier Digital Control Unit (DCU)
     DCUStep:  allows you to easily control a stepper motor connected to the DCU
     DCUPWM: allows you to control the voltage to a DC motor connected to the DCU
     
     Version 1.0.5 fixes a minor problem with the calibration for mV with ion-selective electrodes
     */
    class VernierLib
    {
    public:
        VernierLib();
        
        void autoID();//this is the function for the autoID code
        // it returns calibration information
        int channel()       { return _channel; };
        float voltageID()   { return _voltageID; };
        int sensorNumber()  { return _sensorNumber;};
        // Jenny suggests this change:
        char* sensorName()   { return _sensorName ;};
        char* shortName()    { return _shortName  ;};
        char* sensorUnits()  { return _sensorUnits;};
        float slope()        { return _slope; };
        float intercept()    { return _intercept; };
        float cFactor()      { return _cFactor; };
        int calEquationType(){ return _calEquationType; };
        int page()           { return _page; };
        
        float readSensor();//This function converts count to sensor reading
        float sensorReading()     { return _sensorReading; };
        
        void DCUPWM(int PWMSetting); //function to control PWM via the DCU, line 4 (Arduino line 9)
        
        void DCU (int DCUSetting); //function for controlling a DCU
        
        void DCUStep(int stepCount, int stepDirection, int stepDelay); //function for stepper motors
        
        float readMotionDetector();//function for Motion Detectors
        float distance()     { return _distance; };
        
    protected://  also known as local
        
        float _voltageID;
        int  _channel;
        int _sensorNumber;
        char _sensorName[16];
        char _shortName[12];// 11 char + terminator
        char _sensorUnits[7];
        float _slope;
        float _sum;
        float _intercept;
        float _cFactor;
        int _calEquationType;
        int _page;
        float _sensorReading;
        float _distance;
        // this misc. variable is used many places
        int _i;
    };
#endif
    
    // END OF FILE

    
    
    
    ke half of the distance traveled.*/
  _distance= _duration *340/2/10000 ;// note the 340 is the speed of sound in m/s. note convert to cm
  return _distance;
 }
