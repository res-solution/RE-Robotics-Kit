#define POT_PIN 34
#define CLK_PIN 16
#define DT_PIN 4
#define SW_PIN 17

volatile int encoderCounter = 0;

// Fungsi Interupsi (Interrupt) untuk membaca putaran Rotary Encoder
void IRAM_ATTR readEncoder() {
  if (digitalRead(DT_PIN) == HIGH) {
    encoderCounter++; // Putar ke kanan (Clockwise)
  } else {
    encoderCounter--; // Putar ke kiri (Counter-Clockwise)
  }
}

void setup() {
  Serial.begin(115200);
  
  pinMode(CLK_PIN, INPUT_PULLUP);
  pinMode(DT_PIN, INPUT_PULLUP);
  pinMode(SW_PIN, INPUT_PULLUP);
  
  // Panggil fungsi readEncoder setiap kali sinyal CLK berubah dari HIGH ke LOW (FALLING)
  attachInterrupt(digitalPinToInterrupt(CLK_PIN), readEncoder, FALLING);
}

void loop() {
  if (digitalRead(SW_PIN) == LOW) {
    Serial.println("Tombol Encoder Ditekan! Mereset nilai menjadi 0.");
    encoderCounter = 0; // Reset nilai putaran ketika tombol ditekan
    delay(200); // Debounce sederhana
  }

  int potValue = analogRead(POT_PIN);
  Serial.print("Potensiometer: ");
  Serial.print(potValue);
  Serial.print(" | Posisi Encoder: ");
  Serial.println(encoderCounter);
  
  delay(100);
}