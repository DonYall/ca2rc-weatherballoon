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

#include <stdlib.h>

const float magSens = 0.02;  // Magnetometer sensitivity V/V/mT
const int magOffset = 3;     // Magnetometer offset bits

File dataFile;

Adafruit_BMP085 bmp;

char elapsed[9];

void floatToString(float value, char* buffer, int precision) {
  char temp[10]; // Temporary buffer to hold the integer part
  dtostrf(value, 7, precision, temp); // Convert float to string with desired precision, 7 chars long xxxx.xx
  strcpy(buffer, temp); // Copy the result to the output buffer
  
}

void convertSeconds(long seconds, int &hours, int &minutes, int &remaining_seconds) {
  hours = seconds / 3600;
  long remainder = seconds % 3600;
  minutes = remainder / 60;
  remaining_seconds = remainder % 60;
}

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

  
  unsigned long elapsedTime = millis();
  elapsedTime = elapsedTime/1000;
  int hours, minutes, remaining_seconds;
  convertSeconds(elapsedTime, hours, minutes, remaining_seconds);
  sprintf(elapsed, "%02d:%02d:%02d", hours, minutes, remaining_seconds);

  // NO2 Raw voltage data
  int no2WorkerValue = analogRead(NO2_WORKER_PIN);
  int no2ReferenceValue = analogRead(NO2_REFERENCE_PIN);
  int no2CounterValue = analogRead(NO2_COUNTER_PIN);
 

  // BMP180 data
  // Serial.print("Temperature = ");
  float bmp_temp = (bmp.readTemperature());
  // Serial.println(" *C");

  // Serial.print("Pressure = ");
  float bmp_pressure = (bmp.readPressure());
  // Serial.println(" Pa");

  // Serial.print("Altitude = ");
  float bmp_alt = (bmp.readAltitude());
  // Serial.println(" meters");

  // Serial.print("Pressure at sealevel (calculated) = ");
  float bmp_slpressure = (bmp.readSealevelPressure());
  // Serial.println(" Pa");

  // Serial.print("Real altitude = ");
  float bmp_realalt = (bmp.readAltitude(seaLevelPressure_hPa * 100));
  // Serial.println(" meters"); // 46m too low according to Apple Watch -- 25.26m at Carleton Tunnel Dunton

  
  /*
  // Magnetometer data
  float mag1 = (float(analogRead(MAGNETOMETER_1_OUTMINUS_PIN) - analogRead(MAGNETOMETER_1_OUTPLUS_PIN) - magOffset) / 1024 / magSens);
  // Serial.println(" mT \r");

  float mag2 = (float(analogRead(MAGNETOMETER_2_OUTMINUS_PIN) - analogRead(MAGNETOMETER_2_OUTPLUS_PIN) - magOffset) / 1024 / magSens);
  // Serial.println(" mT \r");

  float mag3 = (float(analogRead(MAGNETOMETER_3_OUTMINUS_PIN) - analogRead(MAGNETOMETER_3_OUTPLUS_PIN) - magOffset) / 1024 / magSens);
  // Serial.println(" mT \r");

  float mag4 = (float(analogRead(MAGNETOMETER_4_OUTMINUS_PIN) - analogRead(MAGNETOMETER_4_OUTPLUS_PIN) - magOffset) / 1024 / magSens);
  // Serial.println(" mT \r");
  */


  //format Strings
  char no2_out[50];
  floatToString(no2WorkerValue, no2_out, 2); // Convert float to string with 2 decimal places
  strcat(no2_out, " "); // Add space separator
  floatToString(no2ReferenceValue, no2_out + strlen(no2_out), 2); // Append next value
  strcat(no2_out, " "); // Add space separator
  floatToString(no2CounterValue, no2_out + strlen(no2_out), 2); // Append next value

  char bmp_out[100];
  floatToString(bmp_temp, bmp_out, 2);
  strcat(bmp_out, " ");
  floatToString(bmp_pressure, bmp_out + strlen(bmp_out), 2);
  strcat(bmp_out, " ");
  floatToString(bmp_alt, bmp_out + strlen(bmp_out), 2);
  strcat(bmp_out, " ");
  floatToString(bmp_slpressure, bmp_out + strlen(bmp_out), 2);
  strcat(bmp_out, " ");
  floatToString(bmp_realalt, bmp_out + strlen(bmp_out), 2);
  /*
  char mag_out[50];
  floatToString(mag1, mag_out, 2);
  strcat(mag_out, " ");
  floatToString(mag2, mag_out + strlen(mag_out), 2);
  strcat(mag_out, " ");
  floatToString(mag3, mag_out + strlen(mag_out), 2);
  strcat(mag_out, " ");
  floatToString(mag4, mag_out + strlen(mag_out), 2);
    */

  Serial.print("Elapsed time: ");
  Serial.println(elapsed);

  Serial.print("NO2 values: ");
  Serial.println(no2_out);

  Serial.print("BMP180 data: ");
  Serial.println(bmp_out);

  //Serial.print("Magnetometer data: ");
  //Serial.println(mag_out);

  SD Card writing
   dataFile = SD.open("data.txt", FILE_WRITE);
   if (dataFile) {
     dataFile.println(elapsed);
     dataFile.println(no2_out);
     dataFile.println(bmp_out);
     //dataFile.println(mag_out);
     dataFile.close();
   } else {                                                                                                             
     Serial.println("Error opening data file");
  }

  delay(1000);

  
}
