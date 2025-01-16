#include <ESP8266WiFi.h>

int led_pin = D6;  //led connected to this pin
#define BUTTON_PIN D3   // GPIO where the button is connected
#define CH_PD_PIN D1    // Connects to CH_PD (optional if directly controlled)


  void setup() {
    pinMode(BUTTON_PIN, INPUT_PULLUP); // Button with pull-up
    pinMode(CH_PD_PIN, OUTPUT);  // sets GPIO 2 to an input so we can read the PIR output state


    pinMode(led_pin, OUTPUT);  // sets GPIO 2 to an input so we can read the PIR output state
  }

 void loop() {
  static bool lastButtonState = HIGH;
  bool currentButtonState = digitalRead(BUTTON_PIN);


   digitalWrite(led_pin, HIGH);  // sets GPIO 2 to high (this is the PIR record)
   delay(1000);
   digitalWrite(led_pin, LOW);  // sets GPIO 2 to low (this is the PIR record)
   delay(1000);
   }