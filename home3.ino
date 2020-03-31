#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>


char* ssid = "helloo";
char* password = "<*****>";
String room_light = "0";
IPAddress ipa(192, 168, 0, 109);
IPAddress gettw(192,168,0,1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(8, 8, 8, 8);  

ESP8266WebServer server; //server variable

void setup() {
  initializePin(); 
  WiFi.config(ipa,gettw,subnet,dns);
  WiFi.begin(ssid, password);
  Serial.begin(115200);
  Serial.print("Searching Connection");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.print(WiFi.localIP());
  
  serverSection();
}

void loop() {
  server.handleClient();
}

void initializePin(){
  
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
}

void serverSection(){
  server.on("/", []() {
    server.send(200, "text/html", "<!DOCTYPE html><html><meta charset='UTF-8'><head>Customise</head><body><h2>Amil Room</h2><h3><a href='/on'>Room Light</a><br></body></html>");
  });

  server.on("/on", room_light_state);
  server.on("/status", all_state);
  
  server.begin();
}

void room_light_state(){
  if(room_light == "0"){
    room_light = "1";
    digitalWrite(D1, HIGH);
    server.send(200, "text/html", room_light);
  }else{
    room_light = "0";
    digitalWrite(D1, LOW);
    server.send(200, "text/html", room_light);
  }
}

void all_state(){
  
 // server.send(200, "text/html", "{'rl':'"+room_light+"','ml':'"+mirror_light+"','bl':'"+bed_light+"','fan':'"+fan+"'}");
 server.send(200, "text/html", "{'rl':'"+room_light+"'}");

}

 
