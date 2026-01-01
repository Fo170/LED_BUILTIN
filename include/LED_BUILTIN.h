//  --------------------------------------------------------------------------
//  LED_BUILTIN.h  –  Gestion non-bloquante des LED intégrées ESP8266 / ESP32
//  Version 2.2.0
//  --------------------------------------------------------------------------
//  ☞  APPELER  LED_BUILTIN_UPDATE()  DANS  loop()  !
//  --------------------------------------------------------------------------
//  Broches & remarques rapides (voir détails plus bas) :
//  –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
//  ESP8266
//  • NodeMCU/Wemos D1 mini  →  GPIO 2  (D4)  LED bleue  –  LOGIQUE INVERSÉE
//  • Adafruit Feather       →  GPIO 0  (D3)  LED rouge  –  INVERSÉE
//  • SparkFun Thing         →  GPIO 5  (D1)  LED bleue  –  INVERSÉE
//  • Heltec WiFi Kit 8      →  GPIO 2  (D4)  LED bleue  –  INVERSÉE
//  • ESP-01                 →  GPIO 2       LED bleue  –  INVERSÉE
//  –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
//  ESP32
//  • DevKit/WROOM/WROVER    →  GPIO 2  (D2)  LED bleue  –  NON INVERSÉE
//  • Heltec WiFi Kit 32 V1  →  GPIO 25       LED blanche –  NON INVERSÉE
//  • Heltec WiFi Kit 32 V3  →  GPIO 35       LED blanche –  NON INVERSÉE
//  • TTGO T-Display         →  GPIO 4  (D4)  LED verte  –  NON INVERSÉE
//  • TTGO T-Display-S3      →  GPIO 38       LED RGB   –  NON INVERSÉE
//  • Adafruit Feather       →  GPIO 13 (D13) LED rouge  –  NON INVERSÉE
//  • M5Stack Core           →  GPIO 2  (D2)  LED rouge  –  NON INVERSÉE
//  • M5Stack ATOM           →  GPIO 27       LED RGB WS2812
//  • ESP32-CAM              →  GPIO 4        LED flash  –  NON INVERSÉE
//  • ESP32-S2               →  GPIO 18       LED bleue  –  NON INVERSÉE
//  • ESP32-S3 DevKit        →  GPIO 48       LED RGB   –  NON INVERSÉE
//  • ESP32-C3               →  GPIO 8        LED RGB   –  NON INVERSÉE
//  --------------------------------------------------------------------------

#ifndef LED_BUILTIN_H
#define LED_BUILTIN_H
#include <Arduino.h>

// ----------------------------------------------------------
// Détection de la plate-forme
// ----------------------------------------------------------
#if defined(ESP8266)
  #define PLATFORM_ESP8266
#elif defined(ESP32)
  #define PLATFORM_ESP32
#endif

// ----------------------------------------------------------
// Valeurs par défaut (au cas où aucune carte n’est reconnue)
// ----------------------------------------------------------
#if defined(PLATFORM_ESP8266) && !defined(LED_BUILTIN)
  #define LED_BUILTIN 2          // GPIO 2 (D4) – logique inversée
#elif defined(PLATFORM_ESP32) && !defined(LED_BUILTIN)
  #define LED_BUILTIN 2          // GPIO 2 (D2) – logique normale
#endif

