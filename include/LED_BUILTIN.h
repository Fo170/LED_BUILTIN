/*
  LED_BUILTIN.h - Gestion non-bloquante des LED intégrées pour ESP8266/ESP32
  Version 2.0 - Sans delay(), utilise millis()
  
  Choisissez la fonction qui correspond le mieux à votre besoin :
  
  Pour un simple clignotement 50% : LED_BUILTIN_BLINK_START()
  Pour un rapport cyclique spécifique : LED_BUILTIN_BLINK_DUTY_START()
  Pour un contrôle précis des temps ON/OFF : LED_BUILTIN_BLINK_TIMING_START()
  Pour un contrôle par fréquence : LED_BUILTIN_BLINK_FREQ_START()
  Pour des motifs complexes : LED_BUILTIN_BLINK_PATTERN_START()
  Pour un signal SOS : LED_BUILTIN_SOS_START()
  
  IMPORTANT : Appelez LED_BUILTIN_UPDATE() dans votre loop() !
  
  Exemples :
  void setup() {
    ENABLE_LED_BUILTIN();
    LED_BUILTIN_BLINK_START(500, 5); // 5 clignotements de 500ms
  }
  
  void loop() {
    LED_BUILTIN_UPDATE(); // À appeler à chaque itération
    // Votre code ici...
  }
*/

// ============================================
// DÉTECTION DE LA PLATEFORME
// ============================================
#if defined(ESP8266)
  #define PLATFORM_ESP8266
#elif defined(ESP32)
  #define PLATFORM_ESP32
#endif

// ============================================
// DÉFINITIONS PAR DÉFAUT
// ============================================
#if defined(PLATFORM_ESP8266)
  #ifndef LED_BUILTIN
    #define LED_BUILTIN 2  // GPIO2 (D4) - NodeMCU, Wemos D1 mini, ESP-12
  #endif
  
#elif defined(PLATFORM_ESP32)
  #ifndef LED_BUILTIN
    #define LED_BUILTIN 2  // GPIO2 - ESP32 DevKit, DOIT ESP32
  #endif
#endif

