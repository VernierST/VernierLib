/* VernierTutorialAnalogVoltage (v2017)
 * This sketch reads the raw count from a Vernier Analog (BTA) 
 * sensor once every half second, converts it to a voltage, 
 * and prints both values to the Serial Monitor.
 * 
 * Plug the sensor into the Analog 2 port on the Vernier Arduino 
 * Interface Shield or into an Analog Protoboard Adapter wired 
 * to Arduino pin A2.
 */

float rawCount; //create global variable for reading from A/D converter (0-1023)
float voltage; //create global variable for voltage (0-5V)
 
void setup() {
  Serial.begin(9600);
  while (!Serial);
  delay(4000);    //Need time for the Serial Monitor to become available
}

void loop() {
  rawCount = analogRead(A2); //read one data value (0-1023)
  voltage = rawCount/1023*5; //convert raw count to voltage (0-5V)
  Serial.print(rawCount); //print raw count 
  Serial.print("\t"); //print a tab character
  Serial.println(voltage); //print voltage and skip to next line
  delay(500); //wait half second
}

