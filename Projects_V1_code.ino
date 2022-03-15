//BT Setup
#include <SoftwareSerial.h>
SoftwareSerial HM10(0, 1); // RX = 0, TX = 1
char appData;  
String inData = "";
  
//Sensor Setup
int TMP36OutputPin = 7; //This reads the TMP36 ouput
float Temperture; // Double command can be used here depends on how percise TMP36 is
float TMP36Voltage;
int Min;
int Max;
int Analog;
unsigned long Sum;
unsigned long Average;

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
#define echoPin 8 // attach pin D8 Arduino to pin Echo of HC-SR04
#define trigPin 7 //attach pin D7 Arduino to pin Trig of HC-SR04


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Default port used
  
  //BT Setup
  Serial.println("HM10 serial started at 9600");
  HM10.begin(9600); // set HM10 serial at 9600 baud rate
  
  //Pin Setup
 pinMode(3, OUTPUT);    // sets the digital pin 3 as output
 pinMode(4, OUTPUT);    // sets the digital pin 4 as output
  
 pinMode(5, OUTPUT);    // sets the digital pin 5 as output
 pinMode(6, OUTPUT);    // sets the digital pin 6 as output

  //SR04 Setup
 pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
 pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
 Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
 Serial.println("with Arduino Nano");

//Bluetooth Setup
  mySerial.begin(9600)
    pinMode(ledpin, OUTPUT)
}

  



void loop() {
  // put your main code here, to run repeatedly:

  //Temperture Sensor Code
  delay(1000);
  int TMP36Value = analogRead(TMP36OutputPin); // Reads TMP36 output and stores value
  TMP36Voltage = TMP36Value * 5;
  TMP36Voltage = TMP36Voltage / 1024;
  Temperture = (TMP36Voltage - 0.5) * 100; // Equation to convert to temeprture
  Serial.print("Current Temperature: ");
  Serial.println(Temperture);
  Serial.print("    TMP36 Voltage: ");
  Serial.print(TMP36Voltage);
  Serial.print("   TMP36Value: ");
  Serial.println(TMP36Value);

  //digitalWrite(3, HIGH); // Used to test LED
  //digitalWrite(4, HIGH); // Used to test LED


  //If statment. If temperture is greater than 24 Relay will come on

  if ( Temperture > 23.00 && (distance < 50) )
  {
    digitalWrite(5, HIGH); //write digital pin 3 high
    digitalWrite(6, HIGH); //write digital pin 4 high
   // digitalWrite(3, HIGH); //write digital pin 3 high so green led turns on
   // digitalWrite(4, HIGH) ; //write digital pin 4 high so red led turns on
  }
  //If temperture is lower than 24 relays get no power
  else {
    digitalWrite(5, HIGH); //if it isn't higher than 512, make pin 3 low
    digitalWrite(6, HIGH); //if it isn't higher than 512, make pin 4 low
   // digitalWrite(3, LOW); //write digital pin 3 high so green led turns off
   // digitalWrite(4, LOW); //write digital pin 4 high so red led turns off
  }
  //////////////////////////////////////////////
  //////////////////////////////////////////////

  //Ultrasonic sensor code
delay(1000);
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  //Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite( trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  //Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  Serial.println("");
  //Ultrasonic sensor code
  
  //Bluetooth code
 {
  HM10.listen();  // listen the HM10 port
  while (HM10.available() > 0) {   // if HM10 sends something then read
    appData = HM10.read();
    inData = String(appData);  // save the data in string format
    Serial.write(appData);
  }

 
  if (Serial.available()) {           // Read user input if available.
    delay(10);
    HM10.write(Serial.read());
  }
  if ( inData == "1") {
    Serial.println("LED OFF");
    digitalWrite(3, LOW); // switch OFF LED
    digitalWrite(4, HIGH); // switch OFF LED
    delay(500);
  }
  if ( inData == "2") {
    Serial.println("LED ON");
    digitalWrite(3, HIGH); // switch OFF LED
    digitalWrite(4, LOW); // switch OFF LED
    delay(500);
  }
  if (inData == "3"){
    Serial.println("LED FLASH TEST");
   digitalWrite(3, HIGH); // switch OFF LED
   digitalWrite(4, LOW); // switch OFF LED
   
   delay(100);
    digitalWrite(4, HIGH); // switch OFF LED
    digitalWrite(3, LOW); // switch OFF LED
    delay(100);
}
if ( inData == "4") {
    Serial.println("PINS SET TO LOW");
    digitalWrite(3, LOW); // switch OFF LED
    digitalWrite(4, LOW); // switch OFF LED
    delay(500);
  }
  
}
  
