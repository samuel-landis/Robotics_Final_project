#include <SPI.h>     
#include "RF24.h"            

int msg[6]; 

int VRx1 = A0;
int VRy1 = A1;
int VRx2 = A2;
int VRy2 = A3;
int VRx3 = A4;
int VRy3 = A5;

int xPosition1 = 0;
int yPosition1 = 0;
int xPosition2 = 0;
int yPosition2 = 0;
int xPosition3 = 0;
int yPosition3 = 0;

int val_0 = 0;
int val_1 = 0;
int val_2 = 0;
int val_3 = 0;
int val_4 = 0;
int val_5 = 0;

RF24 radio(9,10);                     //9 and 10 are a digital pin numbers to which signals CE and CSN are connected.
                                      
const uint64_t pipe = 15772; 


void setup(void){
  Serial.begin(9600);
  Serial.println("Robotics project /n Samuel Landis /n slandis@unm.edu");
  pinMode(VRx1, INPUT);
  pinMode(VRy1, INPUT); 
  pinMode(VRx2, INPUT);
  pinMode(VRy2, INPUT);
  pinMode(VRx3, INPUT);
  pinMode(VRy3, INPUT);
  radio.begin();             
  radio.openWritingPipe(pipe); 
}

void loop(void){ 
  yPosition1 = analogRead(VRy1);
  Serial.println(yPosition1);
  val_0 = map(yPosition1, 630, 730, 170, 10);
  
  xPosition1 = analogRead(VRx1);
  val_1 = map(xPosition1, 520, 710, 170, 10);
  
  yPosition2 = analogRead(VRy2); 
  val_2 = map(yPosition2, 630, 730, 170, 10);
  
  xPosition2 = analogRead(VRx2);
  val_3 = map(xPosition2, 520, 710, 170, 10);
  
  yPosition3 = analogRead(VRy3); 
  val_4 = map(yPosition3, 630, 730, 170, 10);
  
  xPosition3 = analogRead(VRx3);
  val_5 = map(xPosition3, 520, 710, 170, 10);

  msg[0] = val_0;
  msg[1] = val_1;
  msg[2] = val_2;
  msg[3] = val_3;
  msg[4] = val_4;
  msg[5] = val_5;
  radio.write(msg, sizeof(msg));
}
