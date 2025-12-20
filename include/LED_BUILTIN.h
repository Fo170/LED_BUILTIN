/*
Choisissez la fonction qui correspond le mieux à votre besoin :

Pour un simple clignotement 50% : LED_BUILTIN_BLINK()

Pour un rapport cyclique spécifique : LED_BUILTIN_BLINK_DUTY()

Pour un contrôle précis des temps ON/OFF : LED_BUILTIN_BLINK_TIMING()

Pour un contrôle par fréquence : LED_BUILTIN_BLINK_FREQ()

Pour des motifs complexes : LED_BUILTIN_BLINK_PATTERN()
*/

/*
  Exemples d'utilisation de LED_BUILTIN.h
  
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
// LED_BUILTIN.h - Gestion complète des LED intégrées pour ESP8266/ESP32
// Définitions des GPIO pour différentes cartes

// ============================================
// DÉTECTION DE LA PLATEFORME
// ============================================
#if defined(ESP8266)
  #define PLATFORM_ESP8266
#elif defined(ESP32)
  #define PLATFORM_ESP32
  #include <esp32/rom/rtc.h> // Pour détection du modèle ESP32
#endif

// ============================================
// DÉFINITIONS PAR DÉFAUT
// ============================================
#if defined(PLATFORM_ESP8266)
  // ESP8266 par défaut
  #ifndef LED_BUILTIN
    #define LED_BUILTIN 2  // GPIO2 (D4) - NodeMCU, Wemos D1 mini
  #endif
  
#elif defined(PLATFORM_ESP32)
  // ESP32 par défaut
  #ifndef LED_BUILTIN
    // Valeur par défaut pour ESP32 générique
    #define LED_BUILTIN 2
  #endif
#endif

// ============================================
// DÉTECTION SPÉCIFIQUE DES CARTES ESP32
// ============================================
#if defined(PLATFORM_ESP32)
  
  // Heltec Boards
  #if defined(HELTEC_WIFI_LORA_32) || defined(HELTEC_WIFI_LORA_32_V2)
    #undef LED_BUILTIN
    #define LED_BUILTIN 25  // LED blanche
  
  // TTGO Boards
  #elif defined(TTGO_T7_V14) || defined(TTGO_T7_MINI32)
    #undef LED_BUILTIN
    #define LED_BUILTIN 22
  
  #elif defined(TTGO_T_DISPLAY)
    #undef LED_BUILTIN
    #define LED_BUILTIN 4
  
  // Adafruit Boards
  #elif defined(ADAFRUIT_FEATHER_ESP32) || defined(ADAFRUIT_HUZZAH32)
    #undef LED_BUILTIN
    #define LED_BUILTIN 13
  
  // SparkFun Boards
  #elif defined(ESP32_THING)
    #undef LED_BUILTIN
    #define LED_BUILTIN 5
  
  #elif defined(ARDUINO_SPARKFUN_THING_PLUS)
    #undef LED_BUILTIN
    #define LED_BUILTIN 13
  
  // Wemos/Lolin Boards
  #elif defined(WEMOS_LOLIN32) || defined(LOLIN_D32)
    #undef LED_BUILTIN
    #define LED_BUILTIN 5
  
  #elif defined(WEMOS_D1_R32)
    #undef LED_BUILTIN
    #define LED_BUILTIN 2
  
  // M5Stack Boards
  #elif defined(ARDUINO_M5STACK_CORE2) || defined(ARDUINO_M5STACK_FIRE) || defined(ARDUINO_M5STACK_BASIC)
    #undef LED_BUILTIN
    #define LED_BUILTIN 2
  
  #elif defined(ARDUINO_M5STICK_C)
    #undef LED_BUILTIN
    #define LED_BUILTIN 10
  
  #elif defined(ARDUINO_M5STACK_ATOM)
    #undef LED_BUILTIN
    #define LED_BUILTIN 2  // LED RGB
  
  // ESP32-C3
  #elif defined(ESP32C3)
    #undef LED_BUILTIN
    #define LED_BUILTIN 8
  
  // ESP32-S2
  #elif defined(ESP32S2)
    #undef LED_BUILTIN
    #define LED_BUILTIN 18
  
  // ESP32-S3
  #elif defined(ESP32S3)
    #undef LED_BUILTIN
    #define LED_BUILTIN 48
  
  #endif
  
#endif // PLATFORM_ESP32

// ============================================
// DÉTECTION SPÉCIFIQUE DES CARTES ESP8266
// ============================================
#if defined(PLATFORM_ESP8266)
  
  // Certaines cartes ESP8266 utilisent GPIO16
  #if defined(ARDUINO_ESP8266_ESP01) || defined(ARDUINO_ESP8266_ESP12)
    #undef LED_BUILTIN
    #define LED_BUILTIN 2  // GPIO2 pour la plupart
  
  #elif defined(ARDUINO_ESP8266_NODEMCU)
    #undef LED_BUILTIN
    #define LED_BUILTIN 16  // Certaines versions
  
  #endif
  
#endif

// ============================================
// DÉFINITION DE LA POLARITÉ
// ============================================
// Pour permettre à l'utilisateur de surcharger la polarité
#ifndef LED_BUILTIN_POLARITY
  #if defined(PLATFORM_ESP8266)
    #define LED_BUILTIN_POLARITY 0  // 0 = LOW active, 1 = HIGH active
  #elif defined(PLATFORM_ESP32)
    // Vérifier les cartes spécifiques
    #if defined(HELTEC_WIFI_LORA_32) || defined(HELTEC_WIFI_LORA_32_V2) || \
        defined(ADAFRUIT_FEATHER_ESP32) || defined(ESP32_THING) || \
        defined(ARDUINO_SPARKFUN_THING_PLUS)
      #define LED_BUILTIN_POLARITY 1  // HIGH active
    #else
      #define LED_BUILTIN_POLARITY 1  // Par défaut HIGH active pour ESP32
    #endif
  #endif
#endif

// ============================================
// MACROS UTILITAIRES
// ============================================
#if LED_BUILTIN_POLARITY == 0
  #define __LED_BUILTIN_ON__   LOW
  #define __LED_BUILTIN_OFF__  HIGH
#else
  #define __LED_BUILTIN_ON__   HIGH
  #define __LED_BUILTIN_OFF__  LOW
#endif

// ============================================
// FONCTIONS DE BASE
// ============================================
void LED_BUILTIN_ON(void) {
  digitalWrite(LED_BUILTIN, __LED_BUILTIN_ON__);
}

void LED_BUILTIN_OFF(void) {
  digitalWrite(LED_BUILTIN, __LED_BUILTIN_OFF__);
}

void LED_BUILTIN_TOGGLE(void) {
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

void ENABLE_LED_BUILTIN(void) {
  pinMode(LED_BUILTIN, OUTPUT);
  LED_BUILTIN_OFF();  // Éteindre la LED par défaut
}
// ============================================
// FONCTIONS DE CLIGNOTEMENT AVEC RAPPORT CYCLIQUE
// ============================================

/**
 * @brief Clignotement simple avec rapport cyclique 50% (compatible)
 * @param delay_ms Durée d'un demi-cycle (ON ou OFF)
 * @param count Nombre de cycles (défaut: 1)
 */
