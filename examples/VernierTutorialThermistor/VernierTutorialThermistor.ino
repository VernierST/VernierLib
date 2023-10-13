/* VernierTutorialThermistor (v2017)
 * This sketch reads the temperature from a Vernier Stainless
 * Steel Temperature Probe or a Surface Temperature Sensor once
 * every half second.
 * 
 * We use the Steinhart-Hart equation (in the function
 * Thermistor) to calculate temperature from the raw voltage
 * reading. Because of the use of log functions in the
 * Steinhart-Hart equation, this sketch requires the math.h
 * library.
 * 
 * Plug the temperature sensor into the Analog 2 port on the 
 * Vernier Arduino Interface Shield or into an Analog 
 * Protoboard Adapter wired to Arduino pin A2.
 */

#include <math.h> //include library for log function

float rawCount; //create global variable for reading from A/D converter (0-1023)
float temperature; //create global variable for temperature in Celsius

void setup() {
  Serial.begin(9600);
  while (!Serial);
  delay(4000);   //Need time for the Serial Monitor to become available
}

void loop() {
  rawCount=analogRead(A2); //read one data value (0-1023)
  temperature=thermistor(rawCount); //calculate temperature
  Serial.println(temperature,1); // display temperature to one decimal)                               
  delay(500); //wait half second
}

//This function calculates temperature from raw count
float thermistor(int raw) {
  float resistor=15000; //initialize value of fixed resistor in Vernier shield
  float resistance; //create local variable for resistance
  float temp; //create local variable for temperature

  resistance=log(resistor*raw/(1024-raw)); //calculate resistance
  temp = 1 / (0.00102119 + (0.000222468 * resistance) + (0.000000133342 * resistance * resistance * resistance)); //calculate temperature using the Steinhart-Hart equation
  temp = temp - 273.15; //Convert Kelvin to Celsius                      
  return temp; //return the temperature
}