// ============================================
// DÉTECTION SPÉCIFIQUE DES CARTES ESP32
// ============================================
#if defined(PLATFORM_ESP32)
  
  // Heltec WiFi LoRa 32 - LED blanche sur GPIO25
  #if defined(HELTEC_WIFI_LORA_32) || defined(HELTEC_WIFI_LORA_32_V2)
    #undef LED_BUILTIN
    #define LED_BUILTIN 25
  
  // TTGO T7 - LED sur GPIO22
  #elif defined(TTGO_T7_V14) || defined(TTGO_T7_MINI32)
    #undef LED_BUILTIN
    #define LED_BUILTIN 22
  
  // TTGO T-Display - LED sur GPIO4
  #elif defined(TTGO_T_DISPLAY)
    #undef LED_BUILTIN
    #define LED_BUILTIN 4
  
  // Adafruit Feather ESP32 / HUZZAH32 - LED rouge sur GPIO13
  #elif defined(ADAFRUIT_FEATHER_ESP32) || defined(ADAFRUIT_HUZZAH32)
    #undef LED_BUILTIN
    #define LED_BUILTIN 13
  
  // SparkFun ESP32 Thing - LED bleue sur GPIO5
  #elif defined(ESP32_THING)
    #undef LED_BUILTIN
    #define LED_BUILTIN 5
  
  // SparkFun Thing Plus - LED bleue sur GPIO13
  #elif defined(ARDUINO_SPARKFUN_THING_PLUS)
    #undef LED_BUILTIN
    #define LED_BUILTIN 13
  
  // Wemos/Lolin32 - LED bleue sur GPIO5
  #elif defined(WEMOS_LOLIN32) || defined(LOLIN_D32)
    #undef LED_BUILTIN
    #define LED_BUILTIN 5
  
  // Wemos D1 R32 - LED sur GPIO2
  #elif defined(WEMOS_D1_R32)
    #undef LED_BUILTIN
    #define LED_BUILTIN 2
  
  // M5Stack Core2/Fire/Basic - LED rouge sur GPIO2
  #elif defined(ARDUINO_M5STACK_CORE2) || defined(ARDUINO_M5STACK_FIRE) || defined(ARDUINO_M5STACK_BASIC)
    #undef LED_BUILTIN
    #define LED_BUILTIN 2
  
  // M5Stick-C - LED orange sur GPIO10
  #elif defined(ARDUINO_M5STICK_C)
    #undef LED_BUILTIN
    #define LED_BUILTIN 10
  
  // M5Stack ATOM - LED RGB WS2812 sur GPIO27
  #elif defined(ARDUINO_M5STACK_ATOM)
    #undef LED_BUILTIN
    #define LED_BUILTIN 27
    #define LED_BUILTIN_IS_RGB 1  // LED RGB WS2812
  
  // ESP32-C3 - LED RGB sur GPIO8 (certains modèles)
  #elif defined(CONFIG_IDF_TARGET_ESP32C3) || defined(ESP32C3)
    #undef LED_BUILTIN
    #define LED_BUILTIN 8
  
  // ESP32-S2 - LED sur GPIO18
  #elif defined(CONFIG_IDF_TARGET_ESP32S2) || defined(ESP32S2)
    #undef LED_BUILTIN
    #define LED_BUILTIN 18
  
  // ESP32-S3 - LED RGB sur GPIO48 (ESP32-S3-DevKitC)
  #elif defined(CONFIG_IDF_TARGET_ESP32S3) || defined(ESP32S3)
    #undef LED_BUILTIN
    #define LED_BUILTIN 48
  
  // LILYGO T-Display-S3 - LED sur GPIO38
  #elif defined(ARDUINO_LILYGO_T_DISPLAY_S3)
    #undef LED_BUILTIN
    #define LED_BUILTIN 38
  
  // ESP32-CAM (AI-Thinker) - LED flash sur GPIO4
  #elif defined(CAMERA_MODEL_AI_THINKER)
    #undef LED_BUILTIN
    #define LED_BUILTIN 4  // LED flash blanche
  
  #endif
  
#endif // PLATFORM_ESP32

// ============================================
// DÉTECTION SPÉCIFIQUE DES CARTES ESP8266
// ============================================
#if defined(PLATFORM_ESP8266)
  
  // NodeMCU v1.0 - LED bleue sur GPIO2 (inversée)
  #if defined(ARDUINO_ESP8266_NODEMCU)
    #undef LED_BUILTIN
    #define LED_BUILTIN 2
  
  // Wemos D1 mini - LED bleue sur GPIO2 (inversée)
  #elif defined(ARDUINO_ESP8266_WEMOS_D1MINI)
    #undef LED_BUILTIN
    #define LED_BUILTIN 2
  
  // ESP-01 - LED bleue sur GPIO2
  #elif defined(ARDUINO_ESP8266_ESP01)
    #undef LED_BUILTIN
    #define LED_BUILTIN 2
  
  #endif
  
#endif

// ============================================
// DÉFINITION DE LA POLARITÉ
// ============================================
#ifndef LED_BUILTIN_POLARITY
  #if defined(PLATFORM_ESP8266)
    // La plupart des ESP8266 ont des LED inversées (LOW = ON)
    #define LED_BUILTIN_POLARITY 0
  #elif defined(PLATFORM_ESP32)
    // Cartes avec LED inversée (LOW active)
    #if defined(ARDUINO_M5STACK_CORE2) || defined(ARDUINO_M5STACK_FIRE) || \
        defined(ARDUINO_M5STACK_BASIC) || defined(WEMOS_D1_R32)
      #define LED_BUILTIN_POLARITY 0
    #else
      // Par défaut HIGH active pour ESP32
      #define LED_BUILTIN_POLARITY 1
    #endif
  #endif
