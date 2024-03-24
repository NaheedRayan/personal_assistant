#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>


const char *ssid = "Mi Phone";
const char *password = "12345671";

// const int relayPin = D2; // Change this to the GPIO pin where the relay is connected

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Print the ESP8266 IP address
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());


  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH);//(Note that LOW is the voltage level but actually the LED is on; this is because it is active low on the ESP-01)
  
  
  // Define HTTP endpoints
  server.on("/", HTTP_GET, handleRoot);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String responseMessage;

  // Check if the URL contains the parameter "action"
  if (server.hasArg("component_name")&&server.hasArg("component_status")) {
    String component_name = server.arg("component_name");
    String component_status = server.arg("component_status");

    // Check the value of the "action" parameter
    if (component_name.equals("light1") && component_status.equals("9")) {
      digitalWrite(BUILTIN_LED, LOW);
      responseMessage = "Light1 turned ON";
      Serial.println(responseMessage);
    } 
    else if (component_name.equals("light1") && component_status.equals("0")) {
      digitalWrite(BUILTIN_LED, HIGH);
      responseMessage = "Light1 turned OFF";
      Serial.println(responseMessage);
    } 
    else if (component_name.equals("light2") && component_status.equals("9")) {
      digitalWrite(BUILTIN_LED, LOW);
      responseMessage = "Light2 turned ON";
      Serial.println(responseMessage);
    } 
    else if (component_name.equals("light2") && component_status.equals("0")) {
      digitalWrite(BUILTIN_LED, HIGH);
      responseMessage = "Light2 turned OFF";
      Serial.println(responseMessage);
    } 

    else if (component_name.equals("fan1") && component_status.equals("9")) {
      digitalWrite(BUILTIN_LED, LOW);
      responseMessage = "fan1 turned ON";
      Serial.println(responseMessage);
    } 
    else if (component_name.equals("fan1") && component_status.equals("0")) {
      digitalWrite(BUILTIN_LED, HIGH);
      responseMessage = "fan1 turned OFF";
      Serial.println(responseMessage);
    } 
    else if (component_name.equals("fan2") && component_status.equals("9")) {
      digitalWrite(BUILTIN_LED, LOW);
      responseMessage = "fan2 turned ON";
      Serial.println(responseMessage);
    } 
    else if (component_name.equals("fan2") && component_status.equals("0")) {
      digitalWrite(BUILTIN_LED, HIGH);
      responseMessage = "fan2 turned OFF";
      Serial.println(responseMessage);
    } 

    
    
    
    
    else {
      responseMessage = "Invalid action";
      Serial.println(responseMessage);

    }
  } else {
    responseMessage = "Missing action parameter";
    Serial.println(responseMessage);

  }

 

  // Send the response to the client
  server.send(200, "text/plain", responseMessage);
}