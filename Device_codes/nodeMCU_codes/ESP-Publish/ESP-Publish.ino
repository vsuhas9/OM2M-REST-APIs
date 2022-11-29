#include <ESP8266WiFi.h>

// WIFI params
const char* ssid = "xxxxxx";
const char* password = "xxxxxxx";

// CSE params
const char* host = "onem2m.iiit.ac.in";
const int httpPort = 443;
String url = "/~/in-cse/in-name/AE-AQ/Node-Name/Data";
int ty = 4;
const char* origin   = "AirPoll@20:22uHt@Sas";

void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  while( WiFi.status() != WL_CONNECTED) {
    Serial.print("#");
    delay(300);
    // don't do anything else:

}
}

void loop() {
 static int i=0;

 float time_random=random(20,148);
 float soil_moist=random(2,28);
 float temp=random(27,48);
 float rh=random(60,85);
 String con = "["+ String(time_random) + ", " + String(soil_moist) + ", " + String(temp) + ", " + String(rh)+ "]";
  
 String data = "{\"m2m:cin\": {"

  + String()  + "\"con\": \"" + con + "\","

  // + String()  + "\"rn\": \"" + "cin_"+ String() + String(i++) + "\","

  + String()  + "\"cnf\": \"text\""

  + String()  + "}}";

  WiFiClient client;
  delay(3000);
  
   if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    
    
  }
  else{
    String req = String()+"POST " + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "X-M2M-Origin: " + origin + "\r\n" +
               "Content-Type: application/json;ty="+ty+"\r\n" +
               "Content-Length: "+ data.length()+"\r\n"
               "Connection: close\r\n\n" + 
               data;

  Serial.println(req+"\n");

  // Send the HTTP request
  client.print(req);
               
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
     }

  }
    
    
    }
    

}