// ==========================================================
//  ESP 8266
// ==========================================================
#if defined(PLATFORM_ESP8266)

  // ---------- NodeMCU 1.0 (ESP-12E) ----------------------
  #if defined(ARDUINO_ESP8266_NODEMCU_ESP12E) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 2        // D4 – LED bleue – INVERSÉE
  #endif

  // ---------- NodeMCU 0.9 (ESP-12) -----------------------
  #if defined(ARDUINO_ESP8266_NODEMCU_ESP12) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 16       // D0 – LED bleue – INVERSÉE
  #endif

  // ---------- WeMos / LOLIN --------------------------------
  #if (defined(ARDUINO_ESP8266_WEMOS_D1MINI)       || \
       defined(ARDUINO_ESP8266_WEMOS_D1MINIPRO)    || \
       defined(ARDUINO_ESP8266_WEMOS_D1MINILITE)   || \
       defined(ARDUINO_LOLIN_D1MINI)                || \
       defined(ARDUINO_LOLIN_D1MINIPRO)             || \
       defined(ARDUINO_LOLIN_D1MINILITE))           && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 2        // D4 – LED bleue – INVERSÉE
  #endif
  #if (defined(ARDUINO_ESP8266_WEMOS_D1R1) || defined(ARDUINO_LOLIN_D1R1)) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 5        // D1 – LED bleue – INVERSÉE
  #endif
  #if (defined(ARDUINO_ESP8266_WEMOS_D1R2) || defined(ARDUINO_LOLIN_D1R2)) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 2        // D4 – LED bleue – INVERSÉE
  #endif

  // ---------- Adafruit ------------------------------------
  #if (defined(ARDUINO_ESP8266_ADAFRUIT_HUZZAH) || \
       defined(ARDUINO_ESP8266_ADAFRUIT_FEATHER_HUZZAH)) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 0        // D3 – LED rouge – INVERSÉE
  #endif

  // ---------- SparkFun ------------------------------------
  #if (defined(ARDUINO_ESP8266_SPARKFUN_THING) || \
       defined(ARDUINO_ESP8266_SPARKFUN_THINGDEV)) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 5        // D1 – LED bleue – INVERSÉE
  #endif

  // ---------- LilyGO --------------------------------------
  #if defined(ARDUINO_ESP8266_LILYGO_T_OI) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 2        // D4 – LED bleue – INVERSÉE
  #endif

  // ---------- Heltec --------------------------------------
  #if defined(ARDUINO_ESP8266_HELTEC_WIFI_KIT_8) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 2        // D4 – LED bleue – INVERSÉE
  #endif

  // ---------- DFRobot -------------------------------------
  #if defined(ARDUINO_ESP8266_DFROBOT_FIREBEETLE) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 2        // D4 – LED bleue – INVERSÉE
  #endif

  // ---------- Seeed ---------------------------------------
  #if defined(ARDUINO_ESP8266_SEED_WIO) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 2        // D4 – LED bleue – INVERSÉE
  #endif

  // ---------- Olimex --------------------------------------
  #if defined(ARDUINO_ESP8266_OLIMEX_MOD_WIFI_ESP8266) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 2        // D4 – LED bleue – INVERSÉE
  #endif

  // ---------- ESPino / Phoenix ----------------------------
  #if defined(ARDUINO_ESP8266_ESPINO) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 15       // D8 – LED bleue – INVERSÉE
  #endif
  #if defined(ARDUINO_ESP8266_PHOENIX_1_0) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 2        // D4 – LED bleue – INVERSÉE
  #endif

  // ---------- ESP-01 (aucune LED de board) ---------------
  #if defined(ARDUINO_ESP8266_ESP01) && !defined(LED_BUILTIN)
    // laissé volontairement vide – pas de LED sur la board
	// Pas de LED visible sur le module ESP-01 ; l’utilisateur
    // peut connecter une LED externe sur GPIO 2 si désiré.
  #endif
#endif // PLATFORM_ESP8266

