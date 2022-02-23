#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

/*#include <SPI.h>
#define BME_SCK 18
#define BME_MISO 19
#define BME_MOSI 23
#define BME_CS 5*/

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

unsigned long delayTime;

void setup() {
  Serial.begin(115200);
  Serial.println(F("BME280 test"));
  
  bool status;

  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  status = bme.begin(0x76);  
  if (!status) {
    Serial.println("No se pudo encontrar un sensor BME280 valido, comprueba el cableado!");
    while (1);
  }

  Serial.println("-- Test --");
  delayTime = 1000;

  Serial.println();
}

void printBME280() {
  Serial.print("Temperatura = ");
  Serial.print(bme.readTemperature());
  Serial.println(" *C");
  
  Serial.print("Presion = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.print("Altitud = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.print("Humedad = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.println();
  }

void loop() { 
  printBME280();
  delay(delayTime);
}
