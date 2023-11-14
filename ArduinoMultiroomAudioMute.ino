#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //physical mac address
byte ip[] = { 192, 168, 178, 17 }; // IP address in LAN – need to change according to your Network address
byte gateway[] = { 192, 168, 0, 1 }; // internet access via router
byte subnet[] = { 255, 255, 255, 0 }; //subnet mask
EthernetServer server(80); //server port

String readString;

#define PIN_ZONE_1  2
#define PIN_ZONE_2  3
#define PIN_ZONE_3  4
#define PIN_ZONE_4  5
#define PIN_ZONE_5  6
#define PIN_ZONE_6  7
#define PIN_ZONE_7  8
#define PIN_ZONE_8  9
#define PIN_RELAY   18 // A0

void setup()
{
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
   
  // Start ethernet server
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
}

void loop(){
    // Create a client connection
    EthernetClient client = server.available();
    if (client) {
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();

                //read char by char HTTP request
                if (readString.length() < 100) {
                    readString += c;
                }

                if (c == 0x0D) {
                    client.println("HTTP/1.1 200 OK"); 
                    client.println("Content-Type: text/html");
                    client.println();

                    client.println("<html><head><title>Multiroom Audio Zone Mute</title></head><body>");
                    client.println("<h1>Multiroom Audio Zone Mute</h1><ul>");
                    client.println("<li>Zone1: <a href=\"/?Zone1On\"\">ON</a> - <a href=\"/?Zone1Off\"\">OFF</a></li>");
                    client.println("<li>Zone2: <a href=\"/?Zone2On\"\">ON</a> - <a href=\"/?Zone2Off\"\">OFF</a></li>");
                    client.println("<li>Zone3: <a href=\"/?Zone3On\"\">ON</a> - <a href=\"/?Zone3Off\"\">OFF</a></li>");
                    client.println("<li>Zone4: <a href=\"/?Zone4On\"\">ON</a> - <a href=\"/?Zone4Off\"\">OFF</a></li>");
                    client.println("<li>Zone5: <a href=\"/?Zone5On\"\">ON</a> - <a href=\"/?Zone5Off\"\">OFF</a></li>");
                    client.println("<li>Zone6: <a href=\"/?Zone6On\"\">ON</a> - <a href=\"/?Zone6Off\"\">OFF</a></li>");
                    client.println("<li>Zone7: <a href=\"/?Zone7On\"\">ON</a> - <a href=\"/?Zone7Off\"\">OFF</a></li>");
                    client.println("<li>Zone8: <a href=\"/?Zone8On\"\">ON</a> - <a href=\"/?Zone8Off\"\">OFF</a></li>");
                    client.println("<li>Relay: <a href=\"/?RelayOn\"\">ON</a> - <a href=\"/?RelayOff\"\">OFF</a></li>");
                    client.println("</ul></body></html>");

                    delay(10);
                    client.stop();

                    // Control arduino pins based on requested URL
                    if(readString.indexOf("?Zone1On") > -1) 
                    {
                        digitalWrite(PIN_ZONE_1, HIGH);
                    }
                    else if(readString.indexOf("?Zone2On") > -1) 
                    {
                        digitalWrite(PIN_ZONE_2, HIGH); 
                    }
                    else if(readString.indexOf("?Zone3On") > -1) 
                    {
                        digitalWrite(PIN_ZONE_3, HIGH); 
                    }
                    else if(readString.indexOf("?Zone4On") > -1) 
                    {
                        digitalWrite(PIN_ZONE_4, HIGH); 
                    }
                    else if(readString.indexOf("?Zone5On") > -1) 
                    {
                        digitalWrite(PIN_ZONE_5, HIGH); 
                    }
                    else if(readString.indexOf("?Zone6On") > -1) 
                    {
                        digitalWrite(PIN_ZONE_6, HIGH); 
                    }
                    else if(readString.indexOf("?Zone7On") > -1) 
                    {
                        digitalWrite(PIN_ZONE_7, HIGH); 
                    }
                    else if(readString.indexOf("?Zone8On") > -1) 
                    {
                        digitalWrite(PIN_ZONE_8, HIGH); 
                    }
                    else if(readString.indexOf("?RelayOn") > -1) 
                    {
                        digitalWrite(PIN_RELAY, HIGH); 
                    }
                    else if(readString.indexOf("?Zone1Off") > -1) 
                    {
                        digitalWrite(PIN_ZONE_1, LOW); 
                    }
                    else if(readString.indexOf("?Zone2Off") > -1) 
                    {
                        digitalWrite(PIN_ZONE_2, LOW); 
                    }
                    else if(readString.indexOf("?Zone3Off") > -1) 
                    {
                        digitalWrite(PIN_ZONE_3, LOW); 
                    }
                    else if(readString.indexOf("?Zone4Off") > -1) 
                    {
                        digitalWrite(PIN_ZONE_4, LOW); 
                    }
                    else if(readString.indexOf("?Zone5Off") > -1) 
                    {
                        digitalWrite(PIN_ZONE_5, LOW); 
                    }
                    else if(readString.indexOf("?Zone6Off") > -1) 
                    {
                        digitalWrite(PIN_ZONE_6, LOW); 
                    }
                    else if(readString.indexOf("?Zone7Off") > -1) 
                    {
                        digitalWrite(PIN_ZONE_7, LOW); 
                    }
                    else if(readString.indexOf("?Zone8Off") > -1) 
                    {
                        digitalWrite(PIN_ZONE_8, LOW); 
                    }
                    else if(readString.indexOf("?RelayOff") > -1) 
                    {
                        digitalWrite(PIN_RELAY, LOW); 
                    }

                    readString="";
                }
            }
        }
    }
}
