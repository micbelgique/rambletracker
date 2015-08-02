#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>

SoftwareSerial mySerial(3, 2);

Adafruit_GPS GPS(&mySerial);

#define GPSECHO  false // Debug GPS to console ?

boolean usingInterrupt = false;
void useInterrupt(boolean);

float lastLatitude = 0;
float lastLongitude = 0;

File trackerFile;

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
        Serial.println(F("Initializing failed!"));
        Serial.println(F("Please insert SD card if not already in the device."));
        while(! SD.begin(4)) {
            ;
        }
        return;
    }

    Serial.println(F("Initialization done."));

    useInterrupt(true);

    delay(1000);

    mySerial.println(PMTK_Q_RELEASE);
}

SIGNAL(TIMER0_COMPA_vect) {
    char c = GPS.read();
    #ifdef UDR0
        if (GPSECHO)
            if (c) UDR0 = c;
    #endif
}

void useInterrupt(boolean v) {
    if (v) {
        OCR0A = 0xAF;
        TIMSK0 |= _BV(OCIE0A);
        usingInterrupt = true;
    } else {
        TIMSK0 &= ~_BV(OCIE0A);
        usingInterrupt = false;
    }
}

uint32_t timer = millis();
void loop()
{
    if (! usingInterrupt) {
        char c = GPS.read();
        if (GPSECHO)
            if (c) Serial.print(c);
    }

    if (GPS.newNMEAreceived()) {
        if (!GPS.parse(GPS.lastNMEA()))
            return;
    }

    if (timer > millis())  timer = millis();

    if (millis() - timer > 4000) {
        timer = millis();
        if (GPS.fix) {
            if (lastLatitude == 0 || (lastLatitude != GPS.latitudeDegrees && abs(GPS.latitudeDegrees - lastLatitude) > 0.00001) || (lastLongitude != GPS.longitudeDegrees && abs(GPS.longitudeDegrees - lastLongitude) > 0.00001)) {
                trackerFile = SD.open("tracker.txt");
                if (trackerFile) {
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
                    Serial.println("error opening tracker.txt");
                }
            } else {
                Serial.println(F("Move further to get new coordinates.."));
            }

            lastLatitude = GPS.latitudeDegrees;
            lastLongitude = GPS.longitudeDegrees;
        } else {
            Serial.println(F("Looking for satellites..."));
        }
    }
}

String prepend_leading_zero(int v)
{
  return v < 10 ? "0" + (String)v : (String)v;
}