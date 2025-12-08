#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <Firebase_ESP_Client.h>

/* 1. WIFI CONNECT */
#define WIFI_SSID "Lau 1"
#define WIFI_PASSWORD "Hoang123"

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

int FB_dataNL1 = 10;
int FB_dataNL2 = 10;
int FB_dataNL3 = 10;
int FB_dataNL4 = 10;
float dataNL1 = FB_dataNL1 *30000/60;
float dataNL2 = FB_dataNL2 *30000/60;
float dataNL3 = FB_dataNL3 *30000/60;
float dataNL4 = FB_dataNL4 *30000/60;

#define rlice D0
#define rlnungnhiet D8

#define bom1 D7
#define bom2 D6
#define bom3 D5
#define bom4 D4

int receiveData = 0;
#define EN_RS485 D3
#define DONE1 D1
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

void rotnguyenlieu1(){
  // float dataNL1 = FB_dataNL1 *30000/60;    // 50*30000/60   120ml/ph
  digitalWrite(bom1,LOW);
  delay(FB_dataNL1 *30000/60);
  digitalWrite(bom1,HIGH);
}
void rotnguyenlieu2(){
  // float dataNL2 = FB_dataNL2 *30000/60;    // 50*30000/60   120ml/ph
  digitalWrite(bom2,LOW);
  delay(FB_dataNL2 *30000/60);
  digitalWrite(bom2,HIGH);
}
void rotnguyenlieu3(){
  // float dataNL3 = FB_dataNL3 *30000/60;    // 50*30000/60   120ml/ph
  digitalWrite(bom3,LOW);
  delay(FB_dataNL3 *30000/60);
  digitalWrite(bom3,HIGH);
}
void rotnguyenlieu4(){
  // float dataNL4 = FB_dataNL4 *30000/60;    // 50*30000/60   120ml/ph
  digitalWrite(bom4,LOW);
  delay(FB_dataNL4 *30000/60);
  digitalWrite(bom4,HIGH);
}

void layda(){
  digitalWrite(rlice,LOW);
  delay(2000);
  digitalWrite(rlice,HIGH);
}

void nungnong(){
  digitalWrite(rlnungnhiet,LOW);
  delay(3000);
  digitalWrite(rlnungnhiet,HIGH);
}















/******************************   SLAVE 1: STEP   *******************************/
void slave1tachly(){
  delay(2000);
  digitalWrite(EN_RS485,HIGH);
  RS485.write("SL1:1");
  delay(10);
  digitalWrite(EN_RS485, LOW);
  while(true){
    if(digitalRead(DONE1) == HIGH){
      break;
    }
    delay(10);
  }
}
void slave1haly(){
  delay(2000);
  digitalWrite(EN_RS485,HIGH);
  RS485.write("SL1:2");
  delay(10);
  digitalWrite(EN_RS485, LOW);
  while(true){
    if(digitalRead(DONE1) == HIGH){
      break;
    }
    delay(10);
  }
}
void slave1homelayly(){
  delay(2000);
  digitalWrite(EN_RS485,HIGH);
  RS485.write("SL1:3");
  delay(10);
  digitalWrite(EN_RS485, LOW);
  while(true){
    if(digitalRead(DONE1) == HIGH){
      break;
    }
    delay(10);
  }
}

void slave1trahang(){
  delay(2000);
  digitalWrite(EN_RS485,HIGH);
  RS485.write("SL1:4");
  delay(10);
  digitalWrite(EN_RS485, LOW);
  while(true){
    if(digitalRead(DONE1) == HIGH){
      break;
    }
    delay(10);
  }
}

void slave1khuay(){
  delay(2000);
  digitalWrite(EN_RS485,HIGH);
  RS485.write("SL1:5");
  delay(10);
  digitalWrite(EN_RS485, LOW);
  while(true){
    if(digitalRead(DONE1) == HIGH){
      break;
    }
    delay(10);
  }
}







