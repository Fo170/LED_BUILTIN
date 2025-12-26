/*
  LED_BUILTIN.h - Exemples d'utilisation (Version 2.0 Non-Bloquante)
  
  ============================================================================
  IMPORTANT : Cette version utilise millis() au lieu de delay()
  Vous DEVEZ appeler LED_BUILTIN_UPDATE() dans votre loop() !
  ============================================================================
  
  Configuration personnalisée (optionnel) :
  ----
  // Forcer un GPIO spécifique
  #define LED_BUILTIN 4
  #include "LED_BUILTIN.h"
  ----
  // Forcer la polarité
  #define LED_BUILTIN_POLARITY 0  // 0=LOW active (inversée), 1=HIGH active
  #include "LED_BUILTIN.h"
  ----
  // Mode compatibilité (comportement bloquant comme v1.0)
  #define LED_BUILTIN_COMPATIBILITY_MODE
  #include "LED_BUILTIN.h"
  ----
  
  Fonctions disponibles (mode non-bloquant) :
  
  1. LED_BUILTIN_BLINK_START(delay_ms, count)
     - Rapport cyclique 50%
     - Appeler LED_BUILTIN_UPDATE() dans loop()
     
  2. LED_BUILTIN_BLINK_DUTY_START(period_ms, duty_cycle, count)
     - Rapport cyclique personnalisable (0.0 à 1.0)
     
  3. LED_BUILTIN_BLINK_TIMING_START(on_time_ms, off_time_ms, count)
     - Temps ON et OFF indépendants
     
  4. LED_BUILTIN_BLINK_FREQ_START(freq_hz, duty_cycle, duration_ms)
     - Contrôle par fréquence
     
  5. LED_BUILTIN_BLINK_PATTERN_START(pattern, times, length, repeat)
     - Motif personnalisé
     
  6. LED_BUILTIN_SOS_START()
     - Signal SOS prédéfini
     
  7. LED_BUILTIN_UPDATE()
     - À appeler dans loop() - OBLIGATOIRE !
     
  Fonctions de contrôle :
  - LED_BUILTIN_STOP() : Arrête l'animation en cours
  - LED_BUILTIN_IS_ACTIVE() : Vérifie si une animation est active
  
  Support LED RGB (M5Stack ATOM, etc.) :
  - LED_RGB_SET_COLOR(r, g, b, brightness)
  - LED_RGB_RED(), LED_RGB_GREEN(), LED_RGB_BLUE(), etc.
  - LED_RGB_ON(), LED_RGB_OFF()
*/

#include <Arduino.h>
#include "LED_BUILTIN.h"

// ============================================================================
// VARIABLES GLOBALES POUR LA GESTION DES ÉTATS
// ============================================================================
enum TestState {
  TEST_INIT,
  TEST_BASIC,
  TEST_DUTY_CYCLE,
  TEST_FREQUENCIES,
  TEST_PATTERN,
  TEST_MORSE,
  TEST_SOS,
  TEST_COMPLETE
};

TestState currentTest = TEST_INIT;
unsigned long testStartTime = 0;
unsigned long stateStartTime = 0;
uint8_t subTestIndex = 0;

// ============================================================================
// EXEMPLE 1 : UTILISATION DE BASE NON-BLOQUANTE
// ============================================================================
void example_basic_nonblocking() {
  Serial.println("\n=== Exemple 1 : Utilisation de base ===");
  
  ENABLE_LED_BUILTIN();
  
  // Démarre 5 clignotements de 500ms
  LED_BUILTIN_BLINK_START(500, 5);
  
  Serial.println("LED clignote en arrière-plan...");
  Serial.println("Le programme continue normalement !");
}

// ============================================================================
// EXEMPLE 2 : INDICATEUR D'ÉTAT RÉSEAU
// ============================================================================
bool networkConnected = false;
unsigned long lastNetworkToggle = 0;

void example_network_indicator() {
  // Simule un changement d'état réseau toutes les 10 secondes
  if(millis() - lastNetworkToggle > 10000) {
    networkConnected = !networkConnected;
    lastNetworkToggle = millis();
    
    Serial.print("État réseau changé : ");
    Serial.println(networkConnected ? "Connecté" : "Déconnecté");
  }
  
  // Adapte le clignotement selon l'état
  if(networkConnected) {
    if(!LED_BUILTIN_IS_ACTIVE()) {
      // Connecté : clignotement lent (100ms ON, 2900ms OFF)
      LED_BUILTIN_BLINK_TIMING_START(100, 2900, 255);
    }
  } else {
    if(!LED_BUILTIN_IS_ACTIVE()) {
      // Déconnecté : clignotement rapide
      LED_BUILTIN_BLINK_START(200, 255);
    }
  }
}

