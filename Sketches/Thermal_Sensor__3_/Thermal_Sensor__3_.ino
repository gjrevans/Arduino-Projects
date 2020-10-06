#include <max6675.h>

// Declare Constants
#define CS_PIN_1       4 // 6675 Chip Select for Module 1
#define CS_PIN_2       5 // 6675 Chip Select for Module 2
#define CS_PIN_3       6 // 6675 Chip Select for Module 3

#define LIGHT_BAR_PIN  7 // Relay pin to toggle light bar
#define SO_PIN         12 // 6675 Shared Serial Output
#define CK_PIN         13 // 6675 Shared Clock Pin


// Initialize Thermocouples
MAX6675 thermocouple1(CK_PIN, CS_PIN_1, SO_PIN);
MAX6675 thermocouple2(CK_PIN, CS_PIN_2, SO_PIN);
MAX6675 thermocouple3(CK_PIN, CS_PIN_3, SO_PIN);

// Initial Temperature Values
float TEMP_1 = 0;
float TEMP_2 = 0;
float TEMP_3 = 0;

// Relay Delay
int onWait = 20000; // Time On
int offWait = 25000; // Time Off


// MAX6675 is not perfectly calibrated
int variance = 6; // Degrees celsius variance from room temp

void setup() {
  Serial.begin(9600);

  pinMode(LIGHT_BAR_PIN, OUTPUT);
}

void loop() {
  // Turn Pin on for Time
  digitalWrite(LIGHT_BAR_PIN, LOW);
  readTemperature("ON");
  delay(onWait);
  
  // Turn Pin off for Time
  digitalWrite(LIGHT_BAR_PIN, HIGH);
  readTemperature("OFF");
  delay(offWait);
}

float adjustedTemperatureReading(float temperature) {
  return temperature - variance;
}

void readTemperature(String state) {
  Serial.print(state);
  Serial.print(", ");
  
  TEMP_1 = thermocouple1.readCelsius();
  TEMP_1 = adjustedTemperatureReading(TEMP_1);
  delay(250);
  
  TEMP_2 = thermocouple2.readCelsius();
  TEMP_2 = adjustedTemperatureReading(TEMP_2);
  delay(250);
  
  TEMP_3 = thermocouple3.readCelsius();
  TEMP_3 = adjustedTemperatureReading(TEMP_3);
  delay(250);
  
  printTemp(TEMP_1, TEMP_2, TEMP_3);
}

void printTemp(float TEMP_1, float TEMP_2, float TEMP_3) {
  Serial.print(TEMP_1);
  Serial.print(", ");
  Serial.print(TEMP_2);
  Serial.print(", ");
  Serial.println(TEMP_3);  
}
