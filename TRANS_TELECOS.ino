#include <SPI.h>
#include <LoRa.h>

//define the pins used by the transceiver module
#define ss 5
#define rst 14
#define dio0 4

int counter = 0;

const int LED_BUILTIN = 2;

void setup() {
  //setup led
  pinMode(LED_BUILTIN, OUTPUT);
  //initialize Serial Monitor
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Transmisor LoRa");

  //setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);
  
  //replace the LoRa.begin(---E-) argument with your location's frequency 
  //868E6 for Spain
  while (!LoRa.begin(868E6)) {
    Serial.println(".");
    delay(500);
  }
   // Change sync word (0xF3) to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  LoRa.setSyncWord(0xF3);
  Serial.println("Inicializacion LoRa OK!");
}

void loop() {
  Serial.print("Enviando paquete: ");
  Serial.println(counter);

  //Send LoRa packet to receiver
  LoRa.beginPacket();
  LoRa.print("hola ");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(9000);
}
