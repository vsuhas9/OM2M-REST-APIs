#include<HTTPClient.h>
#include <WiFi.h>
#include "time.h"

#define MAIN_SSID "ssid"
#define MAIN_PASS "password"

#define CSE_IP      "replace with system-ip"
#define CSE_PORT    5089
#define HTTPS     false
#define OM2M_ORGIN    "admin:admin"
#define OM2M_MN     "/~/in-cse/in-name/"
#define OM2M_AE     "AE-TEST"
#define OM2M_DATA_CONT  "Node-1/Data"

const char* ntpServer = "pool.ntp.org";
unsigned long epochTime; 
long randNumber;

HTTPClient http;

unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    //Serial.println("Failed to obtain time");
    return(0);
  }
  time(&now);
  return now;
}

void setup() {
Serial.begin(115200);
configTime(0, 0, ntpServer);
WiFi.begin(MAIN_SSID,MAIN_PASS);

while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("#");
  }
}

void loop() {
  epochTime = getTime();
  
  //Sensor Block  BME 
 static int i=0;

 float occupancy=random(0,2);
 float distance=random(0,400);
 
String data="[" + String(epochTime) + ", " + String(occupancy) + " , " + String(distance)+"]";

String server="http://" + String() + CSE_IP + ":" + String() + CSE_PORT + String()+OM2M_MN;

Serial.println(data);
http.begin(server + String() +OM2M_AE + "/" + OM2M_DATA_CONT + "/");

http.addHeader("X-M2M-Origin", OM2M_ORGIN);
http.addHeader("Content-Type", "application/json;ty=4");
http.addHeader("Content-Length", "100");

String label = "Node-1";

String req_data = String() + "{\"m2m:cin\": {"

  + "\"con\": \"" + data + "\","

  + "\"rn\": \"" + "cin_"+String(i++) + "\","

  + "\"lbl\": \"" + label + "\","

  + "\"cnf\": \"text\""

  + "}}";
int code = http.POST(req_data);
http.end();
Serial.println(code);
delay(1000);
}