// ============================================================================
// EXEMPLE 3 : UTILISATION AVEC LED RGB (M5Stack ATOM)
// ============================================================================
#ifdef LED_BUILTIN_IS_RGB
void example_rgb_colors() {
  Serial.println("\n=== Exemple RGB : Changement de couleurs ===");
  
  static uint8_t colorIndex = 0;
  static unsigned long lastColorChange = 0;
  
  if(millis() - lastColorChange > 2000) {
    lastColorChange = millis();
    
    switch(colorIndex) {
      case 0:
        LED_RGB_RED();
        Serial.println("Couleur : ROUGE");
        break;
      case 1:
        LED_RGB_GREEN();
        Serial.println("Couleur : VERT");
        break;
      case 2:
        LED_RGB_BLUE();
        Serial.println("Couleur : BLEU");
        break;
      case 3:
        LED_RGB_YELLOW();
        Serial.println("Couleur : JAUNE");
        break;
      case 4:
        LED_RGB_CYAN();
        Serial.println("Couleur : CYAN");
        break;
      case 5:
        LED_RGB_MAGENTA();
        Serial.println("Couleur : MAGENTA");
        break;
      case 6:
        LED_RGB_WHITE();
        Serial.println("Couleur : BLANC");
        break;
      case 7:
        LED_RGB_ORANGE();
        Serial.println("Couleur : ORANGE");
        break;
      case 8:
        LED_RGB_PURPLE();
        Serial.println("Couleur : VIOLET");
        break;
    }
    
    LED_BUILTIN_BLINK_START(200, 3);
    
    colorIndex++;
    if(colorIndex > 8) colorIndex = 0;
  }
}
#endif

// ============================================================================
// TESTS SÉQUENTIELS
// ============================================================================
void testDutyCycleVariations() {
  static float duty = 0.1f;
  const unsigned long DISPLAY_INTERVAL = 2500;
  
  if(subTestIndex == 0) {
    Serial.println("\n=== Test des rapports cycliques ===");
    Serial.print("Duty cycle: ");
    Serial.print(duty * 100, 0);
    Serial.println("%");
    
    LED_BUILTIN_BLINK_DUTY_START(1000, duty, 2);
    stateStartTime = millis();
    subTestIndex++;
  }
  
  if(millis() - stateStartTime > DISPLAY_INTERVAL && !LED_BUILTIN_IS_ACTIVE()) {
    duty += 0.2f;
    
    if(duty <= 0.9f) {
      Serial.print("Duty cycle: ");
      Serial.print(duty * 100, 0);
      Serial.println("%");
      
      LED_BUILTIN_BLINK_DUTY_START(1000, duty, 2);
      stateStartTime = millis();
    } else {
      // Test terminé
      duty = 0.1f;
      subTestIndex = 0;
      currentTest = TEST_FREQUENCIES;
      Serial.println("Test duty cycle terminé\n");
    }
  }
}

void testDifferentFrequencies() {
  static float freq = 1.0f;
  const unsigned long DISPLAY_INTERVAL = 2500;
  
  if(subTestIndex == 0) {
    Serial.println("=== Test des fréquences ===");
    Serial.print("Fréquence: ");
    Serial.print(freq, 1);
    Serial.println(" Hz");
    
    LED_BUILTIN_BLINK_FREQ_START(freq, 0.3, 2000);
    stateStartTime = millis();
    subTestIndex++;
  }
  
  if(millis() - stateStartTime > DISPLAY_INTERVAL && !LED_BUILTIN_IS_ACTIVE()) {
    freq += 2.0f;
    
    if(freq <= 10.0f) {
      Serial.print("Fréquence: ");
      Serial.print(freq, 1);
      Serial.println(" Hz");
      
      LED_BUILTIN_BLINK_FREQ_START(freq, 0.3, 2000);
      stateStartTime = millis();
    } else {
      // Test terminé
      freq = 1.0f;
      subTestIndex = 0;
      currentTest = TEST_PATTERN;
      Serial.println("Test fréquences terminé\n");
    }
  }
}

