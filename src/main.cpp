#include <ESP8266WiFi.h>
#include <Tiny4kOLED.h>

const int led_pin = D5;       //led connected to this pin (optional)
const int BUTTON_PIN = D7;    // GPIO where the button is connected //D8, D4 not suitable
const int CH_PD_PIN = D3;     // Connects to GPIO0 for triggering the mosfet

unsigned long previousMillis = 0;  // will store last time button has pressed

  void setup() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);  // Button with pull-up
    pinMode(CH_PD_PIN, OUTPUT);         // sets GPIO0 as an output which will pull the mosfet ON
    digitalWrite(CH_PD_PIN, HIGH);      // keep the mosfet off
    delay(4000);                        // wait for a defined delay time the device to boot up
    digitalWrite(CH_PD_PIN, LOW);       // latches the transistor to keep device on

    pinMode(led_pin, OUTPUT);           // sets D5 as an output to show button can be used for any other purpose
    oled.begin(128, 64, sizeof(tiny4koled_init_128x64br), tiny4koled_init_128x64br);
    oled.setOffset(2, 0); //the oled display is not centered, so we need to set an offset
    oled.clear();         //clear the display
    oled.on();            //turn on the display
    oled.setFont(FONT8X16P);  //set double font size
    oled.print("POWER ON"); //print the text
    delay(2000);            //wait for 2 seconds
    oled.clear();           //clear the display
  }

 void loop() {
  if(digitalRead(BUTTON_PIN) == LOW) {  //if button is pressed when device is active
    oled.setCursor(0, 0);
    oled.print("Button pressed ");
    digitalWrite(led_pin, HIGH);        // turns led on
    delay(500);
    digitalWrite(led_pin, LOW);         // turns led off
    delay(500);

    unsigned long currentMillis = millis(); // get the current time, so we can compare it with the previous time
    if(currentMillis - previousMillis > 5000) { //if button pressed for 5 seconds
      oled.clear();
      while(digitalRead(BUTTON_PIN) == LOW){    //while button is kept pressed
        oled.setCursor(0, 0);
        oled.print("Shutting down");            //print the text
        delay(2000);                            //show shutting down for 2 seconds
      }
      oled.clear();
      oled.off();
      digitalWrite(CH_PD_PIN, HIGH);            // turns the mosfet off and thus device off
    }
  }
  else{
    previousMillis = millis();  //if button is not pressed, store the current time
    oled.setCursor(0, 0);
    oled.print("Device is ready");
   }
 }