#endif

// ============================================
// MACROS UTILITAIRES
// ============================================
#if LED_BUILTIN_POLARITY == 0
  #define LED_ON_STATE   LOW
  #define LED_OFF_STATE  HIGH
#else
  #define LED_ON_STATE   HIGH
  #define LED_OFF_STATE  LOW
#endif

// ============================================
// GESTION LED RGB (M5Stack ATOM, etc.)
// ============================================
#ifdef LED_BUILTIN_IS_RGB
  // Vérifier si Adafruit_NeoPixel est disponible
  #if __has_include(<Adafruit_NeoPixel.h>)
    #include <Adafruit_NeoPixel.h>
    #define LED_RGB_AVAILABLE
  #else
    #warning "LED RGB détectée mais Adafruit_NeoPixel n'est pas installé. Installez la bibliothèque Adafruit NeoPixel pour utiliser les fonctions RGB."
    #undef LED_BUILTIN_IS_RGB
  #endif
#endif

#ifdef LED_RGB_AVAILABLE
  
  static Adafruit_NeoPixel* led_rgb_strip = nullptr;
  static uint8_t led_rgb_r = 255, led_rgb_g = 255, led_rgb_b = 255;
  static uint8_t led_rgb_brightness = 50; // 0-255
  
  /**
   * @brief Initialise la LED RGB
   */
  void LED_RGB_INIT() {
    if(led_rgb_strip == nullptr) {
      led_rgb_strip = new Adafruit_NeoPixel(1, LED_BUILTIN, NEO_GRB + NEO_KHZ800);
      led_rgb_strip->begin();
      led_rgb_strip->setBrightness(led_rgb_brightness);
      led_rgb_strip->show();
    }
  }
  
  /**
   * @brief Définit la couleur de la LED RGB
   * @param r Rouge (0-255)
   * @param g Vert (0-255)
   * @param b Bleu (0-255)
   * @param brightness Luminosité (0-255, optionnel)
   */
  void LED_RGB_SET_COLOR(uint8_t r, uint8_t g, uint8_t b, uint8_t brightness = 255) {
    LED_RGB_INIT();
    led_rgb_r = r;
    led_rgb_g = g;
    led_rgb_b = b;
    if(brightness < 255) {
      led_rgb_brightness = brightness;
      led_rgb_strip->setBrightness(brightness);
    }
  }
  
  /**
   * @brief Allume la LED RGB avec la couleur définie
   */
  void LED_RGB_ON() {
    LED_RGB_INIT();
    led_rgb_strip->setPixelColor(0, led_rgb_strip->Color(led_rgb_r, led_rgb_g, led_rgb_b));
    led_rgb_strip->show();
  }
  
  /**
   * @brief Éteint la LED RGB
   */
  void LED_RGB_OFF() {
    LED_RGB_INIT();
    led_rgb_strip->setPixelColor(0, 0);
    led_rgb_strip->show();
  }
  
  // Couleurs prédéfinies
  #define LED_RGB_RED()     LED_RGB_SET_COLOR(255, 0, 0)
  #define LED_RGB_GREEN()   LED_RGB_SET_COLOR(0, 255, 0)
  #define LED_RGB_BLUE()    LED_RGB_SET_COLOR(0, 0, 255)
  #define LED_RGB_YELLOW()  LED_RGB_SET_COLOR(255, 255, 0)
  #define LED_RGB_CYAN()    LED_RGB_SET_COLOR(0, 255, 255)
  #define LED_RGB_MAGENTA() LED_RGB_SET_COLOR(255, 0, 255)
  #define LED_RGB_WHITE()   LED_RGB_SET_COLOR(255, 255, 255)
  #define LED_RGB_ORANGE()  LED_RGB_SET_COLOR(255, 165, 0)
  #define LED_RGB_PURPLE()  LED_RGB_SET_COLOR(128, 0, 128)
