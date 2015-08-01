/*
  This should send data from the SD card file "tracker.txt"
  to our API in order to store them in the database.
 */

#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "phpninja.be";
IPAddress ip(192, 168, 2, 2);
EthernetClient client;
File myFile;
String postData;
char fileChar;
char fileString[500];

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
  // if (client.connect(server, 80)) {
    Serial.println("connected");

    // Remove/Empty the file
    // SD.remove("tracker.txt");
    myFile = SD.open("tracker.txt", FILE_WRITE);

    // re-open the file for reading:
    myFile = SD.open("tracker.txt");
    if (myFile) {
      Serial.println("Reading tracker.txt... Size of " + myFile.size());

      postData = "{\"positions\": [";

      int i;

      for(i = 0; i < myFile.available(); i++) {
        fileChar = myFile.read();
        fileString[i] = fileChar;
      }

      // fileString[i] = ",";

      Serial.println(fileString);

      // while (myFile.available()) {

      //   fileChar = myFile.read();

      //   Serial.println("Post data :");
      //   Serial.println(postData);

      //   postData += myFile.read();
      //   postData += ", ";
      // }

      // Serial.println("Post data :");
      // Serial.println(postData);

      // postData = postData.substring(0, postData.length() - 1);
      // postData = postData + "]}";

      // Serial.println("Post data :");
      // Serial.println(postData);

      // Make a HTTP POST request:
      // Serial.println("[POST] /tracker.php");
      // client.println("POST /tracker.php HTTP/1.1");
      // client.println("Host: phpninja.be");
      // client.println("Content-Type: application/json");
      // client.print("Content-Length: ");
      // client.println(postData.length());
      // client.println();
      // client.println(postData);
      // client.println();
      // client.println("Connection: close");
      // client.println();

      // Serial.println("File content sent.");
      // close the file:
      myFile.close();
    } else {
      // if the file didn't open, print an error:
      Serial.println("error opening tracker.txt");
    }

    Serial.println("Reading response...");
  // }
  // else {
  //   // kf you didn't get a connection to the server:
  //   Serial.println("connection failed");
  // }
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


