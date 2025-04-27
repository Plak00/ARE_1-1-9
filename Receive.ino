#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

#define IR_RECEIVE_PIN 35  

IRrecv irrecv(IR_RECEIVE_PIN);
decode_results results;

void setup() {
    Serial.begin(115200);
    irrecv.enableIRIn();  
    Serial.println("IR Receiver Ready...");
}

void loop() {
    if (irrecv.decode(&results)) {
        Serial.println(resultToHumanReadableBasic(&results)); 
        irrecv.resume();  
    }
}