#endif

// ============================================
// STRUCTURE DE GESTION D'ÉTAT
// ============================================
typedef enum {
  LED_STATE_IDLE,
  LED_STATE_BLINK,
  LED_STATE_PATTERN
} LED_State_t;

typedef struct {
  LED_State_t state;
  unsigned long last_time;
  unsigned long next_time;
  uint16_t on_time;
  uint16_t off_time;
  uint8_t count;
  uint8_t current_count;
  bool led_is_on;
  
  // Pour les patterns
  const uint8_t* pattern;
  const uint16_t* times;
  uint8_t pattern_length;
  uint8_t pattern_index;
  uint8_t pattern_repeat;
  uint8_t pattern_current_repeat;
} LED_Control_t;

static LED_Control_t led_ctrl = {LED_STATE_IDLE, 0, 0, 0, 0, 0, 0, false, nullptr, nullptr, 0, 0, 0, 0};

// ============================================
// FONCTIONS DE BASE
// ============================================
void ENABLE_LED_BUILTIN(void) {
  #ifdef LED_BUILTIN_IS_RGB
    LED_RGB_INIT();
    LED_RGB_OFF();
  #else
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LED_OFF_STATE);
  #endif
}

void LED_BUILTIN_ON(void) {
  #ifdef LED_BUILTIN_IS_RGB
    LED_RGB_ON();
  #else
    digitalWrite(LED_BUILTIN, LED_ON_STATE);
  #endif
}

void LED_BUILTIN_OFF(void) {
  #ifdef LED_BUILTIN_IS_RGB
    LED_RGB_OFF();
  #else
    digitalWrite(LED_BUILTIN, LED_OFF_STATE);
  #endif
}

void LED_BUILTIN_TOGGLE(void) {
  #ifdef LED_BUILTIN_IS_RGB
    // Pour RGB, on alterne entre ON et OFF
    static bool rgb_state = false;
    rgb_state = !rgb_state;
    if(rgb_state) LED_RGB_ON();
    else LED_RGB_OFF();
  #else
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  #endif
}

/**
 * @brief Arrête toute séquence de clignotement en cours
 */
void LED_BUILTIN_STOP(void) {
  led_ctrl.state = LED_STATE_IDLE;
  LED_BUILTIN_OFF();
}

// ============================================
// FONCTION UPDATE - À APPELER DANS loop()
// ============================================
/**
 * @brief Met à jour l'état de la LED (à appeler dans loop())
 * @return true si une animation est en cours, false sinon
 */
bool LED_BUILTIN_UPDATE(void) {
  unsigned long current_time = millis();
  
  switch(led_ctrl.state) {
    case LED_STATE_IDLE:
      return false;
      
    case LED_STATE_BLINK:
      if(current_time >= led_ctrl.next_time) {
        if(led_ctrl.led_is_on) {
          // Passer de ON à OFF
          LED_BUILTIN_OFF();
          led_ctrl.led_is_on = false;
          led_ctrl.current_count++;
          
          // Vérifier si on a terminé
          if(led_ctrl.current_count >= led_ctrl.count) {
            led_ctrl.state = LED_STATE_IDLE;
            return false;
          }
          
          led_ctrl.next_time = current_time + led_ctrl.off_time;
        } else {
          // Passer de OFF à ON
          LED_BUILTIN_ON();
          led_ctrl.led_is_on = true;
          led_ctrl.next_time = current_time + led_ctrl.on_time;
        }
      }
      return true;
      
    case LED_STATE_PATTERN:
      if(current_time >= led_ctrl.next_time) {
        // État suivant du pattern
        if(led_ctrl.pattern[led_ctrl.pattern_index] == 1) {
          LED_BUILTIN_ON();
        } else {
          LED_BUILTIN_OFF();
        }
        
        led_ctrl.next_time = current_time + led_ctrl.times[led_ctrl.pattern_index];
        led_ctrl.pattern_index++;
        
        // Fin du pattern ?
        if(led_ctrl.pattern_index >= led_ctrl.pattern_length) {
          led_ctrl.pattern_index = 0;
          led_ctrl.pattern_current_repeat++;
          
          if(led_ctrl.pattern_current_repeat >= led_ctrl.pattern_repeat) {
            LED_BUILTIN_OFF();
            led_ctrl.state = LED_STATE_IDLE;
            return false;
          }
        }
      }
      return true;
  }
  
  return false;
}