// ==========================================================
//  ESP 32
// ==========================================================
#if defined(PLATFORM_ESP32)

  // ---------- DevKit / WROVER / WROOM ---------------------
  #if (defined(ARDUINO_ESP32_DEV)     || \
       defined(ARDUINO_ESP32_DEVKIT)  || \
       defined(ARDUINO_ESP32_WROVER)  || \
       defined(ARDUINO_ESP32_WROOM))  && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 2        // D2 – LED bleue – NON INVERSÉE
  #endif

  // ---------- Node32s -------------------------------------
  #if defined(ARDUINO_ESP32_NODE32S) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 2        // D2 – LED bleue – NON INVERSÉE
  #endif

  // ---------- TTGO / LilyGO -------------------------------
  #if (defined(ARDUINO_TTGO_T_DISPLAY) || defined(ARDUINO_LILYGO_T_DISPLAY)) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 4        // D4 – LED verte – NON INVERSÉE
  #endif
  #if (defined(ARDUINO_TTGO_T_DISPLAY_S3) || defined(ARDUINO_LILYGO_T_DISPLAY_S3)) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 38       // GPIO 38 – LED RGB – NON INVERSÉE
  #endif
  #if (defined(ARDUINO_TTGO_T_QT) || defined(ARDUINO_LILYGO_T_QT)) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 4        // D4 – LED verte – NON INVERSÉE
  #endif
  #if (defined(ARDUINO_TTGO_T_BEAM) || defined(ARDUINO_LILYGO_T_BEAM)) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 2        // D2 – LED bleue – NON INVERSÉE
  #endif
  #if (defined(ARDUINO_TTGO_T_CAMERA) || defined(ARDUINO_LILYGO_T_CAMERA)) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 4        // GPIO 4 – LED flash – NON INVERSÉE
  #endif
  #if (defined(ARDUINO_TTGO_T_WATCH) || defined(ARDUINO_LILYGO_T_WATCH)) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 2        // D2 – LED bleue – NON INVERSÉE
  #endif
  #if (defined(ARDUINO_TTGO_LORA32_V1) || defined(ARDUINO_TTGO_LORA32_V2)) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 2        // D2 – LED bleue – NON INVERSÉE
  #endif
  #if defined(TTGO_T7_V14) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 22       // GPIO 22 – LED bleue – NON INVERSÉE
  #endif
  #if defined(TTGO_T7_MINI32) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 22       // GPIO 22 – LED bleue – NON INVERSÉE
  #endif

  // ---------- Heltec --------------------------------------
  #if (defined(ARDUINO_HELTEC_WIFI_KIT_32)        || \
       defined(ARDUINO_HELTEC_WIFI_KIT_32_V2)     || \
       defined(ARDUINO_HELTEC_WIFI_LORA_32)       || \
       defined(ARDUINO_HELTEC_WIFI_LORA_32_V2)    || \
       defined(HELTEC_WIFI_LORA_32)              || \
       defined(HELTEC_WIFI_LORA_32_V2)           || \
       defined(ARDUINO_HELTEC_WIRELESS_STICK)     || \
       defined(ARDUINO_HELTEC_WIRELESS_STICK_LITE)) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 25       // GPIO 25 – LED blanche – NON INVERSÉE
  #endif
// ----------------------------------------------------------
//  Heltec WiFi Kit 32 V3  ––  choix obligatoire - LED blanche – NON INVERSÉE
// ----------------------------------------------------------
#if defined(ARDUINO_HELTEC_WIFI_KIT_32_V3) || defined(ARDUINO_HELTEC_WIFI_LORA_32_V3)
  #if !defined(HELTEC_V3_LED_GPIO35) && !defined(HELTEC_V3_LED_GPIO38)
    #error "Heltec V3 board detected : please define either HELTEC_V3_LED_GPIO35 or HELTEC_V3_LED_GPIO38 before including LED_BUILTIN.h"
  #endif
  #if defined(HELTEC_V3_LED_GPIO35) && defined(HELTEC_V3_LED_GPIO38)
    #error "Both HELTEC_V3_LED_GPIO35 and HELTEC_V3_LED_GPIO38 are defined : choose only one"
  #endif
  #if !defined(LED_BUILTIN)
    #ifdef HELTEC_V3_LED_GPIO35
      #define LED_BUILTIN 35
    #elif defined(HELTEC_V3_LED_GPIO38)
      #define LED_BUILTIN 38
    #endif
  #endif
