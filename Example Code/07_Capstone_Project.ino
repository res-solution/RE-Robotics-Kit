#include "DHT.h"

#define DHT_PIN 17
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);

// Konfigurasi Pin 7-Segment
const int pinA = 22, pinB = 5, pinC = 2, pinD = 12, pinE = 21, pinF = 13, pinG = 15;
const int segmentPins[] = {pinA, pinB, pinC, pinD, pinE, pinF, pinG};
const int digitPins[] = {14, 23, 19, 18}; // D1, D2, D3, D4

// Pola angka 0-9 untuk 7-Segment (1 = Nyala, 0 = Mati)
const byte numbers[10][7] = {
  {1,1,1,1,1,1,0}, // 0
  {0,1,1,0,0,0,0}, // 1
  {1,1,0,1,1,0,1}, // 2
  {1,1,1,1,0,0,1}, // 3
  {0,1,1,0,0,1,1}, // 4
  {1,0,1,1,0,1,1}, // 5
  {1,0,1,1,1,1,1}, // 6
  {1,1,1,0,0,0,0}, // 7
  {1,1,1,1,1,1,1}, // 8
  {1,1,1,1,0,1,1}  // 9
};

int currentTemp = 0;
int currentHum = 0;
unsigned long lastMillis = 0;

void setup() {
  Serial.begin(115200);
  dht.begin();
  
  // Inisialisasi pin kontrol 7-Segment
  for(int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
  for(int i = 0; i < 4; i++) {
    pinMode(digitPins[i], OUTPUT);
    digitalWrite(digitPins[i], LOW);  // Matikan digit (LOW = Mati)
  }
}

void displayDigit(int digitIndex, int number) {
  // Matikan semua digit agar angka dari digit sebelumnya tidak tumpang tindih (ghosting)
  for(int i = 0; i < 4; i++) digitalWrite(digitPins[i], LOW);
  
  // Set nilai A-G sesuai pola dari array (1 = Nyala, 0 = Mati)
  // Berdasarkan tes 7Segment.cpp, segmen menyala dengan sinyal HIGH
  for(int i = 0; i < 7; i++) digitalWrite(segmentPins[i], numbers[number][i]);
  
  // Nyalakan digit yang kita inginkan (HIGH = Nyala)
  digitalWrite(digitPins[digitIndex], HIGH);
  delay(5); // Multiplexing delay (waktu tampil per digit)

  // Matikan kembali digit setelah delay untuk menghindari ghosting antar digit
  digitalWrite(digitPins[digitIndex], LOW);
}

void loop() {
  // Baca DHT11 setiap 2000 ms tanpa memblokir perulangan layar multiplexing
  if (millis() - lastMillis >= 2000) {
    lastMillis = millis();
    
    // PENTING: Matikan layar sementara saat membaca DHT.
    // Sensor DHT mem-blokir program ~250ms. Jika layar tidak dimatikan,
    // digit terakhir akan menyangkut (nyala terus) dan merusak tampilan keseluruhan.
    for(int i = 0; i < 4; i++) digitalWrite(digitPins[i], LOW);

    float t = dht.readTemperature();
    float h = dht.readHumidity();
    
    if (!isnan(t) && !isnan(h)) {
      // Gunakan abs() untuk mencegah nilai negatif yang bisa membuat indeks array
      // menjadi negatif (misal numbers[-1]) yang sering tampil acak sebagai angka 8.
      currentTemp = abs(round(t));
      currentHum = abs(round(h));

      // Kirimkan juga nilai ke Serial Monitor
      Serial.print("Suhu: ");
      Serial.print(currentTemp);
      Serial.print(" C, Kelembapan: ");
      Serial.print(currentHum);
      Serial.println(" %");
    }
  }
  
  // Ekstrak dan tampilkan masing-masing digit (D1 & D2 = Suhu, D3 & D4 = Kelembapan)
  displayDigit(0, (currentTemp / 10) % 10);
  displayDigit(1, currentTemp % 10);
  displayDigit(2, (currentHum / 10) % 10);
  displayDigit(3, currentHum % 10);
}