// ============================================
// FONCTIONS DE DÉMARRAGE DE SÉQUENCES
// ============================================

/**
 * @brief Démarre un clignotement simple avec rapport cyclique 50%
 * @param delay_ms Durée d'un demi-cycle (ON ou OFF)
 * @param count Nombre de cycles (défaut: 1)
 */
void LED_BUILTIN_BLINK_START(uint16_t delay_ms, uint8_t count = 1) {
  led_ctrl.state = LED_STATE_BLINK;
  led_ctrl.on_time = delay_ms;
  led_ctrl.off_time = delay_ms;
  led_ctrl.count = count;
  led_ctrl.current_count = 0;
  led_ctrl.led_is_on = false;
  led_ctrl.next_time = millis();
}

/**
 * @brief Démarre un clignotement avec période et rapport cyclique personnalisés
 * @param period_ms Période totale en ms
 * @param duty_cycle Rapport cyclique (0.0 à 1.0)
 * @param count Nombre de cycles (défaut: 1)
 */
void LED_BUILTIN_BLINK_DUTY_START(uint16_t period_ms, float duty_cycle, uint8_t count = 1) {
  if(duty_cycle < 0.0f) duty_cycle = 0.0f;
  if(duty_cycle > 1.0f) duty_cycle = 1.0f;
  
  led_ctrl.state = LED_STATE_BLINK;
  led_ctrl.on_time = (uint16_t)(period_ms * duty_cycle);
  led_ctrl.off_time = period_ms - led_ctrl.on_time;
  led_ctrl.count = count;
  led_ctrl.current_count = 0;
  led_ctrl.led_is_on = false;
  led_ctrl.next_time = millis();
}

/**
 * @brief Démarre un clignotement avec temps ON et OFF séparés
 * @param on_time_ms Temps ON en ms
 * @param off_time_ms Temps OFF en ms
 * @param count Nombre de cycles (défaut: 1)
 */
void LED_BUILTIN_BLINK_TIMING_START(uint16_t on_time_ms, uint16_t off_time_ms, uint8_t count = 1) {
  led_ctrl.state = LED_STATE_BLINK;
  led_ctrl.on_time = on_time_ms;
  led_ctrl.off_time = off_time_ms;
  led_ctrl.count = count;
  led_ctrl.current_count = 0;
  led_ctrl.led_is_on = false;
  led_ctrl.next_time = millis();
}

/**
 * @brief Démarre un clignotement avec fréquence et rapport cyclique
 * @param freq_hz Fréquence en Hz
 * @param duty_cycle Rapport cyclique (0.0 à 1.0)
 * @param duration_ms Durée totale en ms
 */
void LED_BUILTIN_BLINK_FREQ_START(float freq_hz, float duty_cycle, uint16_t duration_ms) {
  if(freq_hz <= 0.0f) return;
  if(duty_cycle < 0.0f) duty_cycle = 0.0f;
  if(duty_cycle > 1.0f) duty_cycle = 1.0f;
  
  uint16_t period_ms = (uint16_t)(1000.0f / freq_hz);
  uint8_t count = (uint8_t)(duration_ms / period_ms);
  
  LED_BUILTIN_BLINK_DUTY_START(period_ms, duty_cycle, count);
}

