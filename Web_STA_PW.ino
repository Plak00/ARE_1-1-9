#include <WiFi.h>
#include <WebServer.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

#define IR_PIN 4
IRsend irsend(IR_PIN);

WebServer server(80); // Create Web Server

const char* ssid = "___";        // Change this to your WiFi SSID
const char* password = "___"; // Change this to your WiFi password

// LG AC IR Codes
uint32_t AC_ON = 0x8800909;
uint32_t AC_OFF = 0x88C0051;

// Toshiba TV IR Code
uint32_t TV_ON_OFF = 0x2FD48B7;

void setup() {
  Serial.begin(115200);
  irsend.begin();

  // Connect to Wi-Fi in STA Mode
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("🔄 Connecting to WiFi...");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\n✅ Connected to WiFi!");
  Serial.print("📡 ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  // Web Server Routes
  server.on("/", HTTP_GET, handleRoot);
  server.on("/ac_on", HTTP_GET, sendAcOn);
  server.on("/ac_off", HTTP_GET, sendAcOff);
  server.on("/tv_on_off", HTTP_GET, sendTvOnOff);

  server.begin();  // Start the web server
  Serial.println("🌐 Web Server Started!");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String html = "<html><head>"
                "<meta name='viewport' content='width=device-width, initial-scale=1'>"
                "<style>"
                "body { font-family: Arial, sans-serif; text-align: center; background-color: #f0f0f0; }"
                "h2 { color: #333; }"
                ".button {"
                "  display: inline-block; padding: 20px 40px; margin: 15px; font-size: 24px; color: white;"
                "  background-color: #007bff; border: none; border-radius: 10px; cursor: pointer;"
                "  transition: 0.3s; }"
                ".button:hover { background-color: #0056b3; }"
                "</style>"
                "<script>"
                "function sendCommand(command) {"
                "  fetch(command).then(response => response.text()).then(text => {"
                "    document.getElementById('status').innerText = text;"
                "  });"
                "}"
                "</script>"
                "</head><body>"
                "<h2>ESP32 IR Remote Control</h2>"
                "<p>LG Air Conditioner</p>"
                "<button class='button' onclick='sendCommand(\"/ac_on\")'>AC ON</button>"
                "<button class='button' onclick='sendCommand(\"/ac_off\")'>AC OFF</button>"
                "<p>Toshiba TV</p>"
                "<button class='button' onclick='sendCommand(\"/tv_on_off\")'>TV ON/OFF</button>"
                "<p id='status'>Status: Ready</p>"
                "</body></html>";

  server.send(200, "text/html", html);
}

void sendAcOn() {
  irsend.sendLG2(AC_ON, 28);
  Serial.println("Sent: LG AC ON");
  server.send(200, "text/plain", "LG AC ON Sent ✅");
}

void sendAcOff() {
  irsend.sendLG2(AC_OFF, 28);
  Serial.println("Sent: LG AC OFF");
  server.send(200, "text/plain", "LG AC OFF Sent ✅");
}

void sendTvOnOff() {
  irsend.sendNEC(TV_ON_OFF, 32);
  Serial.println("Sent: Toshiba TV ON/OFF");
  server.send(200, "text/plain", "Toshiba TV ON/OFF Sent ✅");
}
