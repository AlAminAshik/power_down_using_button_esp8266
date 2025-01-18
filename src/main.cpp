#include <ESP8266WiFi.h>
#include <Tiny4kOLED.h>

const int led_pin = D5;  //led connected to this pin
const int BUTTON_PIN = D7;   // GPIO where the button is connected //D8, D4 not suitable
const int CH_PD_PIN = D4;    // Connects to CH_PD (optional if directly controlled) //must be D3

unsigned long previousMillis = 0;  // will store last time button has pressed

  void setup() {
    pinMode(BUTTON_PIN, INPUT_PULLUP); // Button with pull-up
    pinMode(CH_PD_PIN, OUTPUT);  // sets D1 to an output which will pull the transistor on
    digitalWrite(CH_PD_PIN, HIGH);
    delay(4000);
    digitalWrite(CH_PD_PIN, LOW);  // latches the transistor to keep device on

    pinMode(led_pin, OUTPUT);  // sets GPIO 2 to an input so we can read the PIR output state
    oled.begin(128, 64, sizeof(tiny4koled_init_128x64br), tiny4koled_init_128x64br);
    oled.setOffset(2, 0);
    oled.clear();
    oled.on();
    oled.setFont(FONT8X16P);  //set double font size
    oled.print("POWER ON");
    delay(2000);
    oled.clear();
  }

 void loop() {
  if(digitalRead(BUTTON_PIN) == LOW) {
    oled.setCursor(0, 0);
    oled.print("Button pressed ");
    digitalWrite(led_pin, HIGH);  // sets GPIO 2 to high (this is the PIR record)
    delay(500);
    digitalWrite(led_pin, LOW);  // sets GPIO 2 to low (this is the PIR record)
    delay(500);

    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis > 5000) {
      oled.clear();
      while(digitalRead(BUTTON_PIN) == LOW){
        oled.setCursor(0, 0);
        oled.print("Shutting down");
      }
      oled.clear();
      oled.off();
      digitalWrite(CH_PD_PIN, HIGH);  // turns the device off
    }
  }
  else{
    previousMillis = millis();
    oled.setCursor(0, 0);
    oled.print("Device is ready");
   }
 }