void testPattern() {
  if(subTestIndex == 0) {
    Serial.println("=== Test Pattern personnalisé ===");
    
    static const uint8_t pattern[] = {1, 0, 1, 0, 1};
    static const uint16_t times[] = {100, 200, 100, 200, 300};
    
    LED_BUILTIN_BLINK_PATTERN_START(pattern, times, 5, 2);
    stateStartTime = millis();
    subTestIndex++;
  }
  
  if(millis() - stateStartTime > 3000 && !LED_BUILTIN_IS_ACTIVE()) {
    subTestIndex = 0;
    currentTest = TEST_MORSE;
    Serial.println("Test pattern terminé\n");
  }
}

void testMorse() {
  static uint8_t morseStep = 0;
  
  if(subTestIndex == 0) {
    Serial.println("=== Morse: HELLO ===");
    subTestIndex++;
    morseStep = 0;
    stateStartTime = millis();
  }
  
  if(!LED_BUILTIN_IS_ACTIVE() && millis() - stateStartTime > 300) {
    switch(morseStep) {
      case 0: // H: ....
        Serial.println("H: ....");
        LED_BUILTIN_BLINK_START(100, 4);
        break;
        
      case 1: // E: .
        Serial.println("E: .");
        LED_BUILTIN_BLINK_START(100, 1);
        break;
        
      case 2: // L: .-.. (partie 1)
        Serial.println("L: .-..");
        LED_BUILTIN_BLINK_START(100, 1);
        break;
      case 3: // L: .-.. (partie 2 - long)
        LED_BUILTIN_BLINK_START(300, 1);
        break;
      case 4: // L: .-.. (partie 3 - 2 courts)
        LED_BUILTIN_BLINK_START(100, 2);
        break;
        
      case 5: // L: .-.. (répétition)
        Serial.println("L: .-..");
        LED_BUILTIN_BLINK_START(100, 1);
        break;
      case 6:
        LED_BUILTIN_BLINK_START(300, 1);
        break;
      case 7:
        LED_BUILTIN_BLINK_START(100, 2);
        break;
        
      case 8: // O: ---
        Serial.println("O: ---");
        LED_BUILTIN_BLINK_START(300, 3);
        break;
        
      default:
        subTestIndex = 0;
        morseStep = 0;
        currentTest = TEST_SOS;
        Serial.println("Test morse terminé\n");
        return;
    }
    
    morseStep++;
    stateStartTime = millis();
  }
}

// ============================================================================
// SETUP
// ============================================================================
void setup() {
  Serial.begin(115200);
  delay(100);
  
  Serial.println("\n\n========================================");
  Serial.println("  LED_BUILTIN v2.0 - Exemples");
  Serial.println("  Mode Non-Bloquant");
  Serial.println("========================================\n");
  
  // Initialisation
  ENABLE_LED_BUILTIN();
  
  #ifdef LED_BUILTIN_IS_RGB
    Serial.println("LED RGB détectée !");
    LED_RGB_WHITE();  // Couleur par défaut
  #endif
  
  Serial.print("LED_BUILTIN sur GPIO: ");
  Serial.println(LED_BUILTIN);
  
  Serial.print("Polarité: ");
  Serial.println(LED_BUILTIN_POLARITY ? "HIGH active" : "LOW active (inversée)");
  
  Serial.println("\nDémarrage des tests...\n");
  
  testStartTime = millis();
  currentTest = TEST_BASIC;
  stateStartTime = millis();
}

