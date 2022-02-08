#include <Servo.h>    //the library which helps us to control the servo motor
#include <SPI.h>      //the communication interface with the modem
#include "RF24.h"     //the library which helps us to control the radio modem
#include <Adafruit_PWMServoDriver.h>

RF24 radio(9,10);     /* 9 and 10 CE and CSN are connected.*/

const uint64_t pipe = robot15772sLandis; //the address of the modem,that will receive data from the Arduino.

int msg[6];

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define MIN_PULSE_WIDTH 650
#define MAX_PULSE_WIDTH 2350
#define DEFAULT_PULSE_WIDTH 1500
#define FREQUENCY 50

int pulseWidth(int angle){
int pulse_wide, analog_value;
pulse_wide = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
Serial.println(analog_value);
return analog_value;
}

void setup(){
Serial.begin(9600);
Serial.println("Robotics project /n Samuel Landis /n slandis@unm.edu");
pwm.begin();
pwm.setPWMFreq(FREQUENCY);  
radio.begin();                    //it activates the modem.
radio.openReadingPipe(1, pipe);   //determines the address of our modem which receive data.
radio.startListening();           //enable receiving data via modem
}

void loop(){
  if(radio.available()){
    bool done = false;
    while (!done){
    done = radio.read(msg, sizeof(msg));
    pwm.setPWM(5, 0, pulseWidth(msg[5]));
    pwm.setPWM(4, 0, pulseWidth(msg[4]));
    pwm.setPWM(3, 0, pulseWidth(msg[3]));
    pwm.setPWM(2, 0, pulseWidth(msg[2]));
    pwm.setPWM(1, 0, pulseWidth(msg[1]));
    pwm.setPWM(0, 0, pulseWidth(msg[0]));
    }
  }
}
