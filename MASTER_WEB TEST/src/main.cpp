#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <Firebase_ESP_Client.h>

#include <ModbusMaster.h>

// Khai báo ModbusMaster
ModbusMaster node;

// Chân điều khiển DE/RE
#define MAX485_DE_RE D3  // D2 trên ESP8266 (GPIO4)

#include <SoftwareSerial.h>
SoftwareSerial modbusSerial(3,1); // RX, TX

void preTransmission()  { digitalWrite(MAX485_DE_RE, HIGH); }
void postTransmission() { digitalWrite(MAX485_DE_RE, LOW); }

void setup() {
  pinMode(MAX485_DE_RE, OUTPUT);
  digitalWrite(MAX485_DE_RE, LOW);

  Serial.begin(115200);
  modbusSerial.begin(9600);  // baud rate

  node.begin(1, modbusSerial); // Slave ID = 1
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
}

void loop() {
  // Gửi lệnh bật LED
  node.writeSingleRegister(0x0000, 1);
  Serial.println("LED ON");
  delay(1000);

  // Gửi lệnh tắt LED
  node.writeSingleRegister(0x0000, 0);
  Serial.println("LED OFF");
  delay(1000);
}
