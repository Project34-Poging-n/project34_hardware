
#include "Adafruit_Thermal.h" 

#include "SoftwareSerial.h"
#define TX_PIN A3 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN A4 // Arduino receive   GREEN WIRE   labeled TX on printer
String data = "";
SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor
void setup() {
   pinMode(7, OUTPUT);
   digitalWrite(7, LOW);

  // NOTE: SOME PRINTERS NEED 9600 BAUD instead of 19200, check test page.
  //use baud 9600!!!!
  mySerial.begin(9600);  // Initialize SoftwareSerial
  Serial.begin(9600);
  //Serial1.begin(19200); // Use this instead if using hardware serial
  printer.begin();  
   
}
//test functie
//void print(){
//  printer.justify('C');
//  printer.setSize('M');
//  printer.print(F("Kopie Kaarthouder"));
//  printer.setSize('L');        // Set type size, accepts 'S', 'M', 'L'
//  printer.print(F("Naam bank"));
//  printer.justify('L');
//  printer.setSize('S');
//  printer.print(F("Wijnhaven 107"));
//  printer.print(F("Datum: "));
//  printer.print(F("Tijd: "));
//  printer.print(F(" "));
//  printer.print(F("Bedrag: "));
//  printer.print(F("Pas Nummer: "));
//  printer.print(F(""));
//  printer.setSize('L');
//  printer.justify('C');
//  printer.print(F("Bedankt en tot ziens"));
//  
//}

void asciiToString(int asciiNumber, String& outputString) {
  outputString = String(asciiNumber);
}


void loop() {
  while(data != "Stop"){
    asciiToString(data, outputString);
    if(data != "-1"){

    printer.println(outputString);
    Serial.print(outputString);
    }
  }

}
