#include <WiFi.h>

#define MAIN_SSID "suhas"
#define MAIN_PASS "1234567890"

#define LISTENER_PORT  8000

WiFiServer listener(LISTENER_PORT);

#define LED1 4
#define LED2 14

void setup()
{
    Serial.begin(115200);
    WiFi.begin(MAIN_SSID, MAIN_PASS);
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("#");
  }
   Serial.println("Connection Successful");
  
   listener.begin();
   Serial.println("ESP listener started");
  
   Serial.println("Ip Address is");
   Serial.println(WiFi.localIP());
   
   delay(500);

   pinMode(LED1,OUTPUT);
     pinMode(LED2,OUTPUT);
}
void loop(){
WiFiClient client = listener.available();
if(client){
  #define LISTEN  8000
 String w=client.readString();
Serial.println(w);
int a=w.indexOf("false");
int b=w.indexOf("true");
int c=w.indexOf("LAMP_0");
int d=w.indexOf("LAMP_1");

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

}
delay(100);
}