// ============================================================================
// LOOP - MACHINE À ÉTATS NON-BLOQUANTE
// ============================================================================
void loop() {
  // OBLIGATOIRE : Met à jour l'état de la LED
  LED_BUILTIN_UPDATE();
  
  // Machine à états pour les tests séquentiels
  switch(currentTest) {
    case TEST_BASIC:
      if(subTestIndex == 0) {
        Serial.println("=== Test de base ===");
        Serial.println("ON pendant 1 seconde...");
        LED_BUILTIN_ON();
        stateStartTime = millis();
        subTestIndex++;
      } else if(subTestIndex == 1 && millis() - stateStartTime > 1000) {
        Serial.println("OFF pendant 1 seconde...");
        LED_BUILTIN_OFF();
        stateStartTime = millis();
        subTestIndex++;
      } else if(subTestIndex == 2 && millis() - stateStartTime > 1000) {
        Serial.println("TOGGLE...");
        LED_BUILTIN_TOGGLE();
        stateStartTime = millis();
        subTestIndex++;
      } else if(subTestIndex == 3 && millis() - stateStartTime > 1000) {
        Serial.println("3 clignotements de 500ms...");
        LED_BUILTIN_BLINK_START(500, 3);
        stateStartTime = millis();
        subTestIndex++;
      } else if(subTestIndex == 4 && !LED_BUILTIN_IS_ACTIVE() && millis() - stateStartTime > 2500) {
        Serial.println("Blink timing: 100ms ON, 900ms OFF, 5 fois...");
        LED_BUILTIN_BLINK_TIMING_START(100, 900, 5);
        stateStartTime = millis();
        subTestIndex++;
      } else if(subTestIndex == 5 && !LED_BUILTIN_IS_ACTIVE() && millis() - stateStartTime > 6000) {
        Serial.println("Duty cycle 25%: 250ms ON, 750ms OFF, 3 fois...");
        LED_BUILTIN_BLINK_DUTY_START(1000, 0.25, 3);
        stateStartTime = millis();
        subTestIndex++;
      } else if(subTestIndex == 6 && !LED_BUILTIN_IS_ACTIVE() && millis() - stateStartTime > 4000) {
        subTestIndex = 0;
        currentTest = TEST_DUTY_CYCLE;
        Serial.println("Test de base terminé\n");
      }
      break;
      
    case TEST_DUTY_CYCLE:
      testDutyCycleVariations();
      break;
      
    case TEST_FREQUENCIES:
      testDifferentFrequencies();
      break;
      
    case TEST_PATTERN:
      testPattern();
      break;
      
    case TEST_MORSE:
      testMorse();
      break;
      
    case TEST_SOS:
      if(subTestIndex == 0) {
        Serial.println("=== Signal SOS ===");
        Serial.println("...---...");
        LED_BUILTIN_SOS_START();
        stateStartTime = millis();
        subTestIndex++;
      } else if(!LED_BUILTIN_IS_ACTIVE() && millis() - stateStartTime > 2000) {
        subTestIndex = 0;
        currentTest = TEST_COMPLETE;
        Serial.println("Signal SOS terminé\n");
      }
      break;
      
    case TEST_COMPLETE:
      if(subTestIndex == 0) {
        Serial.println("\n========================================");
        Serial.println("  TOUS LES TESTS TERMINÉS !");
        Serial.println("========================================");
        Serial.print("Durée totale: ");
        Serial.print((millis() - testStartTime) / 1000);
        Serial.println(" secondes\n");
        
        #ifdef LED_BUILTIN_IS_RGB
          Serial.println("Démonstration LED RGB en continu...");
        #else
          Serial.println("Clignotement continu...");
        #endif
        
        subTestIndex++;
      }
      
      // Boucle infinie de démonstration
      #ifdef LED_BUILTIN_IS_RGB
        example_rgb_colors();
      #else
        if(!LED_BUILTIN_IS_ACTIVE()) {
          LED_BUILTIN_BLINK_START(1000, 1);
        }
      #endif
      break;
  }
  
  // Démonstration : votre code peut s'exécuter normalement ici
  // La LED continue de clignoter en arrière-plan !
  
  // Exemple : lecture de capteur, communication série, etc.
  static unsigned long lastPrint = 0;
  if(millis() - lastPrint > 5000) {
    Serial.print(".");
    lastPrint = millis();
  }
}

// ============================================================================
// EXEMPLES BONUS : FONCTIONS UTILITAIRES
// ============================================================================

/*
// Exemple : Indicateur de progression
void showProgress(uint8_t percent) {
  LED_BUILTIN_STOP();
  
  if(percent < 100) {
    // Clignotement proportionnel au progrès
    uint16_t on_time = map(percent, 0, 100, 100, 900);
    uint16_t off_time = 1000 - on_time;
    LED_BUILTIN_BLINK_TIMING_START(on_time, off_time, 255);
  } else {
    LED_BUILTIN_ON();  // Allumé en continu à 100%
  }
}

// Exemple : Codes d'erreur
void showError(uint8_t errorCode) {
  LED_BUILTIN_STOP();
  
  #ifdef LED_BUILTIN_IS_RGB
    LED_RGB_RED();  // Rouge pour erreur
  #endif
  
  // Clignote N fois selon le code d'erreur
  LED_BUILTIN_BLINK_START(300, errorCode);
}

// Exemple : Mode veille
void enterSleepMode() {
  LED_BUILTIN_STOP();
  LED_BUILTIN_BLINK_TIMING_START(50, 9950, 255);  // Un flash toutes les 10s
}

// Exemple : Heartbeat
void heartbeat() {
  if(!LED_BUILTIN_IS_ACTIVE()) {
    static const uint8_t hb_pattern[] = {1, 0, 1, 0};
    static const uint16_t hb_times[] = {100, 100, 100, 2700};
    LED_BUILTIN_BLINK_PATTERN_START(hb_pattern, hb_times, 4, 255);
  }
}
*/