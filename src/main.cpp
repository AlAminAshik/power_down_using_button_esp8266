#include <ESP8266WiFi.h>

const int led_pin = D6;  //led connected to this pin
const int BUTTON_PIN = D2;   // GPIO where the button is connected
const int CH_PD_PIN = D1;    // Connects to CH_PD (optional if directly controlled)


  void setup() {
    pinMode(BUTTON_PIN, INPUT_PULLUP); // Button with pull-up
    pinMode(CH_PD_PIN, OUTPUT);  // sets D1 to an output which will pull the transistor on
    digitalWrite(CH_PD_PIN, HIGH);
    delay(3000);
    digitalWrite(CH_PD_PIN, LOW);  // latches the transistor to keep device on

    pinMode(led_pin, OUTPUT);  // sets GPIO 2 to an input so we can read the PIR output state
  }

 void loop() {
  if(digitalRead(BUTTON_PIN) == LOW) {
    digitalWrite(led_pin, HIGH);  // sets GPIO 2 to high (this is the PIR record)
    delay(1000);
    digitalWrite(led_pin, LOW);  // sets GPIO 2 to low (this is the PIR record)
    delay(1000);
  }
  else{
   digitalWrite(led_pin, HIGH);  // sets GPIO 2 to high (this is the PIR record)
   delay(1000);
   digitalWrite(led_pin, LOW);  // sets GPIO 2 to low (this is the PIR record)
   delay(1000);
   }
 }