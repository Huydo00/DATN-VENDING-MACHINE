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

#define EN_RS485 12
#define DONE 13

// #define ENL298N 4
// #define M1L298N 7
#define servoLy1 4
#define servoLy2 7
int timelayhang = 120;
SoftwareSerial RS485Serial(RX, TX); // RX, TX

Servo myservo1;
Servo myservo2;
int pos1 = 0;
int pos2 = 45;
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

/********** FUNCTION ***********/
void trahangLen(int trahanglen){
  Step_X.setEnablePin(8);
  Step_X.move(trahanglen);
  Step_X.runToPosition();
  Step_X.disableOutputs();
}

void trahangXuong(int trahangxuong){
  Step_X.setEnablePin(8);
  Step_X.move(trahangxuong);
  Step_X.runToPosition();
  Step_X.disableOutputs();
}

void lyNang(int lynang){
  Step_Y.setEnablePin(8);
  Step_Y.move(lynang);
  Step_Y.runToPosition();
  Step_Y.disableOutputs();
}

void lyHa(int lyha){
  Step_Y.setEnablePin(8);
  Step_Y.move(lyha);
  Step_Y.runToPosition();
  Step_Y.disableOutputs();
}
void cangDay(int cangday){
}
void cangRut(int cangrut){
}







/********** LAYLY ***********/
// Trạng thái ban đầu: càng đẩy ra, nâng ly hạ xuống

// B1: nâng ly (nâng ly lên khỏi càng đẩy)
// B2: rút càng
// B3: hạ ly xuống khoảng 1cm
// B4: đẩy càng (càng được đẩy ra để tách ly)
// B5: hạ ly xuống đến hết hành trình và chờ cánh tay robot lấy
void layly(){
  for(pos1 = 0; pos1 < 45; pos1 += 1)  
  {                                
    pos2--;
    myservo1.write(pos1);            
    myservo2.write(pos2);  
    delay(15);                     
  }
  for(pos1 = 45; pos1>=1; pos1-=1)  
  {                                
    pos2++;
    myservo1.write(pos1);  
    myservo2.write(pos2);  
    delay(15);    
  }
  delay(2000);
}

/********** TRA HANG ***********/
// Trạng thái ban đầu: trả hàng nằm trên

// B1: hạ trả hàng xuống
// B3: 120s
// B2: nâng trả hàng lên
void trahang(){
//   trahangxuong(-2800);
//   delay(120000);
//   trahanglen(2800);
}











/********** MAIN ***********/
void setup() {
  Serial.begin(9600);
  RS485Serial.begin(9600);
  myservo1.attach(servoLy1);
  myservo2.attach(servoLy2);  

  pinMode(DONE, OUTPUT);
  pinMode(EN_RS485, OUTPUT);
  digitalWrite(EN_RS485, LOW);
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
  Step_Y.setMaxSpeed(1000);
  Step_Y.setAcceleration(1000);

  digitalWrite(DONE,LOW);
  digitalWrite(EN_RS485,LOW);
  // homeX();
  // Step_X.setEnablePin(8);
  // Step_X.moveTo(3000);     //4300
  // Step_X.runToPosition();
  // Step_X.disableOutputs();
  
  // homeY();
  // Step_Y.setEnablePin(8);
  // Step_Y.moveTo(200);     //4300
  // Step_Y.runToPosition();
  // Step_Y.disableOutputs();

}

void loop(){

  // if (RS485Serial.available()) {
  //   String DATATHL = RS485Serial.readStringUntil('\n');
  //   /**********SL1:1 layly ***********/
  //   if(DATATHL == "SL1:1"){
  //     Serial.println(DATATHL);
  //     layly();
  //     digitalWrite(DONE,HIGH);
  //   }
  //   /**********SL1:2 trahang ***********/
  //   if(DATATHL == "SL1:2"){
  //     Serial.println(DATATHL);
  //     trahang();
  //     digitalWrite(DONE,HIGH);
  //   }
  //   delay(200);
  //   digitalWrite(DONE,LOW);
  // }

}


