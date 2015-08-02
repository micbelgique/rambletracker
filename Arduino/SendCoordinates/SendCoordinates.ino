/*
  This should send data from the SD card file "tracker.txt"
  to our API in order to store them in the database.
 */

#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "rambletracker7574.azurewebsites.net";
// char server[] = "phpninja.be";
IPAddress ip(192, 168, 2, 2);
EthernetClient client;
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

  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected");

    // Remove/Empty the file
    // SD.remove("tracker.txt");
    myFile = SD.open("tracker.txt", FILE_WRITE);

    // re-open the file for reading:
    myFile = SD.open("tracker.txt");
    if (myFile) {
      Serial.println("Reading file...");

      // Make a HTTP POST request:
      Serial.println("[POST] /api/tracks");

      client.println("POST /api/tracks HTTP/1.1");
      client.println("Host: rambletracker7574.azurewebsites.net");

      // client.println("POST /tracker.php HTTP/1.1");
      // client.println("Host: phpninja.be");

      client.println("Content-Type: text/plain");
      client.print("Content-Length: ");
      client.println(myFile.size());
      client.println();
      while(myFile.available()) {
        client.print((char)myFile.read());
      }
      client.println();
      client.println("Connection: close");
      client.println();

      // Serial.println("File content sent.");
      // close the file:
      myFile.close();
    } else {
      // if the file didn't open, print an error:
      Serial.println("error opening tracker.txt");
    }

    Serial.println("Reading response...");
  }
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void loop()
{
  // if there are incoming bytes available
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    while (true);
  }
}


