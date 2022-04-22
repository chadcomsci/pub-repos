#include <WiFi.h> // ESP32 WiFi Library

void connect_wifi();
void check_and_reconnect();

const char* ssid = ""; // Wifi SSID
const char* password = ""; //Wi-FI Password

const int RATE = 9600;
const int WIFI_WAIT_CONN_DELAY = 500;

unsigned long previousMillis = 0;
unsigned long interval = 30000;

void connect_wifi(){

  // static information
  IPAddress local_IP(192, 168, 1, 111);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 0, 0);
  IPAddress primaryDNS(8, 8, 8, 8);   //optional
  IPAddress secondaryDNS(8, 8, 4, 4); //optional
  
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }

  // Connect to local WiFi
  WiFi.begin(ssid, password);
  Serial.begin(RATE);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(WIFI_WAIT_CONN_DELAY);
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); // Print local IP address
}

void check_and_reconnect(){
  unsigned long currentMillis = millis();
  // if WiFi is down, try reconnecting
  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >=interval)) {
    Serial.print(millis());
    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.reconnect();
    previousMillis = currentMillis;
  }
}