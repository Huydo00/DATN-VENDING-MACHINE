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
#define DONE 13
#define DE 12
#define TX 1
#define RX 0

SoftwareSerial RS485Serial(RX, TX); // RX, TX

Servo myservo;
int ena = 8;
int step_X = 2 ; int dir_X = 5;
int step_Y = 3 ; int dir_Y = 6;

AccelStepper Step_X(1, step_X, dir_X);
AccelStepper Step_Y(1, step_Y, dir_Y);

#define E_X 9
#define E_Y 10

bool gt_E_X;
bool gt_E_Y;

void homeX(){
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
  Step_X.disableOutputs();
}

void homeY(){
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
  Step_Y.disableOutputs();
}

void trahangLen(){
  Step_X.setEnablePin(8);
  Step_X.move(100);
  Step_X.runToPosition();
  Step_X.disableOutputs();
}

void trahangXuong(){
  Step_X.setEnablePin(8);
  Step_X.move(-100);
  Step_X.runToPosition();
  Step_X.disableOutputs();
}

void lyLen(){
  Step_Y.setEnablePin(8);
  Step_Y.move(100);
  Step_Y.runToPosition();
  Step_Y.disableOutputs();
}

void lyXuong(){
  Step_Y.setEnablePin(8);
  Step_Y.move(-100);
  Step_Y.runToPosition();
  Step_Y.disableOutputs();
}

void setup() {
  Serial.begin(9600);
  RS485Serial.begin(9600);

  pinMode(DONE, OUTPUT);
  pinMode(DE, OUTPUT);
  digitalWrite(DE, LOW);
  digitalWrite(DONE,HIGH);

  pinMode(E_X, INPUT_PULLUP);
  pinMode(E_Y, INPUT_PULLUP);

  pinMode(ena, OUTPUT);
  pinMode(step_X, OUTPUT);
  pinMode(dir_X, OUTPUT);
  pinMode(step_Y, OUTPUT);
  pinMode(dir_Y, OUTPUT);

  Step_X.setEnablePin(8);
  Step_Y.setEnablePin(8);
  Step_X.setPinsInverted(false, false, true);
  Step_Y.setPinsInverted(false, false, true);

  Step_X.setMaxSpeed(500);
  Step_X.setAcceleration(500);
  Step_Y.setMaxSpeed(500);
  Step_Y.setAcceleration(500);

  homeX();
  Step_X.setEnablePin(8);
  Step_X.moveTo(1000);     //4300
  Step_X.runToPosition();
  Step_X.disableOutputs();
}

void loop(){
  //trahangLEN

  if (RS485Serial.available()) {
    String DATATHL = RS485Serial.readStringUntil('\n');
    if(DATATHL == "SL1:1"){
      Serial.println(DATATHL);
      trahangXuong();
      delay(1000);
      digitalWrite(DONE,LOW);
    }
    digitalWrite(DONE,HIGH);
  }

}