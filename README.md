# LED_BUILTIN Library

Une bibliothèque Arduino complète pour gérer les LED intégrées (LED_BUILTIN) sur les cartes ESP8266 et ESP32 avec support étendu des GPIO et fonctions de clignotement avancées.

## Fonctionnalités

- **Détection automatique** des cartes ESP8266 et ESP32
- **Support complet** des GPIO pour différentes cartes (Heltec, TTGO, Adafruit, SparkFun, etc.)
- **Gestion automatique de la polarité** (LOW/HIGH active)
- **Fonctions de clignotement avancées** avec rapport cyclique personnalisable
- **Compatibilité ascendante** avec les fonctions standard
- **Fonctions utilitaires** (toggle, blink, SOS, motifs personnalisés)

## Cartes supportées

### ESP8266
- NodeMCU (GPIO2/D4)
- Wemos D1 mini (GPIO2)
- ESP-01 (GPIO2)
- Et autres variantes

### ESP32
- Heltec WiFi LoRa 32 (V1/V2) - GPIO25
- TTGO T-Display - GPIO4
- TTGO T7 Mini32 - GPIO22
- Adafruit HUZZAH32 - GPIO13
- SparkFun ESP32 Thing - GPIO5
- Wemos LOLIN32 - GPIO5
- M5Stack Basic - GPIO2
- ESP32-C3 DevKit - GPIO8
- ESP32-S2 DevKit - GPIO18
- ESP32-S3 DevKit - GPIO48
- Et bien d'autres...

## Installation

### Via Arduino IDE :
1. Téléchargez cette librairie en format ZIP
2. Dans Arduino IDE : Croquis → Inclure une bibliothèque → Ajouter la bibliothèque .ZIP
3. Sélectionnez le fichier ZIP téléchargé

### Via Platformio :
dans le fichier platformio.ini

; PlatformIO Project Configuration File
;
;   Build options: build flags, source filter
;   Upload options: custom upload port, speed and extra flags
;   Library options: dependencies, extra library storages
;   Advanced options: extra scripting
;
; Please visit documentation for the other options and examples
; https://docs.platformio.org/page/projectconf.html

[env:esp12e]
platform = espressif8266
board = esp12e
framework = arduino
monitor_speed = 115200
lib_deps = https://github.com/Fo170/LED_BUILTIN.git

[env:az-delivery-devkit-v4]
platform = espressif32
board = az-delivery-devkit-v4
framework = arduino
monitor_speed = 115200
lib_deps = https://github.com/Fo170/LED_BUILTIN.git

