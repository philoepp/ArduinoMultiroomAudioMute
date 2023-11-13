/*
  This a simple example of the aREST Library for the ESP8266 WiFi chip.
  See the README file for more details.

  Written in 2015 by Marco Schwartz under a GPL license.
*/

// Import required libraries
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <aREST.h>

// Create aREST instance
aREST rest = aREST();

// WiFi parameters
const char* ssid = "";
const char* password = "";

// The port to listen for incoming TCP connections
#define LISTEN_PORT           80

// Define output ports for muting

/*
	Either Pin 0/2/4/5 make problems during boot, probably Pin 0/2.
	Change those pins to SPI Pins located in the middle directly on the esp board..
	https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/
*/

#define PIN_ZONE_1  2 // Check
#define PIN_ZONE_2  0 // Check
#define PIN_ZONE_3  4 // Check
#define PIN_ZONE_4  5 // Check
#define PIN_ZONE_5  12
#define PIN_ZONE_6  13
#define PIN_ZONE_7  14
#define PIN_ZONE_8  16
#define PIN_RELAY   15 // GPIO15 needs pulldown

// Create an instance of the server
WiFiServer server(LISTEN_PORT);

// Declare functions to be exposed to the API
int zone1(String command);
int zone2(String command);
int zone3(String command);
int zone4(String command);
int zone5(String command);
int zone6(String command);
int zone7(String command);
int zone8(String command);
int relay(String command);

void setup(void)
{
  // Start Serial
  Serial.begin(115200);

  // Function to be exposed
  rest.function("zone1", zone1);
  rest.function("zone2", zone2);
  rest.function("zone3", zone3);
  rest.function("zone4", zone4);
  rest.function("zone5", zone5);
  rest.function("zone6", zone6);
  rest.function("zone7", zone7);
  rest.function("zone8", zone8);
  rest.function("relay", relay);

  // Give name & ID to the device (ID should be 6 characters long)
  rest.set_id("1");
  rest.set_name("esp8266");

  // Connect to WiFi
  WiFi.hostname("ESP8266ZoneMute");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Activate mDNS this is used to be able to connect to the server
  // with local DNS hostmane esp8266.local
  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());

  // Set mute pins to output
  pinMode(PIN_ZONE_1, OUTPUT);
  pinMode(PIN_ZONE_2, OUTPUT);
  pinMode(PIN_ZONE_3, OUTPUT);
  pinMode(PIN_ZONE_4, OUTPUT);
  pinMode(PIN_ZONE_5, OUTPUT);
  pinMode(PIN_ZONE_6, OUTPUT);
  pinMode(PIN_ZONE_7, OUTPUT);
  pinMode(PIN_ZONE_8, OUTPUT);
  pinMode(PIN_RELAY, OUTPUT);

  // And force them to high
  digitalWrite(PIN_ZONE_1, HIGH);
  digitalWrite(PIN_ZONE_2, HIGH);
  digitalWrite(PIN_ZONE_3, HIGH);
  digitalWrite(PIN_ZONE_4, HIGH);
  digitalWrite(PIN_ZONE_5, HIGH);
  digitalWrite(PIN_ZONE_6, HIGH);
  digitalWrite(PIN_ZONE_7, HIGH);
  digitalWrite(PIN_ZONE_8, HIGH);
  digitalWrite(PIN_RELAY, LOW);
}

void loop() {

  // Handle REST calls
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while(!client.available()){
    delay(1);
  }
  rest.handle(client);

  Serial.println(millis());
}

// Custom function accessible by the API
int zone1(String command) {
  // Get state from command
  int state = command.toInt();

  Serial.print("Received command for zone 1: ");
  Serial.println(state);

  digitalWrite(PIN_ZONE_1, state);
  return 1;
}

// Custom function accessible by the API
int zone2(String command) {

  // Get state from command
  int state = command.toInt();

  digitalWrite(PIN_ZONE_2, state);
  return 1;
}

// Custom function accessible by the API
int zone3(String command) {

  // Get state from command
  int state = command.toInt();

  digitalWrite(PIN_ZONE_3, state);
  return 1;
}

// Custom function accessible by the API
int zone4(String command) {

  // Get state from command
  int state = command.toInt();

  digitalWrite(PIN_ZONE_4, state);
  return 1;
}

// Custom function accessible by the API
int zone5(String command) {

  // Get state from command
  int state = command.toInt();

  digitalWrite(PIN_ZONE_5, state);
  return 1;
}

// Custom function accessible by the API
int zone6(String command) {

  // Get state from command
  int state = command.toInt();

  digitalWrite(PIN_ZONE_6, state);
  return 1;
}

// Custom function accessible by the API
int zone7(String command) {

  // Get state from command
  int state = command.toInt();

  digitalWrite(PIN_ZONE_7, state);
  return 1;
}

// Custom function accessible by the API
int zone8(String command) {

  // Get state from command
  int state = command.toInt();

  digitalWrite(PIN_ZONE_8, state);
  return 1;
}

// Custom function accessible by the API
int relay(String command) {

  // Get state from command
  int state = command.toInt();

  digitalWrite(PIN_RELAY, state);
  return 1;
}
