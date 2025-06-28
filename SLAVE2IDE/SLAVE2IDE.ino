  #include <Arduino.h>
#include <SoftwareSerial.h>
#include <AccelStepper.h>
#include <Servo.h>

/*  MS1   MS2    MS3
    LOW   LOW    LOW    Full
    LOW   HIGH   LOW    1/4
    HIGH  HIGH   LOW    1/8
    HIGH  HIGH   HIGH   1/16 //
*/

/*  1 PWM = 1/4 * 1.8' = 0.45
    1 vòng 360' = 360/0.45 = 800

    X: 20-80   22-110    0.25*0.2   
    Y: 20-80   23-92     0.25*0.25
    Z: 20-90             2/9
    A: 250mm
*/
Servo myservo;
int ena = 8;
int step_X = 2 ; int dir_X = 5;
int step_Y = 3 ; int dir_Y = 6;
int step_Z = 4 ; int dir_Z = 7;
int step_A = 12 ; int dir_A = A0;

AccelStepper Step_X(1, step_X, dir_X);
AccelStepper Step_Y(1, step_Y, dir_Y);
AccelStepper Step_Z(1, step_Z, dir_Z);
AccelStepper Step_A(1, step_A, dir_A);

#define E_X 9
#define E_Y 10
#define E_Z 11
#define E_A A3
#define CAFEDENDAKHONGDUONG 0
#define CAFEDENDACODUONG 0
#define CAFEDENNONGCODUONG 0
#define CAFESUADA 0

bool gt_E_X;
bool gt_E_Y;
bool gt_E_Z;
bool gt_E_A;

void homeZ(){
  int homeZ = 0;
  Step_Z.enableOutputs();

  while(digitalRead(E_Z)){
    Serial.println(digitalRead(E_Z));
    Step_Z.moveTo(homeZ);
    homeZ ++;
    Step_Z.run();
  }
  Step_Z.setCurrentPosition(0);
  homeZ = 0;

  Step_Z.moveTo(-600);
  while (Step_Z.distanceToGo()!=0)
  {
    Step_Z.run();
  }
  Step_Z.disableOutputs();
}

void homeXY(){
  int homeY = 0;
  Step_Y.enableOutputs();

  while(digitalRead(E_Y)){
    Serial.println(digitalRead(E_Y));
    Step_Y.moveTo(homeY);
    homeY --;
    Step_Y.run();
  }
  Step_Y.setCurrentPosition(0);
  homeY = 0;

  Step_Y.moveTo(300);
  while (Step_Y.distanceToGo()!=0)
  {
    Step_Y.run();
  }
  Step_Y.disableOutputs();

  int homeX = 0;
  Step_X.enableOutputs();

  while(digitalRead(E_X)){
    Serial.println(digitalRead(E_X));
    Step_X.moveTo(homeX);
    homeX --;
    Step_X.run();
  }
  Step_X.setCurrentPosition(0);
  homeX = 0;

  Step_X.moveTo(300);
  while (Step_X.distanceToGo()!=0)
  {
    Step_X.run();
  }
  Step_X.disableOutputs();
}

void homeA(){
  int homeA = 0;
  Step_A.enableOutputs();

  while(digitalRead(E_A)){
    Serial.println(digitalRead(E_A));
    Step_A.moveTo(homeA);
    homeA --;
    Step_A.run();
  }
  Step_A.setCurrentPosition(0);
  homeA = 0;

  Step_A.moveTo(600);
  while (Step_A.distanceToGo()!=0)
  {
    Step_A.run();
  }
  Step_A.disableOutputs();
}

void run(byte Ser, int X, int Y, int Z, int A)
{
  Step_X.setEnablePin(8);
  Step_Y.setEnablePin(8);
  Step_Z.setEnablePin(8);
  Step_A.setEnablePin(8);
  
  myservo.write(Ser);

  Step_X.moveTo(X);
  Step_Y.moveTo(Y);
  Step_Z.moveTo(-Z);
  Step_A.moveTo(A);
  while(Step_X.distanceToGo() != 0 or Step_Y.distanceToGo() != 0 or Step_Z.distanceToGo() != 0 or Step_A.distanceToGo() != 0)
  {
    Step_X.run();
    Step_Y.run();
    Step_Z.run();
    Step_A.run();
  }  
  Step_X.disableOutputs();
  Step_Y.disableOutputs();
  Step_Z.disableOutputs();
  Step_A.disableOutputs();
}
/******************************   FUCTION   *******************************/
void scaralayly(){
  run(0, 300, 300, 600, 600);
  delay(500);
}
void scaranguyenlieu1(){
  run(0, 300, 300, 600, 600);
  delay(500);
}
void scaranguyenlieu2(){
  run(0, 300, 300, 600, 600);
  delay(500);
}
void scaranguyenlieu3(){
  run(0, 300, 300, 600, 600);
  delay(500);
}
void scaranguyenlieu4(){
  run(0, 300, 300, 600, 600);
  delay(500);
}
void scaradice(){
  run(0, 300, 300, 600, 600);
  delay(500);
}
void scaradkhuay(){
  run(0, 300, 300, 600, 600);
  delay(500);
}
void scaratrahang(){
  run(0, 300, 300, 600, 600);
  delay(500);
}

















/******************************   MAIN   *******************************/
void setup() {
  Serial.begin(9600);
  pinMode(E_X, INPUT_PULLUP);
  pinMode(E_Y, INPUT_PULLUP);
  pinMode(E_Z, INPUT_PULLUP);
  pinMode(E_A, INPUT_PULLUP);

  pinMode(ena, OUTPUT);
  pinMode(step_X, OUTPUT);
  pinMode(dir_X, OUTPUT);
  pinMode(step_Y, OUTPUT);
  pinMode(dir_Y, OUTPUT);
  pinMode(step_Z, OUTPUT);
  pinMode(dir_Z, OUTPUT);
  pinMode(step_A, OUTPUT);
  pinMode(dir_A, OUTPUT);

  Step_X.setEnablePin(8);
  Step_Y.setEnablePin(8);
  Step_Z.setEnablePin(8);
  Step_A.setEnablePin(8);
  Step_X.setPinsInverted(false, false, true);
  Step_Y.setPinsInverted(false, false, true);
  Step_Z.setPinsInverted(false, false, true);
  Step_A.setPinsInverted(false, false, true);

  Step_X.setMaxSpeed(500);
  Step_X.setAcceleration(500);
  Step_Y.setMaxSpeed(500);
  Step_Y.setAcceleration(500);
  Step_Z.setMaxSpeed(500);
  Step_Z.setAcceleration(500);
  Step_A.setMaxSpeed(500);
  Step_A.setAcceleration(500);
  
  homeZ();
  homeXY();
  homeA();
  //Vitrigoc
  run(0, 300, 300, 600, 600);
  delay(500);
  run(0, 300, 300, 600, 1500);
  delay(500);
  run(0, 300, 300, 600, 600);
  delay(500);
}

void loop(){

}