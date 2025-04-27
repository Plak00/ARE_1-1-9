#include <IRremoteESP8266.h>
#include <IRsend.h>

IRsend irsend(4);  

void setup() {
  Serial.begin(115200);  
  irsend.begin();
  
  Serial.println("Waiting 5 seconds before sending...");
  for (int i = 1; i <= 5; i++) {
    Serial.print(i);
    Serial.println("...");
    delay(1000);
  }
}

void loop() {
  irsend.sendNEC(0x2FD48B7, 32);  
  Serial.println("Sent");  
  delay(5000);  
}
