#include <Arduino.h>
#include <wifi.h>

// put function declarations here:
const char* ssid = "Quyen Ngu";
const char* password = "Quyenoccho";

WiFiServer webServer(80);

unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print("Connecting to wifi");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address");
  Serial.println(WiFi.localIP());

  webServer.begin();
}

void loop() {
  WiFiClient webClient = webServer.available();

  if (webClient)
  {
    //khoi tao gia tri ban dau cho time
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New web Client")

    //bien luu gia tri response
    String currentTime = "";

    // neu co client connect va khong qua thoi gian time out
    while (webClient.connected() && currentTime - previousTime)
    {
      //doc gia tri timer tai thoi diem hien tai
      currentTime = millis();

      //neu client con connect
      if(webClient.available()){
        char c = webClient.read();
        Serial.write(c);
        header += c;     // luu gai tri vao header
        if(c == '\n'){
          if(currentLine.length() == 0){
            webClient.println("HTTP/1.1 200 OK");
            webClient.println("Content-type: text/html");
            webClient.println("Connection: close");
            webClient.println();
          }
        }
      }
    }
    webClient.stop();
    Serial.println("Client Disconnected");
    Serial.println("");
  }

  
  
}
