#include <HTTPClient.h>
#include <WiFi.h>
#define RXp2 16
#define TXp2 17

const char* SSID     = "";
const char* PASSWORD = "";
const char* URL = "http://climaticatech-api.us-east-2.elasticbeanstalk.com/api/esp-data";
const char* API_KEY = "";

void setup() {
 Serial.begin(115200);
 Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);

 connectWiFi();
}

void loop() {
  if(WiFi.status() != WL_CONNECTED)
    connectWiFi();
  
  String msgRecebida = "";
  while(msgRecebida.isEmpty()) {
    msgRecebida = Serial2.readString();
  }
  
  String umidade;
  String temperatura;
  String luminosidade;

  stringSplit(msgRecebida, &umidade, &temperatura, &luminosidade);

  HTTPClient http;

  http.begin(URL);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("X-API-KEY", API_KEY);

  String postData = "{\"umidade\":\"" + umidade + "\", \"temperatura\":\"" + temperatura + "\", \"luminosidade\":\"" + luminosidade + "\"}";

  int httpCode = http.POST(postData);
  String payload = http.getString();

  printInfo(umidade, temperatura, luminosidade, httpCode, payload);
}

void connectWiFi() {
  WiFi.mode(WIFI_OFF);
  delay(1000);
  
  WiFi.mode(WIFI_STA);
  
  WiFi.begin(SSID, PASSWORD);
  Serial.print("Connecting to WiFi");
  
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
    
  Serial.println("\nconnected to : " + String(SSID));
  Serial.print("IP address: "); Serial.println(WiFi.localIP());
}

void stringSplit(String m, String* umidade, String* temperatura, String* luminosidade) {
  char* p;
  char msg[m.length() + 1];
  p = strtok(strcpy(msg, m.c_str()), ",");
  
  int i = 0;
  while(p != NULL && p != "\n") {
    String s = p;

    switch(i) {
      case 0:
        *umidade = s;
        break;
      case 1:
        *temperatura = s;
        break;
      case 2:
        *luminosidade = s;
        break;
    }

    p = strtok(NULL, ",");
    i++;
  }
}

void printInfo(String umidade, String temperatura, String luminosidade, int httpCode, String payload) {
  Serial.printf("Dados: Umidade: %s%%     Temperatura: %s *C     Luminosidade: %s%%\n", umidade, temperatura, luminosidade);
  Serial.printf("URL : %s\n", URL);
  Serial.printf("httpCode: %d\n", httpCode); 
  Serial.println("payload : " + String(payload));
  Serial.println("--------------------------------------------------");
}