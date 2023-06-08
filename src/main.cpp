#include <Arduino.h>
#include "cfop.h"

#define IN1 4
#define IN2 5

#define ENCA 0
#define ENCB 1

volatile int posi = 0; 
long prevT = 0;
float eprev = 0;
float eintegral = 0;
int pos = 0;
int maxPower = 255;
int target = 175;
//Cube rCube;
cfop algo;
int solveActive = 0;
void setMotor(int dir, int pwmVal);
void readEncoder();
int PID();
int move;
int poscount = 0;
void setup() {
  Serial.begin(9600);
  pinMode(ENCA,INPUT_PULLDOWN);
  pinMode(ENCB,INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(ENCA),readEncoder,RISING);
  
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  
  Serial.println("target pos");
 // rCube.shuffleCube();
 // rCube.printCube();

  target = 175;
  solveActive = false;
}

void loop() {
  
  if (solveActive == 0) {
   // algo.setCube(nullptr);
    algo.shuffleCube();
    algo.solveCube();
    solveActive = true;
  }
  else if (solveActive == 1) {
    if(!algo.solveQueue.empty()) {
    int i = 0;
    for (const std::string& value : algo.solveQueue) {
      if(value == "U") {
        Serial.println("Turning UP clockwise");
      }
      else if (value == "'U") {
        Serial.println("Turning UP counterclockwise");
      }
      else if (value == "D") {
        Serial.println("Turning DOWN clockwise");
      }
      else if (value == "'D") {
        Serial.println("Turning DOWN counterclockwise");
      }
      else if (value == "F") {
        Serial.println("Turning FRONT clockwise");
      }
      else if (value == "'F") {
        Serial.println("Turning FRONT counterclockwise");
      }
      else if (value == "L") {
        Serial.println("Turning LEFT clockwise");
      }
      else if (value == "'L") {
        Serial.println("Turning LEFT counterclockwise");
      }
      else if (value == "R") {
        Serial.println("Turning RIGHT clockwise");
      }
      else if (value == "'R") {
        Serial.println("Turning RIGHT counterclockwise");
      }
      else if (value == "B") {
        Serial.println("Turning BACK clockwise");
      }
      else if (value == "'B") {
        Serial.println("Turning BACK counterclockwise");
      }
      i++;
      if(i == algo.solveQueue.size()) {
        Serial.println("Done solving");
        solveActive = 2;
        break;
      }
    }
   }
  }
  else {

  }

}

void setMotor(int dir, int pwmVal) {
  
  if(dir == 1){
    digitalWrite(IN1,pwmVal);
    digitalWrite(IN2,LOW);
  }
  else if(dir == -1){
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,pwmVal);
  }
  else{
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
  }  
}

void readEncoder() {
  int b = digitalRead(ENCB);
  if(b > 0){
    posi++;
  }
  else{
    posi--;
  }
}

int PID() {
    
  // //set target position
  //int target = 170*sin(prevT/1e6);

  //PID constants
  //PID constants
  float kp = 0.1;
  float kd = 0.0;
  float ki = 0.01;

  // time difference
   long currT = micros();
   float deltaT = ((float) (currT - prevT))/( 1.0e6 );
   prevT = currT;

  //int pos = 0; 
     pos = posi;
  
  // error
  int e = pos - target;

  // derivative
  float dedt = (e-eprev)/(deltaT);

  // integral
  eintegral = eintegral + e*deltaT;

  // control signal
  float u = kp*e + kd*dedt + ki*eintegral;

  // motor power
  float pwr = fabs(u);
  if( pwr > maxPower ){
    pwr = maxPower;
  }

  // motor direction
  int dir = 1;
  if(u<0){
    dir = -1;
  }

  // signal the motor
  setMotor(dir,pwr);


  // store previous error
  eprev = e;
  return e;
}
