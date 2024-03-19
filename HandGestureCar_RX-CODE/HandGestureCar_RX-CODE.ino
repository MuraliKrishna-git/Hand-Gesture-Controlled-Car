//Library Needed
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//Motor Connection to The Digital pins
int enA = 0;  
int Motor1 = 3;
int Motor2 = 4;
int enB = 1;  
int Motor3 = 5;
int Motor4 = 6;

RF24 radio(9,10); // CE, CSN Connection in Digital Pins
const byte address[6] = "00001";
char receivedData[32] = "";
int  xAxis, yAxis=0;
int joystick[2]; 
int joystick0,joystick1=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(Motor1, OUTPUT);
  pinMode(Motor2, OUTPUT);
  pinMode(Motor3, OUTPUT);
  pinMode(Motor4, OUTPUT);

  //Set NRF24l01 to Receiver Mode 
  radio.begin();
  radio.openReadingPipe(1, address);
   radio.setDataRate(RF24_250KBPS);
   //radio.setPayloadSize(sizeof(joystick));
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();

  //Initial state of the Motors
  digitalWrite(Motor1, 0);
  digitalWrite(Motor2, 0);
  digitalWrite(Motor3, 0);
  digitalWrite(Motor4, 0);
  delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  
if (radio.available()) {   // If the NRF240L01 module received data
     
    radio.read( &joystick0, sizeof(joystick0) );
    radio.read( &joystick1, sizeof(joystick1) );
    Serial.println(joystick0);
    Serial.println(joystick1);

    xAxis = joystick0;
    yAxis = joystick1;

  //Turn left  
  if ( yAxis > 30 & yAxis < 90) {

  digitalWrite(Motor1, HIGH);
  digitalWrite(Motor2, LOW);
  digitalWrite(Motor3, LOW);
  digitalWrite(Motor4, HIGH);     
    
  }

  //Turn Right
  else if (yAxis > 260 & yAxis < 330) {

  digitalWrite(Motor1, LOW);
  digitalWrite(Motor2, HIGH);
  digitalWrite(Motor3, HIGH);
  digitalWrite(Motor4, LOW);  
    
  }
  
 //Move Backward
 else if (xAxis > 30 & xAxis < 90) {
  
  digitalWrite(Motor1, LOW);
  digitalWrite(Motor2, HIGH);
  digitalWrite(Motor3, LOW);
  digitalWrite(Motor4, HIGH);  
    
  }



  //Move Forward
  else if (xAxis > 260 & xAxis < 335) {

  digitalWrite(Motor1, HIGH);
  digitalWrite(Motor2, LOW);
  digitalWrite(Motor3, HIGH);
  digitalWrite(Motor4, LOW);  
  

}

  //Stop Moving
  else {

  digitalWrite(Motor1, LOW);
  digitalWrite(Motor2, LOW);
  digitalWrite(Motor3, LOW);
  digitalWrite(Motor4, LOW);  
}
    
    Serial.print("xAxis:");
    Serial.println(xAxis);
    delay(1000);
    Serial.print("yAxis:");
    Serial.println(yAxis);
    delay(1000);
    
}
  //If The Receiver Does not Connect to the Transmitter
  else {

  digitalWrite(Motor1,LOW);
  digitalWrite(Motor2, LOW);
  digitalWrite(Motor3, LOW);
  digitalWrite(Motor4, LOW);  
  
  Serial.println("Not Connected!");
  delay(1000);  
    }
}
