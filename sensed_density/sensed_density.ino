#include <Metro.h> // Include Metro library

// next:
// make it pick a random time each time so it's not steady. just diff by about 25 ms or something? rand?

// when motors should turn on once something is sensed
float sensorThreshold = 150; //100

// Define knobs (left to right)
const int proxApin = A0;    
unsigned long proxAvalue = 0; 
float proxAmapped = 0; 

const int proxBpin = A1;    
unsigned long proxBvalue = 0; 
float proxBmapped = 0; 

const int proxCpin = A2;    
unsigned long  proxCvalue = 0; 
float  proxCmapped = 0; 

const int  proxDpin = A3;    
unsigned long proxDvalue = 0; 
float proxDmapped = 0; 


// Set ideal pwm level
int off = 0;
int pwm = 255;

// Define motors pins (*8)
const int motor0 =  2; //2
const int motor1 =  3; //3
const int motor2 =  4; //7
const int motor3 =  5; //10
const int motor4 =  6; //x
const int motor5 =  7; //x
const int motor6 =  8; //x
const int motor7 =  9; //x

// Define motor states (*8)
int motor0State =  pwm;
int motor1State =  pwm;
int motor2State =  pwm;
int motor3State =  pwm;
int motor4State =  pwm;
int motor5State =  pwm;
int motor6State =  pwm;
int motor7State =  pwm;

// Set the active interval (same for all for now?)
float tA =  450;
float tB =  450;
float tC =  400;
float tD =  480;

// Set the rest interval (same for all for now?)
float tArest = 200;
float tBrest = 200;
float tCrest = 200;
float tDrest = 200;

// Instatiate metro object  (*8)
Metro metro0 =  Metro(tA); 
Metro metro1 =  Metro(tA); 
Metro metro2 =  Metro(tB); 
Metro metro3 =  Metro(tB); 
Metro metro4 =  Metro(tC); 
Metro metro5 =  Metro(tC); 
Metro metro6 =  Metro(tD); 
Metro metro7 =  Metro(tD); 


// how many times to do pattern before it reevaluates itself (way arbitrary)
// currently unused
int unitA = 5; 
int unitB = 5;
int unitC = 5; 
int unitD = 5;



void setup()
{
  // declare output pins
  pinMode(motor0,OUTPUT);
  pinMode(motor1,OUTPUT);
  pinMode(motor2,OUTPUT);
  pinMode(motor3,OUTPUT);
  pinMode(motor4,OUTPUT);
  pinMode(motor5,OUTPUT);
  pinMode(motor6,OUTPUT);
  pinMode(motor7,OUTPUT);
  //Serial.begin(9600);
}

void loop() {

  motorcontrol(metro0, motor0, motor0State, tA, tArest, unitA, proxApin, proxAvalue, proxAmapped);
  motorcontrol(metro1, motor1, motor1State, tA, tArest, unitA, proxApin, proxAvalue, proxAmapped);
  motorcontrol(metro2, motor2, motor2State, tB, tBrest, unitB, proxBpin, proxBvalue, proxBmapped);
  motorcontrol(metro3, motor3, motor3State, tB, tBrest, unitB, proxBpin, proxBvalue, proxBmapped);
  motorcontrol(metro4, motor4, motor4State, tC, tCrest, unitC, proxCpin, proxCvalue, proxCmapped);
  motorcontrol(metro5, motor5, motor5State, tC, tCrest, unitC, proxCpin, proxCvalue, proxCmapped);
  motorcontrol(metro6, motor6, motor6State, tD, tDrest, unitD, proxDpin, proxDvalue, proxDmapped);
  motorcontrol(metro7, motor7, motor7State, tD, tDrest, unitD, proxDpin, proxDvalue, proxDmapped);

}


void motorcontrol(Metro& metro, int motor, int &motorState, float t, float trest, int unit, int sensorPin, unsigned long sensorValue, float sensorMapped) {
  if (metro.check() == 1) { // check if the metro has passed its interval

      sensorValue = analogRead(sensorPin);
      //Serial.println(sensorValue);
  
      t = sensorMakeFasterT(t, sensorValue, sensorMapped);
      trest = sensorMakeFasterTrest(trest, sensorValue, sensorMapped);
      pwm = sensorIntensify(sensorValue, sensorMapped);
      
      if(sensorValue > sensorThreshold) {
        if (motorState != off)  { 
            motorState=off;
            metro.interval(trest); // rest between chirps
          } else {
            motorState=pwm;
            metro.interval(t); // original chirp speed
          }
          analogWrite(motor,motorState);        
      } else {
        motorState=off;
        analogWrite(motor,motorState);
      }

  } // end metro check


    
} // end of motorcontrol function





int sensorMakeFasterTrest(float trest, unsigned long sensorValue, float sensorMapped) {
  sensorMapped = mapf(sensorValue, sensorThreshold, 550, 1, 5); //10
  trest = trest/sensorMapped; // shorten rest between notes
  return trest;
}
int sensorMakeFasterT(float t, unsigned long sensorValue, float sensorMapped) {
  sensorMapped = mapf(sensorValue, sensorThreshold, 550, 1, 3); //5
  t = t/sensorMapped; // shorten length of note
  return t;
}

int sensorIntensify(unsigned long sensorValue, float sensorMapped) {
  sensorMapped = mapf(sensorValue, sensorThreshold, 550 , 100, 255);
  pwm = sensorMapped;
  return pwm;
}

// Map floats
float mapf(float x, float in_min, float in_max, float out_min, float out_max) {
 return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

