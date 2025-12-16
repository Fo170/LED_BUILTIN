#include "LED_BUILTIN.h"

void testDutyCycleVariations() {
  Serial.println("=== Test des rapports cycliques ===");
  
  // Rapport cyclique de 10% à 90% par pas de 20%
  for(float duty = 0.1f; duty <= 0.9f; duty += 0.2f) {
    Serial.print("Duty cycle: ");
    Serial.println(duty * 100);
    Serial.print("%");
    
    LED_BUILTIN_BLINK_DUTY(1000, duty, 2);
    delay(500);
  }
}

void testDifferentFrequencies() {
  Serial.println("=== Test des fréquences ===");
  
  // Fréquences de 1Hz à 10Hz
  for(float freq = 1.0f; freq <= 10.0f; freq += 2.0f) {
    Serial.print("Fréquence: ");
    Serial.print(freq);
    Serial.println(" Hz");
    
    LED_BUILTIN_BLINK_FREQ(freq, 0.3, 2000);  // 30% de rapport cyclique
    delay(500);
  }
}

void setup() {
  Serial.begin(115200);
  ENABLE_LED_BUILTIN();
  
  Serial.println("Démarrage des tests LED_BUILTIN");
  delay(1000);
}

void loop() {
  testDutyCycleVariations();
  delay(2000);
  
  testDifferentFrequencies();
  delay(2000);
  
  // Exemple de motif Morse pour "HELLO"
  Serial.println("=== Morse: HELLO ===");
  
  // H: ....
  LED_BUILTIN_BLINK(100, 4);
  delay(300);
  
  // E: .
  LED_BUILTIN_BLINK(100, 1);
  delay(300);
  
  // L: .-..
  LED_BUILTIN_BLINK(100, 1);  // Court
  delay(100);
  LED_BUILTIN_BLINK(300, 1);  // Long
  delay(100);
  LED_BUILTIN_BLINK(100, 2);  // 2 courts
  delay(300);
  
  // L: .-..
  LED_BUILTIN_BLINK(100, 1);
  delay(100);
  LED_BUILTIN_BLINK(300, 1);
  delay(100);
  LED_BUILTIN_BLINK(100, 2);
  delay(300);
  
  // O: ---
  LED_BUILTIN_BLINK(300, 3);
  
  delay(3000);
}