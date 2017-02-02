//#include <Metro.h> // Include Metro library
//#include <math.h> // for logarithmic scaling

// Set ideal pwm level
//int off = LOW;
//int on = HIGH;
int pwm = 120;
int off = 0;
int on = 255;

// Define motors pins (*4)
const int motor0 =  2; //2
const int motor1 =  3; //3
const int motor2 =  4; //7
const int motor3 =  5; //10

// Define motor states (*4)
int motor0State =  on;
int motor1State =  on;
int motor2State =  on;
int motor3State =  on;

// Set the active interval (same for all for now?)
float t =  3850;
int counter = 1;

// counter variables (0)
int counternote =  1;
int counterphrase =  1;

// how many times to do pattern before it reevaluates itself (way arbitrary)
int unit0 = 5; // just one for now
//int unit1 = 5;
//int unit2 = 3;
//int unit3 = 7;


void setup()
{
  // declare output pins
  pinMode(motor0,OUTPUT);
  pinMode(motor1,OUTPUT);
  pinMode(motor2,OUTPUT);
  pinMode(motor3,OUTPUT);
  Serial.begin(57600);
}

void loop() {

  song();
  
}

// custom functions
void song() {

  if (counter % 2 == 0) {
    t = random(2500, 5000);
    Serial.println(t);
    
  } else {
    t = 3850;
    Serial.println("normal time");
  }
  
  if (counter % 5 == 0) {
    // every 5th time, do a randomized song
    Serial.println("weird song");
    songRandom(motor0, motor0State);
    songRandom(motor2, motor2State);
    delay(t);
    
    //digitalWrite(motor2,off);
    songRandom(motor0, motor0State);
    songRandom(motor3, motor3State);
    delay(t);

    digitalWrite(motor0,off);
    songRandom(motor1, motor1State);
    songRandom(motor3, motor3State);
    delay(t);

    digitalWrite(motor0,off);
    digitalWrite(motor3,off);
    songRandom(motor1, motor1State);
    songRandom(motor2, motor2State);
    delay(t);
    
  } else if (counter % 7 == 0 || counter % 8 == 0) {
    // otherwise, do reverse song
    Serial.println("reverse song");
    
    //Serial.println("note 4");
    digitalWrite(motor0,off);
    digitalWrite(motor1,on);
    digitalWrite(motor2,on);
    digitalWrite(motor3,off);
    delay(t);  

     //Serial.println("note 3");
    digitalWrite(motor0,off);
    digitalWrite(motor1,on);
    digitalWrite(motor2,off);
    digitalWrite(motor3,on);
    delay(t);

    //Serial.println("note 2");
    digitalWrite(motor0,on);
    digitalWrite(motor1,off);
    digitalWrite(motor2,off);
    digitalWrite(motor3,on);
    delay(t);

    //Serial.println("note 1");
    digitalWrite(motor0,on);
    digitalWrite(motor1,off);
    digitalWrite(motor2,on);
    digitalWrite(motor3,off);
    delay(t);
       
  } else {
    // otherwise, to the normal song
    Serial.println("normal song");
    //Serial.println("note 1");
    digitalWrite(motor0,on);
    digitalWrite(motor1,off);
    digitalWrite(motor2,on);
    digitalWrite(motor3,off);
    delay(t);
  
    //Serial.println("note 2");
    digitalWrite(motor0,on);
    digitalWrite(motor1,off);
    digitalWrite(motor2,off);
    digitalWrite(motor3,on);
    delay(t);
  
    //Serial.println("note 3");
    digitalWrite(motor0,off);
    digitalWrite(motor1,on);
    digitalWrite(motor2,off);
    digitalWrite(motor3,on);
    delay(t);
  
    //Serial.println("note 4");
    digitalWrite(motor0,off);
    digitalWrite(motor1,on);
    digitalWrite(motor2,on);
    digitalWrite(motor3,off);
    delay(t);  
  }
  counter = counter+1;
  Serial.println(counter);
}

void songRandom(int motor, int &motorState) {

  int randomize = random(0,2);
  if (randomize == 0) {
    motorState=pwm;
  } else {
    motorState=on;    
  } 
  digitalWrite(motor, motorState);
  
}

