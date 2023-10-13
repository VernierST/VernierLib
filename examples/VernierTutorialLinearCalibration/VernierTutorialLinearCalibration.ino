/* VernierTutorialLinearCalibration (v2017)
 * This sketch reads the raw count from a Vernier Analog (BTA) 
 * sensor once every half second, and uses its algebraic slope 
 * and intercept to convert it to standard units.
 * 
 * Plug the sensor into the Analog 2 port on the Vernier Arduino 
 * Interface Shield or into an Analog Protoboard Adapter wired 
 * to Arduino pin A2.
 */

float rawCount; //create global variable for reading from A/D converter (0-1023)
float voltage; //create global variable for voltage (0-5V)
float sensorValue; //create global variable for sensor value
float slope = -4.9; //create global variable for slope for a Dual-Range Force Sensor +/-10N range
float intercept = 12.25; //create global variable for intercept for a Dual-Range Force Sensor +/-10N range
char *units = "N"; //create global variable for units for a Dual-Range Force Sensor


void setup() {
  Serial.begin(9600);
  while (!Serial);
  delay(4000);    //Need time for the Serial Monitor to become available
}

void loop() {
  rawCount = analogRead(A2); //read one data value (0-1023)
  voltage = rawCount/1023*5; //convert raw count to voltage (0-5V)
  sensorValue = slope*voltage+intercept; //convert to sensor value with linear calibration equation
  Serial.print(sensorValue); //print sensor value 
  Serial.print(" ");
  Serial.println(units); //print units and skip to next line
  delay(500); //wait half second
}