#endif
  // ---------- Adafruit ------------------------------------
  #if (defined(ARDUINO_FEATHER_ESP32)       || \
       defined(ARDUINO_FEATHER_ESP32_V2)    || \
       defined(ADAFRUIT_FEATHER_ESP32)      || \
       defined(ADAFRUIT_HUZZAH32)            || \
       defined(ARDUINO_METRO_ESP32)         || \
       defined(ARDUINO_ESP32_SAOLA_S2))     && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 13       // D13 – LED rouge – NON INVERSÉE
  #endif
  #if defined(ARDUINO_FEATHER_ESP32_S2_TFT) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 42       // GPIO 42 – LED RGB – NON INVERSÉE
  #endif
  #if (defined(ARDUINO_FEATHER_ESP32_S3) || defined(ARDUINO_ESP32_SAOLA_S3)) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 2        // D2 – LED RGB – NON INVERSÉE
  #endif
  #if defined(ARDUINO_FEATHER_ESP32_C3) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 8        // GPIO 8 – LED RGB – NON INVERSÉE
  #endif
  #if defined(ARDUINO_FEATHER_ESP32_C6) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 15       // GPIO 15 – LED RGB – NON INVERSÉE
  #endif

  // ---------- SparkFun ------------------------------------
  #if defined(ARDUINO_SPARKFUN_ESP32_THING) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 5        // GPIO 5 – LED bleue – NON INVERSÉE
  #endif
  #if (defined(ARDUINO_SPARKFUN_ESP32_THING_PLUS)       || \
       defined(ARDUINO_SPARKFUN_THING_PLUS)             || \
       defined(ARDUINO_SPARKFUN_ESP32_S3_THING_PLUS)    || \
       defined(ARDUINO_SPARKFUN_REDBOARD_ESP32))        && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 13       // D13 – LED bleue – NON INVERSÉE
  #endif
  #if defined(ARDUINO_SPARKFUN_ESP32_C3_THING_PLUS) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 8        // GPIO 8 – LED RGB – NON INVERSÉE
  #endif

  // ---------- M5Stack -------------------------------------
  #if (defined(ARDUINO_M5STACK_CORE) || \
       defined(ARDUINO_M5STACK_FIRE) || \
       defined(ARDUINO_M5STACK_BASIC)) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 2        // D2 – LED rouge – NON INVERSÉE
  #endif
  #if defined(ARDUINO_M5STACK_CORE2) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 25       // GPIO 25 – LED rouge – NON INVERSÉE
  #endif
  #if defined(ARDUINO_M5STACK_ATOM) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 27       // GPIO 27 – LED RGB WS2812
    #define LED_BUILTIN_IS_RGB   1
  #endif
  #if (defined(ARDUINO_M5STICKC) || defined(ARDUINO_M5STICK_C) || defined(ARDUINO_M5STICKC_PLUS)) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 10       // GPIO 10 – LED orange – NON INVERSÉE
  #endif

  // ---------- DFRobot -------------------------------------
  #if (defined(ARDUINO_DFROBOT_FIREBEETLE_ESP32)      || \
       defined(ARDUINO_DFROBOT_FIREBEETLE_ESP32_E)   || \
       defined(ARDUINO_DFROBOT_FIREBEETLE_ESP32_S3)) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 2        // D2 – LED bleue – NON INVERSÉE
  #endif
  #if defined(ARDUINO_DFROBOT_FIREBEETLE_ESP32_C3) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 8        // GPIO 8 – LED RGB – NON INVERSÉE
  #endif
  #if defined(ARDUINO_DFROBOT_FIREBEETLE_ESP32_C6) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 8        // GPIO 8 – LED RGB – NON INVERSÉE
  #endif
  #if defined(ARDUINO_DFROBOT_FIREBEETLE_ESP32_C6_N16) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 18       // GPIO 18 – LED RGB – NON INVERSÉE
  #endif

  // ---------- Seeed ---------------------------------------
  #if (defined(ARDUINO_SEEED_WIO_ESP32)      || \
       defined(ARDUINO_SEEED_WIO_ESP32_S3)   || \
       defined(ARDUINO_SEEED_XIAO_ESP32_S3)) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 2        // D2 – LED bleue – NON INVERSÉE
  #endif
  #if (defined(ARDUINO_SEEED_WIO_ESP32_C3) || \
       defined(ARDUINO_SEEED_XIAO_ESP32_C3) || \
       defined(ARDUINO_SEEED_WIO_ESP32_C6) || \
       defined(ARDUINO_SEEED_XIAO_ESP32_C6)) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 8        // GPIO 8 – LED RGB – NON INVERSÉE
  #endif

  // ---------- Olimex --------------------------------------
  #if (defined(ARDUINO_OLIMEX_ESP32_EVB)         || \
       defined(ARDUINO_OLIMEX_ESP32_GATEWAY)     || \
       defined(ARDUINO_OLIMEX_ESP32_POE)         || \
       defined(ARDUINO_OLIMEX_ESP32_POE_ISO)     || \
       defined(ARDUINO_OLIMEX_ESP32_S3_DEVKIT_LIPO)) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 2        // D2 – LED verte – NON INVERSÉE
  #endif
  #if defined(ARDUINO_OLIMEX_ESP32_C3_DEVKIT_LIPO) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 8        // GPIO 8 – LED RGB – NON INVERSÉE
  #endif

  // ---------- LOLIN / Wemos ESP32 -------------------------
  #if (defined(ARDUINO_LOLIN_D32)     || \
       defined(ARDUINO_LOLIN_D32_PRO) || \
       defined(ARDUINO_LOLIN32)       || \
       defined(ARDUINO_LOLIN32_LITE) || \
       defined(WEMOS_LOLIN32)        || \
       defined(LOLIN_D32))           && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 5        // GPIO 5 – LED bleue – NON INVERSÉE
  #endif
  #if defined(WEMOS_D1_R32) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 2        // D2 – LED bleue – NON INVERSÉE
  #endif

  // ---------- ESP32-CAM & dérivés -------------------------
  #if (defined(ARDUINO_ESP32_CAM) || defined(CAMERA_MODEL_AI_THINKER)) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 4        // GPIO 4 – LED flash blanche – NON INVERSÉE
  #endif
  #if defined(ARDUINO_ESP32_EYE) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 2        // D2 – LED bleue – NON INVERSÉE
  #endif

  // ---------- ESP32-Sx bare-chips -------------------------
  #if (defined(ARDUINO_ESP32_S2_DEV) || defined(CONFIG_IDF_TARGET_ESP32S2) || defined(ESP32S2)) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 18       // GPIO 18 – LED bleue – NON INVERSÉE
  #endif
  #if (defined(ARDUINO_ESP32_S3_DEV) || defined(CONFIG_IDF_TARGET_ESP32S3) || defined(ESP32S3)) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 48       // GPIO 48 – LED RGB – NON INVERSÉE
  #endif
  #if (defined(ARDUINO_ESP32_C3_DEV) || defined(CONFIG_IDF_TARGET_ESP32C3) || defined(ESP32C3)) && !defined(LED_BUILTIN)
    #undef LED_BUILTIN
    #define LED_BUILTIN 8        // GPIO 8 – LED RGB – NON INVERSÉE
  #endif
  // ----------------------------------------------------------
