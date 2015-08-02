/*
  SD card read/write

 This example shows how to read and write data to and from an SD card file
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4

 created   Nov 2010
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */

#include <SPI.h>
#include <SD.h>

File myFile;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  // Remove/Empty the file
  SD.remove("tracker.txt");
  myFile = SD.open("tracker.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to tracker.txt...");
    myFile.println("50.357933,5.496082,2015-07-31 17:12:18");
    myFile.println("50.359631,5.495116,2015-07-31 17:21:34");
    myFile.println("50.362040,5.497241,2015-07-31 17:28:45");
    myFile.println("50.365366,5.499923,2015-07-31 17:31:10");
    myFile.println("50.374686,5.515609,2015-07-31 17:39:28");
    myFile.println("50.372086,5.512926,2015-07-31 17:42:54");
    myFile.println("50.364969,5.506618,2015-07-31 17:46:12");
    myFile.println("50.358713,5.500824,2015-07-31 17:55:09");
    myFile.println("50.355934,5.495095,2015-07-31 18:10:08");
    myFile.print("50.357536,5.496554,2015-07-31 18:33:39");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening tracker.txt");
  }

  // re-open the file for reading:
  myFile = SD.open("tracker.txt");
  if (myFile) {
    Serial.println("tracker.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening tracker.txt");
  }
}

void loop()
{
  // nothing happens after setup
}