/******************************   SLAVE 2: SCARA   *******************************/
void scaracholayly(){
  delay(2000);
  digitalWrite(EN_RS485,HIGH);
  RS485.write("SL2:1");
  delay(10);
  digitalWrite(EN_RS485, LOW);
  while(true){
    if(digitalRead(DONE) == HIGH){
      break;
    }
    delay(10);
  }
}
void scaralayly(){
  delay(2000);
  digitalWrite(EN_RS485,HIGH);
  RS485.write("SL2:2");
  delay(10);
  digitalWrite(EN_RS485, LOW);
  while(true){
    if(digitalRead(DONE) == HIGH){
      break;
    }
    delay(10);
  }
}
void scaranguyenlieu1(){
  delay(2000);
  digitalWrite(EN_RS485,HIGH);
  RS485.write("SL2:3");
  delay(10);
  digitalWrite(EN_RS485, LOW);
  while(true){
    if(digitalRead(DONE) == HIGH){
      break;
    }
    delay(10);
  }
}
void scaranguyenlieu2(){
  delay(2000);
  digitalWrite(EN_RS485,HIGH);
  RS485.write("SL2:4");
  delay(10);
  digitalWrite(EN_RS485, LOW);
  while(true){
    if(digitalRead(DONE) == HIGH){
      break;
    }
    delay(10);
  }
}
void scaranguyenlieu3(){
  delay(2000);
  digitalWrite(EN_RS485,HIGH);
  RS485.write("SL2:5");
  delay(10);
  digitalWrite(EN_RS485, LOW);
  while(true){
    if(digitalRead(DONE) == HIGH){
      break;
    }
    delay(10);
  }
}
void scaranguyenlieu4(){
  delay(2000);
  digitalWrite(EN_RS485,HIGH);
  RS485.write("SL2:6");
  delay(10);
  digitalWrite(EN_RS485, LOW);
  while(true){
    if(digitalRead(DONE) == HIGH){
      break;
    }
    delay(10);
  }
}


void scaradice(){
  delay(2000);
  digitalWrite(EN_RS485,HIGH);
  RS485.write("SL2:8");
  delay(10);
  digitalWrite(EN_RS485, LOW);
  while(true){
    if(digitalRead(DONE) == HIGH){
      break;
    }
    delay(10);
  }
}
void scaradkhuay(){
  delay(2000);
  digitalWrite(EN_RS485,HIGH);
  RS485.write("SL2:7");
  delay(10);
  digitalWrite(EN_RS485, LOW);
  while(true){
    if(digitalRead(DONE) == HIGH){
      break;
    }
    delay(10);
  }
}
void scaradkhuayend(){
  delay(2000);
  digitalWrite(EN_RS485,HIGH);
  RS485.write("SL2:71");
  delay(10);
  digitalWrite(EN_RS485, LOW);
  while(true){
    if(digitalRead(DONE) == HIGH){
      break;
    }
    delay(10);
  }
}
void scaratrahang(){
  delay(2000);
  digitalWrite(EN_RS485,HIGH);
  RS485.write("SL2:9");
  delay(10);
  digitalWrite(EN_RS485, LOW);
  while(true){
    if(digitalRead(DONE) == HIGH){
      break;
    }
    delay(10);
  }
}








/******************************   FUNCTION  *******************************/
void layly(){
  scaracholayly();
  slave1tachly();
  slave1haly();
  scaralayly();

  // slave1tachly();
  // slave1haly();
  // scaracholayly();
  // scaralayly();
  // slave1homelayly();
}
void nguyenlieu1(){
  scaranguyenlieu1();
  rotnguyenlieu1();
}
void nguyenlieu2(){
  scaranguyenlieu2();
  rotnguyenlieu2();
}
void nguyenlieu3(){
  scaranguyenlieu3();
  rotnguyenlieu3();
}
void nguyenlieu4(){
  scaranguyenlieu4();
  rotnguyenlieu4();
}
void khuay(){
  scaradkhuay();
  slave1khuay();
  scaradkhuayend();
}
void ice(){
  scaradice();
  layda();
}
void trahang(){
  scaratrahang();
  slave1trahang();
  slave1homelayly();
}
void hottemp(){
}










/******************************   INSPECTION PROCESS   *******************************/
void CFDADUONG(){
  layly();

  //NGUYENLIEU
  if(Firebase.RTDB.getString(&fbdo, "/MACHINEROBOT/cfdendaDA/nl1")){
    FB_dataNL1 = (fbdo.stringData()).toInt();
  } 
  nguyenlieu1();

  if(Firebase.RTDB.getString(&fbdo, "/MACHINEROBOT/cfdendaDA/nl2")){
    FB_dataNL3 = (fbdo.stringData()).toInt();
  }
  nguyenlieu3();

  khuay();
  ice();
  trahang();
  Firebase.RTDB.setInt(&fbdo, "/MACHINEROBOT/cfdendaDA/CFSUADASTART", 0);
}


