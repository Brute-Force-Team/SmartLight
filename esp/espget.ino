#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>
#include <string>
using namespace std;
/*
const char* ssid = "ESP";  // Enter SSID here
const char* password = "qwer1234";  //Enter Password here

IPAddress local_ip(192,168,43,250);
IPAddress gateway(192,168,43,1);
IPAddress subnet(255,255,255,0);
*/

const char* ssid = "nazik";
const char* password = "27092000f";


ESP8266WebServer server(80);

const char* host = "192.168.43.80";

void setup () {
 
 Serial.begin(115200);
// WiFi.softAP(ssid, password);
// WiFi.softAPConfig(local_ip, gateway, subnet);
 WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 server.on("/", Start);
 server.on("/N", OFF);
 server.on("/Y", ON);
 server.on("/D", DAT);
 server.on("/A", AUTO);
 
 server.on("/GET",HTTP_GET, [](){

  String CLRGBID=server.arg("text");
  sendOnBoard(CLRGBID);
  server.send(200,"text/plain","OK");
  }
 );
 /*
 server.on("/N", OFF);
 server.on("/N", OFF);
 server.on("/N", OFF);
 server.on("/N", OFF);
 server.on("/N", OFF);
 server.on("/N", OFF);
 server.on("/N", OFF);
 server.on("/N", OFF);
 server.on("/N", OFF);
 server.on("/N", OFF);
 server.on("/N", OFF);
 */
 server.begin();
}

void loop() {
  server.handleClient();
}
void sendOnBoard(String in)
{
 String temp = "";
 String comm = "LC";
  for (int i = 0; i < in.length(); ++i)
  {
    if (in[i] != '-') temp += in[i]; else
    {
      
      //++i;
      if (temp.length() == 1)
      {
        comm += temp;
      }
      else if (temp.length()==2)
      {
        int tint = (temp[0] - '0')*10+ (temp[1] - '0');
        char tchar = tint;
        comm += tchar;
      }
      else
      {
        int tint = (temp[0] - '0') * 100 + (temp[0] - '0') * 10 + (temp[1] - '0');
        char tchar = tint;
        comm += tchar;
      }
      temp = "";
    }
  }
  Serial.println(comm);
  }
void Start() {
  Serial.println("Y");
  server.send(200, "text/html", "");
}
void OFF() {
  Serial.println("N");
  server.send(200, "text/html", "");
}
void ON() {
  Serial.println("Y");
  server.send(200, "text/html", "");
}
void DAT() {
  Serial.println("D");
  server.send(200, "text/html", "");
}
void AUTO() {
  Serial.println("A");
  server.send(200, "text/html", "");
}

/*
void set_on(){
  Get();
  server.send(200, "text/html", "");
}
void Get() {

   
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {      /// подключаемся к серверу 
    Serial.println("D");
    return;
  }
   /// если подключились, отправляем чего от сервера хотим
              // сам GET запрос с ID и ключем
    client.println("/config");
              // говорим к какому хосту обращаемся (на сервере может быть несколько сайтов)
   // client.println("Host: api.openweathermap.org");
              // говорим что закончили
   // client.println("Connection: close");
    client.println();
 
  delay(1000);  // ждем немного 
                // читаем ответ и отправляем его в Serial
  while(client.available()){
   String line = client.readStringUntil('\r'); 
    Serial.print(line);
  }
 
  Serial.println();
}
*/
