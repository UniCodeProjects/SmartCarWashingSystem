#include <Arduino.h>

bool isHandshakeEnded = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  // while (!isHandshakeEnded) {
  //   String received = Serial.readStringUntil('\r');
  //   if (received.equals("HELLO ARDUINO")) {
  //     Serial.println("HELLO JAVA");
  //     isHandshakeEnded = true;
  //   }
  // }
  

  Serial.println("HELLO JAVA");
  delay(1000);
}
