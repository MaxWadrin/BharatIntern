// Include the required libraries
#include <SoftwareSerial.h>

// Define the pin connections for each sensor
const int coPin = A0;   // Analog input pin for CO sensor
const int co2Pin = A1;  // Analog input pin for CO2 sensor
const int nh3Pin = A2;  // Analog input pin for NH3 sensor

// Create instances of SoftwareSerial for each sensor
SoftwareSerial coSerial(2, 3);   // RX, TX pins for CO sensor
SoftwareSerial co2Serial(4, 5);  // RX, TX pins for CO2 sensor
SoftwareSerial nh3Serial(6, 7);  // RX, TX pins for NH3 sensor

// Variables to store the sensor readings
int coValue, co2Value, nh3Value;

void setup() {
  // Initialize the serial communication
  Serial.begin(9600);
  
  // Initialize the SoftwareSerial for each sensor
  coSerial.begin(9600);
  co2Serial.begin(9600);
  nh3Serial.begin(9600);
}

void loop() {
  // Read the sensor values
  coValue = analogRead(coPin);
  co2Value = analogRead(co2Pin);
  nh3Value = analogRead(nh3Pin);
  
  // Convert the analog readings to voltage values
  float coVoltage = coValue * (5.0 / 1023.0);
  float co2Voltage = co2Value * (5.0 / 1023.0);
  float nh3Voltage = nh3Value * (5.0 / 1023.0);
  
  // Send the voltage values to each sensor
  coSerial.println(coVoltage);
  co2Serial.println(co2Voltage);
  nh3Serial.println(nh3Voltage);
  
  // Read the response from each sensor
  String coResponse = coSerial.readStringUntil('\n');
  String co2Response = co2Serial.readStringUntil('\n');
  String nh3Response = nh3Serial.readStringUntil('\n');
  
  // Convert the response to ppm (parts per million)
  float coPPM = coResponse.toFloat() * 1000;
  float co2PPM = co2Response.toFloat() * 1000;
  float nh3PPM = nh3Response.toFloat() * 1000;
  
  // Print the sensor readings in ppm
  Serial.print("CO: ");
  Serial.print(coPPM);
  Serial.print(" ppm\tCO2: ");
  Serial.print(co2PPM);
  Serial.print(" ppm\tNH3: ");
  Serial.print(nh3PPM);
  Serial.println(" ppm");
  
  // Delay before taking the next set of readings
  delay(1000);
}
