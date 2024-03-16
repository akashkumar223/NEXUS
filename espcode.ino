#include <ESP8266WiFi.h>
String apiKey = "B2GETGHSCH5KTJ1R"; // Enter your Write API key from ThingSpeak
const char* ssid = "Redmi"; // replace with your wifi ssid and wpa2 key
const char* pass = "akash123";
const char* server = "api.thingspeak.com";
#define Gas_sensor 0 
int AQI;
WiFiClient client;
void setup()
{
 Serial.begin(115200);
 delay(10);
 pinMode(Gas_sensor, INPUT);
 Serial.println("Connecting to ");
 Serial.println(ssid);
 WiFi.begin(ssid, pass);
 while (WiFi.status() != WL_CONNECTED)
 {
 delay(500);
 Serial.print(".");
 }
 Serial.println("");
 Serial.println("WiFi connected");
}
void loop()
{

 AQI = analogRead(Gas_sensor);

 if (client.connect(server,80)) // "184.106.153.149" or api.thingspeak.com
 {

 String postStr = apiKey;
 postStr +="&field1=";
 postStr += String(AQI);
 postStr += "\r\n\r\n";
 client.print("POST /update HTTP/1.1\n");
 client.print("Host: api.thingspeak.com\n");
 client.print("Connection: close\n");
 client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
 client.print("Content-Type: application/x-www-form-urlencoded\n");
 client.print("Content-Length: ");
 client.print(postStr.length());
 client.print("\n\n");
 client.print(postStr);
 Serial.print("AQI: ");
 Serial.print(AQI);
 
 }
 client.stop();
 Serial.println("Waiting...");

 // thingspeak needs minimum 15 sec delay between updates
 delay(15000);
}