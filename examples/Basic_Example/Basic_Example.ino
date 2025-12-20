/*
  Exemples d'utilisation de LED_BUILTIN.h
  ----
  SET_LED_BUILTIN_PIN(4);  // Utilise GPIO4 au lieu de la détection automatique
  ----
  #define LED_BUILTIN_POLARITY 0  // Force LOW active (0=ON, 1=OFF)
  #include "LED_BUILTIN.h"
  ----
  #elif defined(MY_CUSTOM_BOARD)
  #undef LED_BUILTIN
  #define LED_BUILTIN 5  // GPIO5 pour votre carte
  ----
  Cette librairie offre plusieurs fonctions de clignotement :
  
  1. LED_BUILTIN_BLINK(delay_ms, count)
     - Rapport cyclique 50%
     - delay_ms: temps ON et OFF
     
  2. LED_BUILTIN_BLINK_DUTY(period_ms, duty_cycle, count)
     - Rapport cyclique personnalisable (0.0 à 1.0)
     - period_ms: temps total d'un cycle
     
  3. LED_BUILTIN_BLINK_TIMING(on_time_ms, off_time_ms, count)
     - Temps ON et OFF indépendants
     
  4. LED_BUILTIN_BLINK_FREQ(freq_hz, duty_cycle, duration_ms)
     - Contrôle par fréquence
     
  5. LED_BUILTIN_BLINK_PATTERN(pattern, times, length, repeat)
     - Motif personnalisé
     
  6. LED_BUILTIN_SOS()
     - Signal SOS prédéfini
	 
*/

#include <Arduino.h>
#include "LED_BUILTIN.h"
/*
void setup() 
{
  Serial.begin(115200);
  
  delay(2000);
  Serial.println("\nDebut");

  //Serial.print("\n11.5V >>"), Serial.println(charge);
}
*/
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
  ENABLE_LED_BUILTIN(); // Initialise la LED
  
  Serial.println("\nDémarrage des tests LED_BUILTIN");
  
  LED_BUILTIN_ON();      // Allume la LED
  delay(1000);
  LED_BUILTIN_OFF();     // Éteint la LED
  delay(1000);
  LED_BUILTIN_TOGGLE();  // Alterne l'état
  delay(1000);
  // 3 cycles de 500ms ON / 500ms OFF
  LED_BUILTIN_BLINK(500, 3);
  delay(1000);
  
  // 100ms ON, 900ms OFF, 5 cycles
  LED_BUILTIN_BLINK_TIMING(100, 900, 5);
  delay(1000);
  
  // Période 1000ms, 25% ON (250ms ON, 750ms OFF), 3 cycles
  LED_BUILTIN_BLINK_DUTY(1000, 0.25, 3);
  delay(1000);
  
  testDutyCycleVariations();
  delay(2000);
  
  testDifferentFrequencies();
  delay(2000);
  
  // 2Hz, 30% de rapport cyclique, pendant 5 secondes
  LED_BUILTIN_BLINK_FREQ(2.0, 0.3, 5000);
  delay(2000);
  
  uint8_t pattern[] = {1, 0, 1, 0, 1};  // ON, OFF, ON, OFF, ON
  uint16_t times[] = {100, 200, 100, 200, 300};
  LED_BUILTIN_BLINK_PATTERN(pattern, times, 5, 2);  // Répété 2 fois
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

  Serial.println("=== signal SOS ===");
}


void loop() {
 LED_BUILTIN_SOS();  // Émet un signal SOS (---...---)
}
