/*
  SD card read/write

  This example shows how to read and write data to and from an SD card file
  The circuit:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

  created   Nov 2010
  by David A. Mellis
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

*/

#include <SPI.h>
#include <SD.h>
#include <TinyBME280.h>
#include <floatToString.h>
#include <String.h>
File myFile;
void setup() {
  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("data.csv", FILE_WRITE);
  myFile.println("Temperature, Humidity, Pressure")
  myFile.close()

  // re-open the file for reading:
  BME280setup();

  // Begin myFile monitor output for debugging
  


}

void loop() {
  // Runs forever after setup

  // Gives the temperature as a signed 32-bit integer in °C with a resolution of 0.01°C. So an output value of “5123” equals 51.23°C.
  float temp = BME280temperature() / 100;
  String stemp;
  stemp = String(temp);
  // Pives the pressure in Pa as an unsigned 32-bit integer, so an output value of “96386” equals 96386 Pa, or 963.86 hPa.
  float press = BME280pressure() / 100;
  String spress;
  spress = String(press);
  // Gives the humidity in %RH with a resolution of 0.01% RH, so an output value of “4653” represents 46.53 %RH.
  float humid = BME280humidity() / 100;
  String shumid;
  shumid = String(humid);

  myFile = SD.open("data.csv", FILE_WRITE);

  // Print the data to myFile output!
  myFile.println(stemp + "," + shumid + "," + spress);
  myFile.close();
  delay(1000);
}