#define POT_PIN 32

int ledPins[] = {15, 2, 0, 12, 21, 22, 13, 5, 14};
int numLeds = 9;

int buttonPins[] = {16, 4, 17};
int numButtons = 3;

void setup() {
  Serial.begin(115200);
  
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  
  for (int i = 0; i < numButtons; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}

void loop() {
  int potValue = analogRead(POT_PIN);
  Serial.print("Potensiometer: ");
  Serial.print(potValue);
  
  // Print status dari masing-masing tombol
  for (int i = 0; i < numButtons; i++) {
    Serial.print(" | Tombol ");
    Serial.print(buttonPins[i]);
    Serial.print(": ");
    Serial.print(digitalRead(buttonPins[i]));
  }
  Serial.println(); // Pindah baris di Serial Monitor
  
  // Nyalakan semua LED
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
  delay(500);
  
  // Matikan semua LED
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  delay(500);
}