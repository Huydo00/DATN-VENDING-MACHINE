#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <Firebase_ESP_Client.h>

/* 1. WIFI CONNECT */
#define WIFI_SSID "DT"
#define WIFI_PASSWORD "25022003"

/* 2. API & URL */
#define API_KEY "AIzaSyAn0rRvInY8z2XsOMulwNpv9ckU-OKB2CY"
#define DATABASE_URL "smh-iot-2e746-default-rtdb.firebaseio.com/" 

/* 3. EMAIL & PASS */
#define USER_EMAIL "hhuys0105@gmail.com"
#define USER_PASSWORD "12345678"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

int s=0;

int CAFESUADA = 0;
int CAFEDENDA = 0;
int CAFEDENDAKHONGDUONG = 0;
int CAFEDENNONG = 0;

#define bom1 D0
#define bom2 D1
#define bom3 D4
#define bom4 D5



int receiveData = 0;
#define EN_RS485 D3
#define DONE D2
SoftwareSerial RS485(3,1); //RX,TX

void firebaseconnect(){
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;
  Firebase.reconnectNetwork(true);
  fbdo.setBSSLBufferSize(4096, 1024);
  fbdo.setResponseSize(2048);
  Firebase.begin(&config, &auth);
  Firebase.setDoubleDigits(5);
  config.timeout.serverResponse = 10;
}













/******************************   MASTER:WEB  *******************************/
void nguyenlieu1(){
}
void nguyenlieu2(){
}
void nguyenlieu3(){
}
void nguyenlieu4(){
}
void hottemp(){
}
void ice(){
}
void khuay(){
}















/******************************   SLAVE 1: STEP   *******************************/
void layly(){
  delay(10);
  digitalWrite(EN_RS485,HIGH);
  RS485.write("SL1:1");
  delay(10);
  digitalWrite(EN_RS485, LOW);
  while(true){
    if(digitalRead(DONE) == HIGH){
      break;
    }
  }
}

void trahang(){
  delay(10);
  digitalWrite(EN_RS485,HIGH);
  RS485.write("SL1:2");
  delay(10);
  digitalWrite(EN_RS485, LOW);
  while(true){
    if(digitalRead(DONE) == HIGH){
      break;
    }
  }
}










/******************************   SLAVE 2: SCARA   *******************************/
void scaralayly(){
  delay(10);
  digitalWrite(EN_RS485,HIGH);
  RS485.write("SL2:1");
  delay(10);
  digitalWrite(EN_RS485, LOW);
  while(true){
    if(digitalRead(DONE) == HIGH){
      break;
    }
  }
}
void scaranguyenlieu1(){
  delay(10);
  digitalWrite(EN_RS485,HIGH);
  RS485.write("SL2:2");
  delay(10);
  digitalWrite(EN_RS485, LOW);
  while(true){
    if(digitalRead(DONE) == HIGH){
      break;
    }
  }
}
void scaralnguyenlieu2(){
  delay(10);
  digitalWrite(EN_RS485,HIGH);
  RS485.write("SL2:3");
  delay(10);
  digitalWrite(EN_RS485, LOW);
  while(true){
    if(digitalRead(DONE) == HIGH){
      break;
    }
  }
}
void scaranguyenlieu3(){
  delay(10);
  digitalWrite(EN_RS485,HIGH);
  RS485.write("SL2:4");
  delay(10);
  digitalWrite(EN_RS485, LOW);
  while(true){
    if(digitalRead(DONE) == HIGH){
      break;
    }
  }
}
void scaranguyenlieu4(){
  delay(10);
  digitalWrite(EN_RS485,HIGH);
  RS485.write("SL2:5");
  delay(10);
  digitalWrite(EN_RS485, LOW);
  while(true){
    if(digitalRead(DONE) == HIGH){
      break;
    }
  }
}
void scaradice(){
  delay(10);
  digitalWrite(EN_RS485,HIGH);
  RS485.write("SL2:6");
  delay(10);
  digitalWrite(EN_RS485, LOW);
  while(true){
    if(digitalRead(DONE) == HIGH){
      break;
    }
  }
}
void scaradkhuay(){
  delay(10);
  digitalWrite(EN_RS485,HIGH);
  RS485.write("SL2:7");
  delay(10);
  digitalWrite(EN_RS485, LOW);
  while(true){
    if(digitalRead(DONE) == HIGH){
      break;
    }
  }
}
void scaratrahang(){
  delay(10);
  digitalWrite(EN_RS485,HIGH);
  RS485.write("SL2:8");
  delay(10);
  digitalWrite(EN_RS485, LOW);
  while(true){
    if(digitalRead(DONE) == HIGH){
      break;
    }
  }
}









/******************************   MENU DRINK   *******************************/
void CFNONG(){
  
}
void CFDADUONG(){
  
}
void CFDAKKHONGDUONG(){
  
}
void CFSUA(){
  layly();
  delay(5);
  scaralayly();
  delay(5);

  scaranguyenlieu1();   //sua
  delay(5)
  nguyenlieu1();
  delay(5);

  scaralnguyenlieu2();    //cafe
  delay(5);
  nguyenlieu2();
  delay(5);

  scaradkhuay();
  delay(5);
  khuay();
  delay(5);

  scaradice();
  delay(5);
  ice();
  delay(5);

  scaratrahang();
  delay(5);
  trahang();
  delay(5);
}

void CFSUAtest(){
  layly();
  delay(5);
  scaralayly();
  delay(5);
}















/******************************   MAIN   *******************************/
void setup() {
  Serial.begin(9600);
  RS485.begin(9600);

  pinMode(EN_RS485,OUTPUT);
  pinMode(bom1,OUTPUT);
  pinMode(bom2,OUTPUT);
  pinMode(bom3,OUTPUT);
  pinMode(bom4,OUTPUT);
  pinMode(DONE, INPUT);

  //Set Mode RX
  digitalWrite(EN_RS485,LOW);
  // WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  // Serial.print("Connecting to Wi-Fi");
  // while (WiFi.status() != WL_CONNECTED){
  //   Serial.print(".");
  //   delay(300);
  // }
  // firebaseconnect();
  delay(2000);
  layly();
}
void loop() {
    


  // if (Serial.available()) {

  //   String dataToSend = Serial.readStringUntil('\n');
  //   Serial.print("Data sent: ");
  //   Serial.println(dataToSend);
  //   if(dataToSend == "layly"){
  //     layly();
  //   }
  // }













  // if(Firebase.RTDB.getString(&fbdo, "/MACHINE/CAFESUADA")){
  //   CAFESUADA = (fbdo.stringData()).toInt();
  //   if (CAFESUADA == 1){
  //     Serial.println("CAFE SUA DA");
  //     digitalWrite(bom1,LOW); // rút
  //     layly();
  //     delay(1000);
  //     digitalWrite(bom1,HIGH);
  //     Firebase.RTDB.setInt(&fbdo, "/MACHINE/CAFESUADA", 0);
  //   }
  // }
  // else
  //   Serial.println("wait...");

}