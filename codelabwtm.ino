//Codelab WTMSSA 2017 -- Danielle & Tuane
#include <ESP8266WiFi.h>
 
const char* ssid = "Danielle";
const char* password = "12345678";
 
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  // preparando a porta GPIO2
  pinMode(4, OUTPUT);
  digitalWrite(4, 0);
 
  pinMode(5, OUTPUT);
  digitalWrite(5, 0);
 
  // Connectando no WiFi 
  Serial.println();
  Serial.println();
  Serial.print("Conectado no WIFI !!! ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi conectado");
 
  // Startando o servidor
  server.begin();
  Serial.println("Servidor startado");
  Serial.println(WiFi.localIP());
}
 
void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  Serial.println("cliente identificado");
  while(!client.available()){
    delay(1);
  }
 
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
 
  String buf = "";
 
  buf += "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n";
  buf += "<html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>\r\n";
  buf += "<title>Codelab Internet das Coisas com Node MCU - WTMSSA 2017</title>";
  buf += "<style>.c{text-align: center;} div,input{padding:5px;font-size:1em;} input{width:80%;} body{text-align: center;font-family:verdana;} button{border:0;border-radius:0.3rem;background-color:#FF1493;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;} .q{float: right;width: 64px;text-align: right;}</style>";
  buf += "</head>";
  buf += "<h3>ESP8266 Web Service - </h3>";
  buf += "<p>GPIO4 <a href=\"?function=led4_on\"><button>ON</button></a> <a href=\"?function=led4_off\"><button>OFF</button></a></p>";
  buf += "<p>GPIO5 <a href=\"?function=led5_on\"><button>ON</button></a> <a href=\"?function=led5_off\"><button>OFF</button></a></p>";
  buf += "<h4>WTMSSA 2017 - Codelab Danielle & Tuane </h4>";
  buf += "</html>\n";
 
  client.print(buf);
  client.flush();
 
  if (req.indexOf("led5_on") != -1)
    digitalWrite(5, 1);
  else if (req.indexOf("led5_off") != -1)
    digitalWrite(5, 0);
  else if (req.indexOf("led4_on") != -1)
    digitalWrite(4, 1);
  else if (req.indexOf("led4_off") != -1)
    digitalWrite(4, 0);
  else {
    Serial.println("Requisicao Invalida");
    client.stop();
  }
  Serial.println("Cliente Desconectado");
}
