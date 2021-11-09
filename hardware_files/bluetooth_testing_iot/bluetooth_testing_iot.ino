//#include<SoftwareSerial.h>
//
//const int ledPin = 13; // the pin that the LED is attached to
//int incomingByte;      // a variable to read incoming serial data into
//
///* Create object named bt of the class SoftwareSerial */ 
//SoftwareSerial bt(2,3); /* (Rx,Tx) */  
//
//void setup() {
//  bt.begin(9600); /* Define baud rate for software serial communication */
//  Serial.begin(9600); /* Define baud rate for serial communication */
//  pinMode(ledPin, OUTPUT);
//
//}
//
//void loop() {
//  
//    if (bt.available()) /* If data is available on serial port */
//    {
////      incomingByte = bt.read();
//     Serial.write(bt.read()); /* Print character received on to the serial monitor */
////    if (incomingByte =='H') {
////      digitalWrite(ledPin, HIGH);
////    }
////    if (incomingByte == 'L') {
////      digitalWrite(ledPin, LOW);
////    }
////    
//    }
//}




#include<SoftwareSerial.h>

/* Create object named bt of the class SoftwareSerial */ 
SoftwareSerial bt(2,3); /* (Rx,Tx) */  

void setup() {
  bt.begin(9600); /* Define baud rate for software serial communication */
  Serial.begin(9600); /* Define baud rate for serial communication */
}

void loop() {
  
    if (bt.available()) /* If data is available on serial port */
    {
     Serial.println(bt.read()); /* Print character received on to the serial monitor */
    }
}
