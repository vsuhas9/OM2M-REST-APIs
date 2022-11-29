///////////////////////////////Including the required Header files//////////////////////////////////////////////////////////
#include <WiFiClientSecure.h>
#include <WiFiClient.h>
#include<ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>


//Include the required sensor header files below this line///////////////////////////////////////////////////////////////////




/////////////////////////Defining the constants and creating required objects and functions//////////////////////////////////

#define MAIN_SSID "suhas"
#define MAIN_PASS "1234567890"

#define CSE_IP      "192.168.19.225"
#define CSE_PORT    8282
#define HTTPS     false
#define OM2M_ORGIN    "admin:admin"
#define OM2M_MN     "/~/mn-cse/mn-name/"
#define OM2M_AE_0     "LAMP_0"
#define OM2M_AE_1     "LAMP_1"
#define OM2M_DATA_CONT  "DATA"
#define LISTENER_PORT  8000

WiFiServer listener(LISTENER_PORT);
HTTPClient http;
int send_req();
bool connect_http();
int post_request(String req);

//////////////////////////Define the sensors global variables below this line//////////////////////////////////////////////

#define LED1 14
#define LED2 15


 
/////////////////////////////Void Setup/////////////////////////////////////////////////////////////////////////////////////
void setup() {
  
      Serial.begin(115200);
      Serial.println("Connecting to "+String()+MAIN_SSID);
     WiFi.begin(MAIN_SSID, MAIN_PASS);
  while( WiFi.status() != WL_CONNECTED) {
    Serial.print("#");
    delay(500);
    // don't do anything else:
    
  }
      Serial.println("COnnection Successful");
      listener.begin();
      Serial.println("ESP listener started");
      Serial.println(WiFi.localIP());
      delay(500);
//////Include the sensor setup segments here///////////////////////////////////////////////////////////////////////////////
pinMode(LED1,OUTPUT);
pinMode(LED2,OUTPUT); 
Serial.println("ESP Setup Complete");
}

void loop() {




///////////////////////////////////////////////////Receiving data from actuator////////////////////////////////////////////
listener.begin();
WiFiClient client = listener.available();
 String w=client.readString();
Serial.println(w);
int a=w.indexOf("false");
int b=w.indexOf("true");
int c=w.indexOf("LAMP_0");
int d=w.indexOf("LAMP_1");
////////////////////////////////////////////////Turning ON the LEDS based on received data/////////////////////////////////

if(b>0)
{
  if(c>0)
  {
  digitalWrite(LED1,HIGH);
  Serial.println("Light-1 ON");
  }
  else if(d>0)
  {  digitalWrite(LED2,HIGH);
    Serial.println("Light-2 ON");
  }
}
else if(a>0)
{
  if(c>0)
  {
  digitalWrite(LED1,LOW);
  Serial.println("Light-1 OFF");
  }
  else if(d>0)
  {  digitalWrite(LED2,LOW);
    Serial.println("Light-2 OFF");
  }
}


client.flush();

// Send HTTP response to the client
String s = "HTTP/1.1 200 OK\r\n";
client.print(s);
delay(100);


}
