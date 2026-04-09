#include <ESP8266WiFi.h> 

const char* ssid     = "ESP01_PWM";
const char* password = "12345678";

WiFiServer server(80);
const int pwmPin = 2;

int pwmValue = 0;
int pwmFreq = 1000; // default 1 kHz

void setup() {
  pinMode(pwmPin, OUTPUT);

  analogWriteFreq(pwmFreq);   // set frekuensi awal
  analogWrite(pwmPin, pwmValue);
  
  WiFi.softAP(ssid, password);
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (!client) return;

  String req = client.readStringUntil('\n');

  // ===== SET PWM =====
  if (req.indexOf("/set?val=") != -1) {
    int pos = req.indexOf("val=") + 4;
    int pwm = req.substring(pos).toInt();
    pwm = constrain(pwm, 0, 1023);

    pwmValue = pwm;
    analogWrite(pwmPin, pwmValue);

    client.print("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nPWM=");
    client.print(pwmValue);
    client.println();
    return;
  }

  // ===== SET FREKUENSI =====
  if (req.indexOf("/freq?val=") != -1) {
    int pos = req.indexOf("val=") + 4;
    int freq = req.substring(pos).toInt();

    // batas aman ESP8266
    freq = constrain(freq, 100, 5000);

    pwmFreq = freq;
    analogWriteFreq(pwmFreq);

    // apply ulang duty
    analogWrite(pwmPin, pwmValue);

    client.print("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nFREQ=");
    client.print(pwmFreq);
    client.println();
    return;
  }

  // ===== DEFAULT RESPONSE =====
  client.print("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
  client.println("Gunakan:");
  client.println("/set?val=0-1023");
  client.println("/freq?val=100-5000");
}
