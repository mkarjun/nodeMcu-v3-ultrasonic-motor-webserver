/*
static const uint8_t D0   = 16;
static const uint8_t D1   = 5;
static const uint8_t D2   = 4;
static const uint8_t D3   = 0;
static const uint8_t D4   = 2;
static const uint8_t D5   = 14;
static const uint8_t D6   = 12;
static const uint8_t D7   = 13;
static const uint8_t D8   = 15;
static const uint8_t D9   = 3;
static const uint8_t D10  = 1;
*/
#define trigPin 12  //d6
#define echoPin 14  //d5

#include "ESP8266WiFi.h"
const char* ssid = "Lenovo A6000";
const char* password = "1@qazqaz";
 
int motorPin = 13; // GPIO13
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(500);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
 
  pinMode(motorPin, OUTPUT);
  digitalWrite(motorPin, LOW);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
   delay(100);
  Serial.print("Use this URL to connect: ");
   delay(100);
    delay(100);
  Serial.print("http://");
   delay(100);
  Serial.print(WiFi.localIP());
  Serial.println("/");
  delay(100);
}
 
void loop() {
  long duration, distance;
  /*====================================*/
/*sonic*/
//long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delay(100); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delay(100); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print(distance);
  Serial.println(" cm");
   if(distance <= 4) {
    digitalWrite(motorPin, LOW);
    }

    
  /*==========================================*/
   //delay(100);
    //delay(100);
     delay(300);
        // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = LOW;
  if (request.indexOf("/motor=ON") != -1)  {
     if (distance > 7){
    digitalWrite(motorPin, HIGH);
    value = HIGH;
                       }
  else if (distance < 4) {
    digitalWrite(motorPin, LOW);
    value = LOW;
                           }
  //  digitalWrite(motorPin, HIGH);
    //value = HIGH;
  }
     if (distance >= 4){
        if (request.indexOf("/motor=OFF") != -1)  {
    digitalWrite(motorPin, LOW);
    value = LOW;
  }
  else{    
    digitalWrite(motorPin, HIGH);
  }
     }
 /*==========================================
 if (distance >= 7){
    digitalWrite(motorPin, HIGH);
    value = HIGH;
  }
  else if (distance <= 4) {
    digitalWrite(motorPin, LOW);
    value = LOW;
  }
 ==========================================*/
// Set motorPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  MARRAKARUTH PAGE KITTILA
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
client.print("* water level : ");
 client.print(distance);
 client.print("    ");
  client.print("*   motor is now : ");
 
  if(value == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("<a href=\"/motor=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/motor=OFF\"\"><button>Turn Off </button></a><br />");  
  client.println("<a href=\"\"><button>refresh </button></a>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");


}
