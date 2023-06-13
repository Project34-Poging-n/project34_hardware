int ledPin = 13; 
char incomingData; 

void setup() {
  Serial.begin(9600); 
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) { // check if data is available on the serial port
    incomingData = Serial.read(); // read the incoming data

    // do something with the incoming data
    if (incomingData == 'Aan') { 
      digitalWrite(ledPin, HIGH); 
      Serial.println("LED turned on"); 
    } else if (incomingData == 'Uit') {
      digitalWrite(ledPin, LOW); 
      Serial.println("LED turned off"); 
    }
  }
}
