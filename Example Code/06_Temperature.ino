#include "DHT.h"

#define DHT_PIN 17 // Gunakan pin 17 karena mendukung I/O dua arah
#define DHT_TYPE DHT11
#define LM35_PIN 32

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  // Pembacaan sensor LM35 (Analog)
  // Menggunakan analogReadMilliVolts untuk mendapatkan nilai mV yang terkalibrasi pabrik (eFuse)
  float voltage_mV = analogReadMilliVolts(LM35_PIN);
  float tempLM35 = voltage_mV / 10.0;         // 10mV per derajat Celcius
  
  // Pembacaan sensor DHT11 (Digital)
  float tempDHT = dht.readTemperature();
  float humDHT = dht.readHumidity();

  Serial.print("Suhu LM35: ");
  Serial.print(tempLM35);
  
  // Cek apakah pembacaan DHT berhasil
  if (isnan(tempDHT) || isnan(humDHT)) {
    Serial.println(" C | Gagal membaca dari sensor DHT11!");
  } else {
    Serial.print(" C | Suhu DHT11: ");
    Serial.print(tempDHT);
    Serial.print(" C | Kelembaban DHT11: ");
    Serial.print(humDHT);
    Serial.println(" %");
  }
  
  delay(2000); // DHT11 butuh jeda waktu minimal 2 detik antar pembacaan
}