void CFDAKHONGDUONG(){
  layly();

  //NGUYENLIEU
  if(Firebase.RTDB.getString(&fbdo, "/MACHINEROBOT/cfdenkodaDA/nl1")){
    FB_dataNL1 = (fbdo.stringData()).toInt();
  } 
  nguyenlieu1();

  if(Firebase.RTDB.getString(&fbdo, "/MACHINEROBOT/cfdenkodaDA/nl2")){
    FB_dataNL3 = (fbdo.stringData()).toInt();
  }
  nguyenlieu3();

  khuay();
  ice();
  trahang();
  Firebase.RTDB.setInt(&fbdo, "/MACHINEROBOT/cfdenkodaDA/CFSUADASTART", 0);
}


void CFSUA(){

  layly();

  //NGUYENLIEU
  if(Firebase.RTDB.getString(&fbdo, "/MACHINEROBOT/CFSUADA/nl1")){
    FB_dataNL1 = (fbdo.stringData()).toInt();
  } 
  nguyenlieu1();

  if(Firebase.RTDB.getString(&fbdo, "/MACHINEROBOT/CFSUADA/nl2")){
    FB_dataNL2 = (fbdo.stringData()).toInt();
  }
  nguyenlieu2();

  khuay();
  ice();
  trahang();
  Firebase.RTDB.setInt(&fbdo, "/MACHINEROBOT/CFSUADA/CFSUADASTART", 0);
}














/******************************   MAIN   *******************************/
void setup() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  firebaseconnect();

  Serial.begin(9600);
  RS485.begin(9600);

  pinMode(EN_RS485,OUTPUT);
  pinMode(rlice,OUTPUT);
  pinMode(rlnungnhiet,OUTPUT);
  pinMode(bom1,OUTPUT);
  pinMode(bom2,OUTPUT);
  pinMode(bom3,OUTPUT);
  pinMode(bom4,OUTPUT);
  pinMode(DONE1, INPUT);
  pinMode(DONE, INPUT);

  //Set Mode RX
  digitalWrite(EN_RS485,LOW);
  digitalWrite(rlice,HIGH);
  digitalWrite(bom1,HIGH);
  digitalWrite(bom2,HIGH);
  digitalWrite(bom3,HIGH);
  digitalWrite(bom4,HIGH);

  //////////////////////TESTTTTT





  // slave1tachly();
  // slave1haly();
  // scaracholayly();
  // scaralayly();
  // slave1homelayly(); 

  // nguyenlieu1();
  // nguyenlieu2();

  // scaradkhuay();
  // khuay();
  // scaradkhuayend();


  // scaratrahang();
  // slave1trahang();



  // scaranguyenlieu1();
  // scaranguyenlieu2();
}
void loop() {

  if(Firebase.RTDB.getString(&fbdo, "/MACHINEROBOT/CFSUADA/CFSUADASTART")){
    CAFESUADA = (fbdo.stringData()).toInt();
    if (CAFESUADA == 1){
      CFSUA();
      Firebase.RTDB.setInt(&fbdo, "/MACHINEROBOT/CFSUADA/CFSUADASTART", 0);
    }
  }
  if(Firebase.RTDB.getString(&fbdo, "/MACHINEROBOT/cfdendaDA/CFSUADASTART")){
    CAFESUADA = (fbdo.stringData()).toInt();
    if (CAFESUADA == 1){
      CFDADUONG();
      Firebase.RTDB.setInt(&fbdo, "/MACHINEROBOT/cfdendaDA/CFSUADASTART", 0);
    }
  }
  if(Firebase.RTDB.getString(&fbdo, "/MACHINEROBOT/cfdenkodaDA/CFSUADASTART")){
    CAFESUADA = (fbdo.stringData()).toInt();
    if (CAFESUADA == 1){
      CFDAKHONGDUONG();
      Firebase.RTDB.setInt(&fbdo, "/MACHINEROBOT/cfdenkodaDA/CFSUADASTART", 0);
    }
  }

}