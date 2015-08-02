
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>
#include <stdio.h>
#include <Ethernet.h>

SoftwareSerial mySerial(3, 2);

Adafruit_GPS GPS(&mySerial);

#define GPSECHO  false // Debug GPS to console ?

boolean usingInterrupt = false;
void useInterrupt(boolean); // Func prototype keeps Arduino 0023 happy

float lastLatitude = 0;
float lastLongitude = 0;

File trackerFile;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "rambletracker7574.azurewebsites.net";
IPAddress ip(192, 168, 2, 2);
EthernetClient client;

void setup()
{
  Serial.begin(115200);
  Serial.println(F("Initializing GPS..."));

  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  GPS.sendCommand(PGCMD_ANTENNA);

  Serial.println(F("Initializing SD card..."));

  if (! SD.begin(4)) {
    Serial.println(F("Initialization failed!"));
    Serial.println(F("Please insert SD card if not already in the device."));
    while(! SD.begin(4)) {
      ;
    }
    return;
  }
  Serial.println(F("Initialization done."));

  trackerFile = SD.open("tracker.txt", FILE_WRITE);


  useInterrupt(true);

  delay(1000);
  // Ask for firmware version
  mySerial.println(PMTK_Q_RELEASE);
}


// Interrupt is called once a millisecond, looks for any new GPS data, and stores it
SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();
  // if you want to debug, this is a good time to do it!
#ifdef UDR0
  if (GPSECHO)
    if (c) UDR0 = c;
    // writing direct to UDR0 is much much faster than Serial.print
    // but only one character can be written at a time.
#endif
}

void useInterrupt(boolean v) {
  if (v) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    usingInterrupt = true;
  } else {
    // do not call the interrupt function COMPA anymore
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
  }
}

uint32_t timer = millis();
void loop()                     // run over and over again
{
  // in case you are not using the interrupt above, you'll
  // need to 'hand query' the GPS, not suggested :(
  if (! usingInterrupt) {
    // read data from the GPS in the 'main loop'
    char c = GPS.read();
    // if you want to debug, this is a good time to do it!
    if (GPSECHO)
      if (c) Serial.print(c);
  }

  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences!
    // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
    //Serial.println(GPS.lastNMEA());   // this also sets the newNMEAreceived() flag to false

    if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
      return;  // we can fail to parse a sentence in which case we should just wait for another
  }

  // if millis() or timer wraps around, we'll just reset it
  if (timer > millis())  timer = millis();

  // approximately every 2 seconds or so, print out the current stats
  if (millis() - timer > 4000) {
    timer = millis(); // reset the timer

    if (Ethernet.begin(mac) == 0) {
      Serial.println(F("Waiting Ethernet Connection to sync..."));
      Ethernet.begin(mac, ip);
    }

    if (client.connect(server, 80)) {
      trackerFile = SD.open("tracker.txt");
      if (trackerFile) {
        client.println("POST /api/tracks HTTP/1.1");
        client.println("Host: rambletracker7574.azurewebsites.net");

        client.println("Content-Type: text/plain");
        client.print("Content-Length: ");
        client.println("389");
        client.println();
        while(trackerFile.available()) {
          client.print((char)trackerFile.read());
        }
        client.println();
        client.println("Connection: close");
        client.println();

        Serial.println("File content sent.");
        // close the file:
        trackerFile.close();
      } else {
        // if the file didn't open, print an error:
        Serial.println("error opening tracker.txt");
      }
    }

    if (GPS.fix) {

      if (lastLatitude == 0 || (lastLatitude != GPS.latitudeDegrees && abs(GPS.latitudeDegrees - lastLatitude) > 0.00001) || (lastLongitude != GPS.longitudeDegrees && abs(GPS.longitudeDegrees - lastLongitude) > 0.00001)) {

        // Lat & Long
        Serial.print(GPS.latitudeDegrees, 6); // N/S
        Serial.print(F(","));
        Serial.print(GPS.longitudeDegrees, 6); // E/O
        Serial.print(F(","));
        // Date & Time
        Serial.print(F("20"));
        Serial.print(prepend_leading_zero(GPS.year));
        Serial.print(F("-"));
        Serial.print(prepend_leading_zero(GPS.month));
        Serial.print(F("-"));
        Serial.print(prepend_leading_zero(GPS.day));
        Serial.print(F(" "));
        Serial.print(prepend_leading_zero(GPS.hour));
        Serial.print(F(":"));
        Serial.print(prepend_leading_zero(GPS.minute));
        Serial.print(F(":"));
        Serial.print(prepend_leading_zero(GPS.seconds));
        Serial.println();

        trackerFile.print(GPS.latitudeDegrees, 6);
        trackerFile.print(",");
        trackerFile.print(GPS.longitudeDegrees, 6);
        trackerFile.print(",");
        trackerFile.print(F("20"));
        trackerFile.print(prepend_leading_zero(GPS.year));
        trackerFile.print("-");
        trackerFile.print(prepend_leading_zero(GPS.month));
        trackerFile.print("-");
        trackerFile.print(prepend_leading_zero(GPS.day));
        trackerFile.print(" ");
        trackerFile.print(prepend_leading_zero(GPS.hour));
        trackerFile.print(":");
        trackerFile.print(prepend_leading_zero(GPS.minute));
        trackerFile.print(":");
        trackerFile.print(prepend_leading_zero(GPS.seconds));
        trackerFile.print("\r\n");
        trackerFile.flush();
      } else {
        Serial.println(F("Move.."));
      }

      lastLatitude = GPS.latitudeDegrees;
      lastLongitude = GPS.longitudeDegrees;
    } else {
      Serial.println(F("Looking..."));
    }
  }
}

String prepend_leading_zero(int v)
{
  return v < 10 ? "0" + (String)v : (String)v;
}