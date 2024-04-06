#define NO2_WORKER_PIN A0
#define NO2_REFERENCE_PIN A1
#define NO2_COUNTER_PIN A2
// #define MAGNETOMETER_1_OUTMINUS_PIN A3
// #define MAGNETOMETER_1_OUTPLUS_PIN A4
// #define MAGNETOMETER_2_OUTMINUS_PIN A5
// #define MAGNETOMETER_2_OUTPLUS_PIN A6
// #define MAGNETOMETER_3_OUTMINUS_PIN A7
// #define MAGNETOMETER_3_OUTPLUS_PIN A8
// #define MAGNETOMETER_4_OUTMINUS_PIN A9
// #define MAGNETOMETER_4_OUTPLUS_PIN A10
#define SD_CARD_PIN 10

#define seaLevelPressure_hPa 1013.25
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <SD.h>
#include <SPI.h>

const float magSens = 0.02;  // Magnetometer sensitivity V/V/mT
const int magOffset = 3;     // Magnetometer offset bits

File dataFile;

Adafruit_BMP085 bmp;

void setup() {
  Serial.begin(9600);
  // if (!bmp.begin()) {
  //   Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  //   while (1) {
  //   }
  // }

  if (!SD.begin(SD_CARD_PIN)) {
    Serial.println("Card failed, or not present");
    while (1) {
    }
  }
  Serial.println("Card initialized.");
}

void loop() {
  int no2WorkerValue = analogRead(NO2_WORKER_PIN);
  int no2ReferenceValue = analogRead(NO2_REFERENCE_PIN);
  int no2CounterValue = analogRead(NO2_COUNTER_PIN);

  // NO2 Raw voltage data
  Serial.print("NO2 Worker: ");
  Serial.print(no2WorkerValue);
  Serial.print(", Reference: ");
  Serial.print(no2ReferenceValue);
  Serial.print(", Counter: ");
  Serial.println(no2CounterValue);
  Serial.println();

  // BMP180 data
  // Serial.print("Temperature = ");
  // Serial.print(bmp.readTemperature());
  // Serial.println(" *C");

  // Serial.print("Pressure = ");
  // Serial.print(bmp.readPressure());
  // Serial.println(" Pa");

  // Serial.print("Altitude = ");
  // Serial.print(bmp.readAltitude());
  // Serial.println(" meters");

  // Serial.print("Pressure at sealevel (calculated) = ");
  // Serial.print(bmp.readSealevelPressure());
  // Serial.println(" Pa");

  // Serial.print("Real altitude = ");
  // Serial.print(bmp.readAltitude(seaLevelPressure_hPa * 100));
  // Serial.println(" meters"); // 46m too low according to Apple Watch -- 25.26m at Carleton Tunnel Dunton

  Serial.println();

  // Magnetometer data
  // Serial.print(float(analogRead(MAGNETOMETER_1_OUTMINUS_PIN) - analogRead(MAGNETOMETER_1_OUTPLUS_PIN) - magOffset) / 1024 / magSens);
  // Serial.println(" mT \r");

  // Serial.print(float(analogRead(MAGNETOMETER_2_OUTMINUS_PIN) - analogRead(MAGNETOMETER_2_OUTPLUS_PIN) - magOffset) / 1024 / magSens);
  // Serial.println(" mT \r");

  // Serial.print(float(analogRead(MAGNETOMETER_3_OUTMINUS_PIN) - analogRead(MAGNETOMETER_3_OUTPLUS_PIN) - magOffset) / 1024 / magSens);
  // Serial.println(" mT \r");

  // Serial.print(float(analogRead(MAGNETOMETER_4_OUTMINUS_PIN) - analogRead(MAGNETOMETER_4_OUTPLUS_PIN) - magOffset) / 1024 / magSens);
  // Serial.println(" mT \r");

  // SD Card writing
  // dataFile = SD.open("data.txt", FILE_WRITE);
  // if (dataFile) {
  //   dataFile.println("Hello");
  //   dataFile.close();
  // } else {                                                                                                             
  //   Serial.println("Error opening data file");
  // }

  delay(1000);
}