/**
 * @brief Démarre un clignotement avec motif personnalisé
 * @param pattern Tableau d'états (1=ON, 0=OFF)
 * @param times Tableau de durées en ms
 * @param length Longueur des tableaux
 * @param repeat Nombre de répétitions (défaut: 1)
 */
void LED_BUILTIN_BLINK_PATTERN_START(const uint8_t* pattern, const uint16_t* times, uint8_t length, uint8_t repeat = 1) {
  led_ctrl.state = LED_STATE_PATTERN;
  led_ctrl.pattern = pattern;
  led_ctrl.times = times;
  led_ctrl.pattern_length = length;
  led_ctrl.pattern_index = 0;
  led_ctrl.pattern_repeat = repeat;
  led_ctrl.pattern_current_repeat = 0;
  led_ctrl.next_time = millis();
}

/**
 * @brief Démarre un signal SOS (signal de détresse)
 */
void LED_BUILTIN_SOS_START(void) {
  // Pattern SOS : ...---...
  static const uint8_t sos_pattern[] = {
    1,0, 1,0, 1,0,  // S (3 courts)
    0,              // Pause
    1,0, 1,0, 1,0,  // O (3 longs)
    0,              // Pause
    1,0, 1,0, 1,0   // S (3 courts)
  };
  
  static const uint16_t sos_times[] = {
    200,200, 200,200, 200,300,  // S
    300,                        // Pause
    600,200, 600,200, 600,300,  // O
    300,                        // Pause
    200,200, 200,200, 200,1000  // S + pause finale
  };
  
  LED_BUILTIN_BLINK_PATTERN_START(sos_pattern, sos_times, 19, 1);
}

/**
 * @brief Vérifie si une animation est en cours
 * @return true si une animation est active, false sinon
 */
bool LED_BUILTIN_IS_ACTIVE(void) {
  return led_ctrl.state != LED_STATE_IDLE;
}

// ============================================
// COMPATIBILITÉ AVEC L'ANCIENNE VERSION (BLOQUANTE)
// ============================================
#ifdef LED_BUILTIN_COMPATIBILITY_MODE

void LED_BUILTIN_BLINK(uint16_t delay_ms, uint8_t count = 1) {
  LED_BUILTIN_BLINK_START(delay_ms, count);
  while(LED_BUILTIN_UPDATE()) {
    yield(); // Permet au système de traiter d'autres tâches
  }
}

void LED_BUILTIN_BLINK_DUTY(uint16_t period_ms, float duty_cycle, uint8_t count = 1) {
  LED_BUILTIN_BLINK_DUTY_START(period_ms, duty_cycle, count);
  while(LED_BUILTIN_UPDATE()) {
    yield();
  }
}

void LED_BUILTIN_BLINK_TIMING(uint16_t on_time_ms, uint16_t off_time_ms, uint8_t count = 1) {
  LED_BUILTIN_BLINK_TIMING_START(on_time_ms, off_time_ms, count);
  while(LED_BUILTIN_UPDATE()) {
    yield();
  }
}

void LED_BUILTIN_BLINK_FREQ(float freq_hz, float duty_cycle, uint16_t duration_ms) {
  LED_BUILTIN_BLINK_FREQ_START(freq_hz, duty_cycle, duration_ms);
  while(LED_BUILTIN_UPDATE()) {
    yield();
  }
}

void LED_BUILTIN_BLINK_PATTERN(const uint8_t* pattern, const uint16_t* times, uint8_t length, uint8_t repeat = 1) {
  LED_BUILTIN_BLINK_PATTERN_START(pattern, times, length, repeat);
  while(LED_BUILTIN_UPDATE()) {
    yield();
  }
}

void LED_BUILTIN_SOS(void) {
  LED_BUILTIN_SOS_START();
  while(LED_BUILTIN_UPDATE()) {
    yield();
  }
}

#endif // LED_BUILTIN_COMPATIBILITY_MODE
