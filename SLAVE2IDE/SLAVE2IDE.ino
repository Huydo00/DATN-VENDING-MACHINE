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
#define TX 1
#define RX 0

SoftwareSerial RS485Serial(RX, TX); // RX, TX

// #define EN_RS485 12
#define DONE 13

Servo myservo;
#define kep A2

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

  Step_Z.moveTo(-300);
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
void scaramokep(){
  myservo.write(90);
}
void scaradongkep(){
  myservo.write(45);
}
void scaracholayly(){
  run(0, 3000, 300, 300, 2000);
  run(0, 5000, 8000, 600, 10000);
  scaramokep();
  run(0, 6000, 8800, 1300, 10000);
}
void scaralayly(){
  run(0, 6280, 8850, 1320, 10000);
  scaradongkep();
  run(0, 6280, 8850, 1320, 7000);
}
void scaranguyenlieu1(){
  run(0, 4000, 4000, 2000, 6000);
  run(0, 2750, 5500, 2050, 6000);
}
void scaranguyenlieu2(){
  run(0, 3150, 4500, 2100, 6000);
}
void scaranguyenlieu3(){
  run(0, 3380, 3750, 2100, 6000);
}
void scaranguyenlieu4(){
  run(0, 3500, 2850, 2000, 6000);
}
void scaraice(){
  run(0, 3500, 2850, 2000, 7000);
}
void scarakhuay(){
  run(0, 4000, 1400, 2000, 6000);
  run(0, 2400, 2300, 1700, 6000);
  run(0, 2400, 2300, 1700, 4000);
}
void scarakhuayend(){
  run(0, 2400, 2300, 1700, 6000);
  run(0, 3000, 1500, 1700, 6000);
}
void scaratrahang(){
  run(0, 4000, 4000, 2000, 6000);
  run(0, 6200, 4600, 2000, 6000);
  run(0, 6200, 4600, 2000, 11500);
  scaramokep();
  run(0, 6500, 4500, 2200, 11500);
  run(0, 6500, 4500, 2200, 8500);
}
void scaraend(){
  delay(5000);
  run(0, 5900, 1500, 1300, 8500);
  run(0, 4500, 500, 200, 4000);
  run(0, 500, 500, 200, 700);
  homeZ();
  homeXY();
  homeA();
}
















/******************************   MAIN   *******************************/
void setup() {
  Serial.begin(9600);
  RS485Serial.begin(9600);
  myservo.attach(kep);
  scaradongkep();

  pinMode(DONE, OUTPUT);
  // pinMode(EN_RS485, OUTPUT);
  // digitalWrite(EN_RS485, LOW);
  digitalWrite(DONE,HIGH);

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

  Step_X.setMaxSpeed(600);
  Step_X.setAcceleration(600);
  Step_Y.setMaxSpeed(600);
  Step_Y.setAcceleration(600);
  Step_Z.setMaxSpeed(600);
  Step_Z.setAcceleration(600);
  Step_A.setMaxSpeed(600);
  Step_A.setAcceleration(600);
  
  homeZ();
  homeXY();
  homeA();


  // scarakhuay();

  // scaralayly();
  // scaranguyenlieu2();

  // scaratrahang();
  // scaraend();
}

void loop(){

  if (RS485Serial.available()) {
    String DATATHL = RS485Serial.readStringUntil('\n');
    /**********SL1:1 scaracholayly***********/
    if(DATATHL == "SL2:1"){
      Serial.println(DATATHL);
      scaracholayly();
      digitalWrite(DONE,LOW);
      delay(100);
    }
    /**********SL1:1 scaralayly***********/
    if(DATATHL == "SL2:2"){
      Serial.println(DATATHL);
      scaralayly();
      digitalWrite(DONE,LOW);
      delay(100);
    }





    /**********SL1:2 NL1***********/
    if(DATATHL == "SL2:3"){
      Serial.println(DATATHL);
      scaranguyenlieu1();
      digitalWrite(DONE,LOW);
      delay(100);
    }
    /**********SL1:2 NL2***********/
     if(DATATHL == "SL2:4"){
      Serial.println(DATATHL);
      scaranguyenlieu2();
      digitalWrite(DONE,LOW);
      delay(100);
    }
    /**********SL1:2 NL1***********/
    if(DATATHL == "SL2:5"){
      Serial.println(DATATHL);
      scaranguyenlieu3();
      digitalWrite(DONE,LOW);
      delay(100);
    }
    /**********SL1:2 NL2***********/
     if(DATATHL == "SL2:6"){
      Serial.println(DATATHL);
      scaranguyenlieu4();
      digitalWrite(DONE,LOW);
      delay(100);
    }





    /**********SL1:2 KHUAY***********/
    if(DATATHL == "SL2:7"){
      Serial.println(DATATHL);
      scarakhuay();
      digitalWrite(DONE,LOW);
      delay(100);
    }
    if(DATATHL == "SL2:71"){
      Serial.println(DATATHL);
      scarakhuayend();
      digitalWrite(DONE,LOW);
      delay(100);
    }
    /**********SL1:2 ICE***********/
     if(DATATHL == "SL2:8"){
      Serial.println(DATATHL);
      scaraice();
      digitalWrite(DONE,LOW);
      delay(100);
    }
    /**********SL1:2 TRAHANG***********/
     if(DATATHL == "SL2:9"){
      Serial.println(DATATHL);
      scaratrahang();
      digitalWrite(DONE,LOW);
      delay(100);
      digitalWrite(DONE,HIGH);
      scaraend();
    }

  digitalWrite(DONE,HIGH);
  }
}
