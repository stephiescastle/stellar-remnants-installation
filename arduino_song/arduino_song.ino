//#include <Metro.h> // Include Metro library
//#include <math.h> // for logarithmic scaling

// Set ideal pwm level
int off = LOW;
int pwm = HIGH;

// Define motors pins (*4)
const int motor0 =  2; //2
const int motor1 =  3; //3
const int motor2 =  4; //7
const int motor3 =  5; //10

// Define motor names (*$4)
char plate2 = 'plate2';
char plate3 = 'plate3';
char plate7 = 'plate7';
char plate10 = 'plate10';

// Define motor states (*4)
int motor0State =  pwm;
int motor1State =  pwm;
int motor2State =  pwm;
int motor3State =  pwm;

// Set the active interval (same for all for now?)
float t =  3850;
//float t1 =  290;
//float t2 =  295;
//float t3 =  185;

// Set the rest interval (same for all for now?)
//float t0rest =  15; 
//float t1rest =  220; 
//float t2rest =  225; 
//float t3rest =  125; 

// Instatiate metro object  (*4)
//Metro metro0 =  Metro(t0); 
//Metro metro1 =  Metro(t1); 
//Metro metro2 =  Metro(t2); 
//Metro metro3 =  Metro(t3); 

///////////////////////////////////////
//////// installation settings ////////
///////////////////////////////////////

// counter variables (0)
int counternote =  1;
int counterphrase =  1;

// how many times to do pattern before it reevaluates itself (way arbitrary)
int unit0 = 5; // just one for now
//int unit1 = 5;
//int unit2 = 3;
//int unit3 = 7;


// installation time multiplier
int installationgp = 30;  // grand pause (*trest)
int installationrest = 14; // pause (*trest)

void setup()
{
  // declare output pins
  pinMode(motor0,OUTPUT);
  pinMode(motor1,OUTPUT);
  pinMode(motor2,OUTPUT);
  pinMode(motor3,OUTPUT);
  Serial.begin(9600);
}

void loop() {

  Serial.println("note 1");
  digitalWrite(motor0,pwm);
  digitalWrite(motor1,off);
  digitalWrite(motor2,pwm);
  digitalWrite(motor3,off);
  delay(t);

  Serial.println("note 2");
  digitalWrite(motor0,pwm);
  digitalWrite(motor1,off);
  digitalWrite(motor2,off);
  digitalWrite(motor3,pwm);
  delay(t);

  Serial.println("note 3");
  digitalWrite(motor0,off);
  digitalWrite(motor1,pwm);
  digitalWrite(motor2,off);
  digitalWrite(motor3,pwm);
  delay(t);

  Serial.println("note 4");
  digitalWrite(motor0,off);
  digitalWrite(motor1,pwm);
  digitalWrite(motor2,pwm);
  digitalWrite(motor3,off);
  delay(t);
  
}

