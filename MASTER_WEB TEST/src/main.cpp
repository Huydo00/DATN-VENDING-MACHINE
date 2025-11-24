#include <Arduino.h>
#include <ModbusMaster.h>
#include <SoftwareSerial.h>

// -------------- RS‑485 pins ----------------
#define MAX485_DE_RE D3         // D0 = GPIO16   (DE+RE)
// SoftwareSerial: RX, TX
SoftwareSerial RS485Serial(4, 5);  // D2 = GPIO4 (RX), D1 = GPIO5 (TX)

// -------------- ModbusMaster object --------
ModbusMaster node;

// ---------------- Helpers ------------------
void preTransmission()  { digitalWrite(MAX485_DE_RE, HIGH); }
void postTransmission() { digitalWrite(MAX485_DE_RE, LOW);  }

// ---------------- Setup --------------------
void setup()
{
  // RS‑485 direction control
  pinMode(MAX485_DE_RE, OUTPUT);
  digitalWrite(MAX485_DE_RE, LOW);        // start in receive mode

  // RS‑485 serial port
  RS485Serial.begin(9600);                // must match slave

  // Modbus Master initialisation
  node.begin(1, RS485Serial);             // Slave‑ID = 1
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);

  // Debug USB
  Serial.begin(115200);
  Serial.println("\nESP8266 Modbus Master – LED ON/OFF demo");
}

// ---------------- Loop ---------------------
void loop()
{
  digitalWrite(MAX485_DE_RE, HIGH);
  uint8_t result;

  /* ---- BẬT LED ---- */
  result = node.writeSingleRegister(0x0000, 1);   // regs[0] = 1
  if (result == node.ku8MBSuccess)
    Serial.println("LED ON – write OK");
  else
    Serial.printf("LED ON – error code %u\n", result);

  delay(1000);

  /* ---- TẮT LED ---- */
  result = node.writeSingleRegister(0x0000, 0);   // regs[0] = 0
  if (result == node.ku8MBSuccess)
    Serial.println("LED OFF – write OK");
  else
    Serial.printf("LED OFF – error code %u\n", result);

  delay(1000);
}