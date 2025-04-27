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
  irsend.sendLG2(0x8800909, 28);  
  Serial.println("Sent Turn On");  
  delay(5000);  
  irsend.sendLG2(0x88C0051, 28);  
  Serial.println("Sent Turn Off"); 
  delay(5000);    
}