//  ESP32-C6  ––  choix obligatoire - LED RGB – NON INVERSÉE
// ----------------------------------------------------------
#if defined(ARDUINO_ESP32_C6_DEV)
  #if !defined(ESP32_C6_LED_GPIO8) && !defined(ESP32_C6_LED_GPIO18)
    #error "ESP32-C6 board detected : please define either ESP32_C6_LED_GPIO8 or ESP32_C6_LED_GPIO18 before including LED_BUILTIN.h"
  #endif
  #if defined(ESP32_C6_LED_GPIO8) && defined(ESP32_C6_LED_GPIO18)
    #error "Both ESP32_C6_LED_GPIO8 and ESP32_C6_LED_GPIO18 are defined : choose only one"
  #endif
  #if !defined(LED_BUILTIN)
    #ifdef ESP32_C6_LED_GPIO8
      #define LED_BUILTIN 8
    #elif defined(ESP32_C6_LED_GPIO18)
      #define LED_BUILTIN 18
    #endif
  #endif
#endif

  // ---------- Generic (aucune LED) ------------------------
  #if defined(ARDUINO_ESP32_GENERIC) && !defined(LED_BUILTIN)
    // laissé volontairement vide – pas de LED sur le module nu
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
// n’oublie pas que l’adresse du pixel est 0 (pas 1) 
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
