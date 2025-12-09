#include <ESP8266WiFi.h>

const char* ssid     = "ESP01_PWM";
const char* password = "12345678";

WiFiServer server(80);
const int pwmPin = 2;

void setup() {
  pinMode(pwmPin, OUTPUT);
  analogWrite(pwmPin, 0);
  
  WiFi.softAP(ssid, password);
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) return;

  String req = client.readStringUntil('\n');

  // Tangani request: /set?val=NNN
  if (req.indexOf("/set?val=") != -1) {
    int pos = req.indexOf("val=") + 4;
    int pwm = req.substring(pos).toInt();
    pwm = constrain(pwm, 0, 1023);
    analogWrite(pwmPin, pwm);

    client.print("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nPWM=");
    client.print(pwm);
    client.println();
    return;
  }

  // Response untuk selain /set
  client.print("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
  client.println("Gunakan: /set?val=0-1023");
}
