int pinA = 22, pinB = 5, pinC = 2, pinD = 12, pinE = 21, pinF = 13, pinG = 15, pinDP = 0;
int digitPins[] = {14, 23, 19, 18}; // Pin kontrol untuk Digit 1 hingga 4

void setup() {
  int segmentPins[] = {pinA, pinB, pinC, pinD, pinE, pinF, pinG};
  for(int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
  
  // Inisialisasi pin kontrol digit
  for(int i = 0; i < 4; i++) {
    pinMode(digitPins[i], OUTPUT);
    digitalWrite(digitPins[i], HIGH); // Aktifkan digit (Asumsi Common Cathode, beri HIGH jika Common Anode)
  }
}

void loop() {
  // Tampilkan angka 8 (Semua segment menyala)
  digitalWrite(pinA, HIGH); digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH); digitalWrite(pinD, HIGH);
  digitalWrite(pinE, HIGH); digitalWrite(pinF, HIGH);
  digitalWrite(pinG, HIGH); digitalWrite(pinDP, HIGH);
  delay(1000);
  
  // Tampilkan angka 1 (Hanya B dan C menyala)
  digitalWrite(pinA, LOW); digitalWrite(pinB, HIGH);
  digitalWrite(pinC, HIGH); digitalWrite(pinD, LOW);
  digitalWrite(pinE, LOW); digitalWrite(pinF, LOW);
  digitalWrite(pinG, LOW); digitalWrite(pinDP, LOW);
  delay(1000);
}