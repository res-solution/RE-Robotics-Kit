#define LED_PIN 2

// Array untuk menyimpan pin dari ke-4 tombol
const int buttonPins[] = {16, 4, 17, 32};
const int numButtons = 4;

// Menyimpan status sebelumnya untuk setiap tombol dan status LED
int lastButtonState[] = {HIGH, HIGH, HIGH, HIGH};
bool ledState = false;

void setup() {
  Serial.begin(115200);
  Serial.println("Program Tombol dan LED dimulai. Tekan tombol untuk mengubah status LED.");
  pinMode(LED_PIN, OUTPUT);
  
  for (int i = 0; i < numButtons; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}

void loop() {
  for (int i = 0; i < numButtons; i++) {
    int currentState = digitalRead(buttonPins[i]);
    
    // Deteksi jika tombol baru saja ditekan (transisi dari HIGH ke LOW)
    if (currentState == LOW && lastButtonState[i] == HIGH) {
      ledState = !ledState; // Balikkan status LED (Toggle)
      digitalWrite(LED_PIN, ledState);
      
      Serial.print("Tombol di pin ");
      Serial.print(buttonPins[i]);
      Serial.println(" ditekan. LED di-toggle!");
      
      delay(50); // Jeda singkat untuk debouncing
    }
    
    // Simpan status saat ini untuk iterasi berikutnya
    lastButtonState[i] = currentState;
  }
}