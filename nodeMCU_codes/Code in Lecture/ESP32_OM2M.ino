#include<HTTPClient.h>
#include <WiFi.h>

// header file
HTTPClient http;


//sensor object 

#define MAIN_SSID "suhas"
#define MAIN_PASS "1234567890"

#define CSE_IP      "192.168.93.225"
#define CSE_PORT    8080
#define HTTPS     false
#define OM2M_ORGIN    "admin:admin"
#define OM2M_MN     "/~/in-cse/in-name/"
#define OM2M_AE     "Test-AE"
#define OM2M_DATA_CONT  "Node-1/Data"

void setup() {
Serial.begin(115200);
WiFi.begin(MAIN_SSID,MAIN_PASS);


}

void loop() {

  
  //Sensor Block  DHT 
 static int i=0;
 float soil_moist=23;
 float temp=34;
 float rh=30;
 

 
String data="[" + String(temp) + " , " + String(rh)+ "]";

String server="http://" + String() + CSE_IP + ":" + String() + CSE_PORT + String()+OM2M_MN;


http.begin(server + String() +OM2M_AE + "/" + OM2M_DATA_CONT + "/");

http.addHeader("X-M2M-Origin", OM2M_ORGIN);
http.addHeader("Content-Type", "application/json;ty=4");
http.addHeader("Content-Length", "100");

String req_data = String() + "{\"m2m:cin\": {"

  + "\"con\": \"" + data + "\","

   + "\"rn\": \"" + "cin_"+String(i++) + "\","

  + "\"cnf\": \"text\""

  + "}}";
int code = http.POST(req_data);
http.end();
Serial.println(code);
delay(1000);
}
