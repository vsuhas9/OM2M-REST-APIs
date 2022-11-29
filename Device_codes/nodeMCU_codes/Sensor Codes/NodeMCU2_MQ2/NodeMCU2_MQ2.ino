#include <JSONVar.h>
#include <JSON.h>
#include <Arduino_JSON.h>
#include <time.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>

uint32_t delayMS;

  // ############################################################### //
  // ######### COMMON CODE (CSE) FOR ALL SENSORS  ######### //
  // ###############################################################  //
  
// ##################### Update the Wifi SSID, Password and IP adress of the server ##########
// WIFI params
char* WIFI_SSID = "WiFi-SSID"; 
char* WIFI_PSWD = "WiFi-Password";

//SERVER IP ADDRESS
//For Local host: 1) If you are using Windows OS then use command "ipconfig" in Command Prompt to find IPV4 address and use that. 
//                2) If you are using Linux OS then use command "ifconfig" in terminal to find IPV4 address and use that. 
String CSE_IP      = "CSE-IP"; 
// #######################################################
int WIFI_DELAY  = 100; //ms
// oneM2M : CSE params
int   CSE_HTTP_PORT = 8080;
String CSE_NAME    = "in-name";
String CSE_M2M_ORIGIN  = "admin:admin";

// oneM2M : resources' params
int TY_AE  = 2;
int TY_CNT = 3;
int TY_CI  = 4;
int TY_SUB = 23;

// HTTP constants
int LOCAL_PORT = 9999;
char* HTTP_CREATED = "HTTP/1.1 201 Created";
char* HTTP_OK    = "HTTP/1.1 200 OK\r\n";
int REQUEST_TIME_OUT = 5000; //ms

//MISC
int SERIAL_SPEED  = 9600;
#define DEBUG
///////////////////////////////////////////
// Global variables
WiFiServer server(LOCAL_PORT);    // HTTP Server (over WiFi). Binded to listen on LOCAL_PORT contant
WiFiClient client;
// Method for creating an HTTP POST with preconfigured oneM2M headers
// param : url  --> the url path of the targted oneM2M resource on the remote CSE
// param : ty --> content-type being sent over this POST request (2 for ae, 3 for cnt, etc.)
// param : rep  --> the representaton of the resource in JSON format
String doPOST(String url, int ty, String rep) {

  String postRequest = String() + "POST " + url + " HTTP/1.1\r\n" +
                       "Host: " + CSE_IP + ":" + CSE_HTTP_PORT + "\r\n" +
                       "X-M2M-Origin: " + CSE_M2M_ORIGIN + "\r\n" +
                       "Content-Type: application/json;ty=" + ty + "\r\n" +
                       "Content-Length: " + rep.length() + "\r\n"
                       "Connection: close\r\n\n" +
                       rep;

  // Connect to the CSE address
  Serial.println("connecting to " + CSE_IP + ":" + CSE_HTTP_PORT + " ...");
  // Get a client
  WiFiClient client;
  if (!client.connect(CSE_IP, CSE_HTTP_PORT)) {
    Serial.println("Connection failed !");
    return "error";
  }
  // if connection succeeds, we show the request to be send
#ifdef DEBUG
  Serial.println(postRequest);
#endif

  // Send the HTTP POST request
  client.print(postRequest);

  // Manage a timeout
  unsigned long startTime = millis();
  while (client.available() == 0) {
    if (millis() - startTime > REQUEST_TIME_OUT) {
      Serial.println("Client Timeout");
      client.stop();
      return "error";
    }
  }
  // If success, Read the HTTP response
  String result = "";
  if (client.available()) {
    result = client.readStringUntil('\r');
    //    Serial.println(result);
  }
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  Serial.println();
  Serial.println("closing connection...");
  return result;
}
// Method for creating an ContentInstance(CI) resource on the remote CSE under a specific CNT (this is done by sending a POST request)
// param : ae --> the targted AE name (should be unique under the remote CSE)
// param : cnt  --> the targeted CNT name (should be unique under this AE)
// param : ciContent --> the CI content (not the name, we don't give a name for ContentInstances)
String createCI(String ae, String cnt1, String cnt2, String ciContent) {
  String ciRepresentation =
    "{\"m2m:cin\": {"
    "\"con\":\"" + ciContent + "\""
    "}}";
  return doPOST("/" + CSE_NAME + "/" + ae + "/" + cnt1 + "/" + cnt2, TY_CI, ciRepresentation);
}
void init_WiFi() {
  Serial.println("Connecting to  " + String(WIFI_SSID) + " ...");
  WiFi.persistent(false);
  WiFi.begin(WIFI_SSID, WIFI_PSWD);
  // wait until the device is connected to the wifi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(WIFI_DELAY);
    Serial.print(".");
  }
  // Connected, show the obtained ip address
  Serial.println("WiFi Connected ==> IP Address = " + WiFi.localIP().toString());
}
void init_HTTPServer() {
  server.begin();
  Serial.println("Local HTTP Server started !");
}

  // ############################################################### //
  // ######### CODE FOR THE SENSOR ######### //
  // ###############################################################  //
int data = 0;
int smokeA0 = A0; // smoke sensor connected with analog pin A1 of the arduino / mega.

void setup() {
  // intialize the serial liaison
  Serial.begin(SERIAL_SPEED);
  init_WiFi();// Connect to WiFi network
  init_HTTPServer(); // Start HTTP server
  
  // ######### USE THIS SPACE FOR YOUR SETUP CODE ######### //
  pinMode(smokeA0, INPUT);
}

void loop() {
  // ############################################################### //
  // ######### USE THIS SPACE FOR YOUR SENSOR POLING CODE  ######### //
  // ###############################################################  //
  data = analogRead(smokeA0); 
  Serial.print("Smoke: "); 
  Serial.println(data); 
  // ################################################################### //
  // ######### USE THIS SPACE FOR YOUR SENDING DATA TO SERVER  ######### //
  // ################################################################### //
  
  ////// Storing as a string in a single containers///////
    String sensor_value_string;
    sensor_value_string = String(data);
    createCI("Smart_Monitoring", "NodeMCU2", "node_data", sensor_value_string);
  // Check if the data instance was created.
  delay(5000);
}