void LED_BUILTIN_BLINK(uint16_t delay_ms, uint8_t count = 1) {
  for(uint8_t i = 0; i < count; i++) {
    LED_BUILTIN_ON();
    delay(delay_ms);
    LED_BUILTIN_OFF();
    if(i < count - 1) delay(delay_ms);
  }
}

/**
 * @brief Clignotement avec période et rapport cyclique personnalisés
 * @param period_ms Période totale en ms
 * @param duty_cycle Rapport cyclique (0.0 à 1.0)
 * @param count Nombre de cycles (défaut: 1)
 * 
 * Exemples:
 * - duty_cycle = 0.5 -> 50% ON, 50% OFF
 * - duty_cycle = 0.25 -> 25% ON, 75% OFF
 * - duty_cycle = 0.75 -> 75% ON, 25% OFF
 */
void LED_BUILTIN_BLINK_DUTY(uint16_t period_ms, float duty_cycle, uint8_t count = 1) {
  // Limiter le rapport cyclique entre 0 et 1
  if(duty_cycle < 0.0f) duty_cycle = 0.0f;
  if(duty_cycle > 1.0f) duty_cycle = 1.0f;
  
  uint16_t on_time = (uint16_t)(period_ms * duty_cycle);
  uint16_t off_time = period_ms - on_time;
  
  for(uint8_t i = 0; i < count; i++) {
    if(on_time > 0) {
      LED_BUILTIN_ON();
      delay(on_time);
    }
    
    if(off_time > 0) {
      LED_BUILTIN_OFF();
      if(i < count - 1 || on_time > 0) {
        delay(off_time);
      }
    }
  }
}

/**
 * @brief Clignotement avec temps ON et OFF séparés
 * @param on_time_ms Temps ON en ms
 * @param off_time_ms Temps OFF en ms
 * @param count Nombre de cycles (défaut: 1)
 */
void LED_BUILTIN_BLINK_TIMING(uint16_t on_time_ms, uint16_t off_time_ms, uint8_t count = 1) {
  for(uint8_t i = 0; i < count; i++) {
    LED_BUILTIN_ON();
    delay(on_time_ms);
    LED_BUILTIN_OFF();
    if(i < count - 1) delay(off_time_ms);
  }
}

/**
 * @brief Clignotement avec fréquence et rapport cyclique
 * @param freq_hz Fréquence en Hz
 * @param duty_cycle Rapport cyclique (0.0 à 1.0)
 * @param duration_ms Durée totale en ms
 */
void LED_BUILTIN_BLINK_FREQ(float freq_hz, float duty_cycle, uint16_t duration_ms) {
  if(freq_hz <= 0.0f) return;
  if(duty_cycle < 0.0f) duty_cycle = 0.0f;
  if(duty_cycle > 1.0f) duty_cycle = 1.0f;
  
  uint16_t period_ms = (uint16_t)(1000.0f / freq_hz);
  uint16_t on_time = (uint16_t)(period_ms * duty_cycle);
  uint16_t off_time = period_ms - on_time;
  
  unsigned long start_time = millis();
  
  while(millis() - start_time < duration_ms) {
    LED_BUILTIN_ON();
    if(on_time > 0) delay(on_time);
    
    LED_BUILTIN_OFF();
    unsigned long elapsed = millis() - start_time;
    if(elapsed < duration_ms && off_time > 0) {
      delay(off_time);
    }
  }
}

/**
 * @brief Clignotement avec motif personnalisé
 * @param pattern Tableau d'états (1=ON, 0=OFF)
 * @param times Tableau de durées en ms
 * @param length Longueur des tableaux
 * @param repeat Nombre de répétitions (défaut: 1)
 */
void LED_BUILTIN_BLINK_PATTERN(const uint8_t* pattern, const uint16_t* times, uint8_t length, uint8_t repeat = 1) {
  for(uint8_t r = 0; r < repeat; r++) {
    for(uint8_t i = 0; i < length; i++) {
      if(pattern[i] == 1) {
        LED_BUILTIN_ON();
      } else {
        LED_BUILTIN_OFF();
      }
      delay(times[i]);
    }
  }
  LED_BUILTIN_OFF();
}

/**
 * @brief Clignotement SOS (signal de détresse)
 */
void LED_BUILTIN_SOS(void) {
  // S = 3 courts
  LED_BUILTIN_BLINK(200, 3);
  delay(300);
  
  // O = 3 longs
  LED_BUILTIN_BLINK(600, 3);
  delay(300);
  
  // S = 3 courts
  LED_BUILTIN_BLINK(200, 3);
  delay(1000);
}

/**
 * @brief Fonction pour forcer une valeur spécifique (override)
 * @param pin Numéro de GPIO à utiliser
 */
void SET_LED_BUILTIN_PIN(uint8_t pin) {
  #undef LED_BUILTIN
  #define LED_BUILTIN pin
  ENABLE_LED_BUILTIN();
}
