# LED_BUILTIN Library v2.3.1

Une bibliothèque Arduino **non-bloquante** pour gérer les LED intégrées (LED_BUILTIN) sur les cartes ESP8266 et ESP32 avec support étendu des GPIO, fonctions de clignotement avancées et gestion des LED RGB.
## 📋 Cartes supportées (extrait)

| Carte | GPIO par défaut | Broche Dx | Type / Couleur | Logique | Détection auto |
|-------|-----------------|-----------|----------------|---------|----------------|
| **ESP8266** |
| NodeMCU 1.0 | 2 | D4 | Bleue | Inversée | ✅ |
| Wemos D1 mini | 2 | D4 | Bleue | Inversée | ✅ |
| Adafruit Feather HUZZAH | 0 | D3 | Rouge | Inversée | ✅ |
| SparkFun Thing | 5 | D1 | Bleue | Inversée | ✅ |
| **ESP32** |
| DevKit / WROVER | 2 | D2 | Bleue | Standard | ✅ |
| Heltec WiFi Kit 32 V1/V2 | 25 | — | Blanche | Standard | ✅ |
| Heltec WiFi Kit 32 **V3** | **35 ou 38** | — | Blanche | Standard | **❌ choix obligatoire** |
| TTGO T-Display | 4 | D4 | Verte | Standard | ✅ |
| TTGO T-Display-S3 | 38 | — | RGB | Standard | ✅ |
| Adafruit Feather ESP32-C6 | **8 ou 18** | — | RGB | Standard | **❌ choix obligatoire** |
| M5Stack ATOM | 27 | — | RGB WS2812 | — | ✅ |
| ESP32-CAM | 4 | — | Flash blanche | Standard | ✅ |
| ESP32-S3 DevKit | 48 | — | RGB | Standard | ✅ |
| ESP32-C3 | 8 | — | RGB | Standard | ✅ |

> Pour une liste complète, ouvrez [`LED_BUILTIN.h`](include/LED_BUILTIN.h) – chaque section est commentée (couleur, broche Dx, polarité).

---

## ⚙️ Configuration obligatoire (ESP32-C6 & Heltec V3)

Avant **l’include**, définissez **une seule** des deux macros :

**HELTEC_V3** (certains ont la LED sur GPIO 35, d’autres sur 38) :
```cpp
#define HELTEC_V3_LED_GPIO35 // ou HELTEC_V3_LED_GPIO38
#include "LED_BUILTIN.h"
```

**ESP32-C6** (certains ont la LED sur GPIO 8, d’autres sur 18) :
```cpp
#define ESP32_C6_LED_GPIO8   // ou ESP32_C6_LED_GPIO18
#include "LED_BUILTIN.h"
```

Si aucune macro n’est fournie → erreur de compilation explicite.

## 📦 Installation

### Via Arduino IDE
1. Téléchargez cette bibliothèque en format ZIP
2. Dans Arduino IDE : **Croquis → Inclure une bibliothèque → Ajouter la bibliothèque .ZIP**
3. Sélectionnez le fichier ZIP téléchargé

### Via PlatformIO (recommandé)

Ajoutez la dépendance à votre `platformio.ini` :

```ini
# Pour cartes standard (ESP32, ESP8266, etc.)
lib_deps = 
    https://github.com/Fo170/LED_BUILTIN.git@^2.2.0

# Pour cartes avec LED RGB (M5Stack ATOM)
lib_deps = 
    https://github.com/Fo170/LED_BUILTIN.git@^2.2.0
    adafruit/Adafruit NeoPixel@^1.12.0   ; uniquement si LED RGB utilisée
```

### Dépendances

**Optionnel** - Uniquement pour les cartes avec LED RGB (M5Stack ATOM) :

```ini
lib_deps = 
    adafruit/Adafruit NeoPixel@^1.12.0
```

**Note** : Si vous utilisez une carte avec LED RGB sans installer Adafruit NeoPixel, vous verrez un warning à la compilation mais les fonctions LED standard resteront disponibles.

## 📖 Guide d'utilisation rapide

### Exemple de base (non-bloquant)

```cpp
#include "LED_BUILTIN.h"

void setup() {
  ENABLE_LED_BUILTIN();
  
  // Démarre 10 clignotements de 500ms
  LED_BUILTIN_BLINK_START(500, 10);
}

void loop() {
  // OBLIGATOIRE : met à jour l'état de la LED
  LED_BUILTIN_UPDATE();
  
  // Votre code s'exécute normalement ici
  // pendant que la LED clignote en arrière-plan
}
```

### Fonctions principales

#### Initialisation
```cpp
ENABLE_LED_BUILTIN();        // Initialise la LED (obligatoire)
```

#### Contrôle direct
```cpp
LED_BUILTIN_ON();            // Allume la LED
LED_BUILTIN_OFF();           // Éteint la LED
LED_BUILTIN_TOGGLE();        // Inverse l'état
```

#### Clignotement simple (50% duty cycle)
```cpp
// Clignote pendant 500ms ON, 500ms OFF, 5 fois
LED_BUILTIN_BLINK_START(500, 5);
```

#### Rapport cyclique personnalisé
```cpp
// Période de 1000ms, 25% ON (250ms), 75% OFF (750ms), 3 fois
LED_BUILTIN_BLINK_DUTY_START(1000, 0.25, 3);
```

#### Temps ON/OFF indépendants
```cpp
// 200ms ON, 800ms OFF, 10 fois
LED_BUILTIN_BLINK_TIMING_START(200, 800, 10);
```

#### Contrôle par fréquence
```cpp
// 2 Hz, rapport cyclique 30%, pendant 5000ms
LED_BUILTIN_BLINK_FREQ_START(2.0, 0.3, 5000);
```

#### Motif personnalisé
```cpp
const uint8_t pattern[] = {1, 0, 1, 0, 1, 0};  // ON, OFF, ON, OFF, ON, OFF
const uint16_t times[] = {100, 100, 100, 100, 500, 1000};

// Répète le motif 3 fois
LED_BUILTIN_BLINK_PATTERN_START(pattern, times, 6, 3);
```

#### Signal SOS
```cpp
LED_BUILTIN_SOS_START();     // ...---... (morse)
```

#### Contrôle de l'animation
```cpp
LED_BUILTIN_STOP();          // Arrête l'animation en cours
LED_BUILTIN_IS_ACTIVE();     // Retourne true si une animation est active
```

## 🎨 Support LED RGB (M5Stack ATOM)

**Note importante** : Le support RGB nécessite l'installation de la bibliothèque **Adafruit NeoPixel**. Si vous ne l'installez pas, vous verrez un warning à la compilation mais les fonctions LED standard fonctionneront normalement.

Pour les cartes équipées de LED RGB WS2812 :

```cpp
#include "LED_BUILTIN.h"

void setup() {
  ENABLE_LED_BUILTIN();
  
  // Pour utiliser les fonctions RGB, installez d'abord Adafruit NeoPixel
  // Définir la couleur et la luminosité
  LED_RGB_SET_COLOR(255, 0, 0, 50);  // Rouge, luminosité 50/255
  LED_RGB_ON();
  delay(1000);
  
  // Couleurs prédéfinies
  LED_RGB_GREEN();
  LED_RGB_ON();
  delay(1000);
  
  LED_RGB_BLUE();
  LED_RGB_ON();
  delay(1000);
  
  // Clignotement avec couleur
  LED_RGB_YELLOW();
  LED_BUILTIN_BLINK_START(300, 5);
}

void loop() {
  LED_BUILTIN_UPDATE();
}
```

### Couleurs prédéfinies RGB
```cpp
LED_RGB_RED()        // Rouge
LED_RGB_GREEN()      // Vert
LED_RGB_BLUE()       // Bleu
LED_RGB_YELLOW()     // Jaune
LED_RGB_CYAN()       // Cyan
LED_RGB_MAGENTA()    // Magenta
LED_RGB_WHITE()      // Blanc
LED_RGB_ORANGE()     // Orange
LED_RGB_PURPLE()     // Violet
```

## 🔄 Mode compatibilité (API bloquante)

Si vous avez du code existant utilisant l'ancienne version, activez le mode compatibilité :

```cpp
#define LED_BUILTIN_COMPATIBILITY_MODE
#include "LED_BUILTIN.h"

void setup() {
  ENABLE_LED_BUILTIN();
}

void loop() {
  // Ancien code - fonctionne de manière bloquante
  LED_BUILTIN_BLINK(500, 3);  // Bloque pendant l'exécution
  // ...
}
```

## 🎯 Exemples avancés

### Indicateur d'état réseau
```cpp
void loop() {
  LED_BUILTIN_UPDATE();
  
  if(WiFi.status() == WL_CONNECTED) {
    if(!LED_BUILTIN_IS_ACTIVE()) {
      // Connecté : clignotement lent
      LED_BUILTIN_BLINK_TIMING_START(100, 2900, 255);
    }
  } else {
    if(!LED_BUILTIN_IS_ACTIVE()) {
      // Déconnecté : clignotement rapide
      LED_BUILTIN_BLINK_START(200, 255);
    }
  }
  
  // Votre code réseau ici
}
```

### Séquence de démarrage
```cpp
void setup() {
  ENABLE_LED_BUILTIN();
  
  // Pattern de démarrage
  const uint8_t boot_pattern[] = {1,0,1,0,1,0,1,0,1};
  const uint16_t boot_times[] = {50,50,50,50,50,50,100,100,500};
  
  LED_BUILTIN_BLINK_PATTERN_START(boot_pattern, boot_times, 9, 1);
  
  // L'initialisation continue pendant que la LED clignote
  WiFi.begin(ssid, password);
}

void loop() {
  LED_BUILTIN_UPDATE();
  // ...
}
```

### Alerte d'erreur
```cpp
void showError() {
  LED_BUILTIN_STOP();  // Arrête toute animation en cours
  
  #ifdef LED_BUILTIN_IS_RGB
    LED_RGB_RED();  // Passe en rouge pour les LED RGB
  #endif
  
  // Clignotement rapide d'urgence
  LED_BUILTIN_BLINK_START(100, 255);
}
```

## 🔧 Configuration avancée

### Surcharger le GPIO
```cpp
// Avant d'inclure la bibliothèque
#define LED_BUILTIN 13  // Forcer GPIO13

#include "LED_BUILTIN.h"
```

### Surcharger la polarité
```cpp
// 0 = LOW active (inversée), 1 = HIGH active
#define LED_BUILTIN_POLARITY 1

#include "LED_BUILTIN.h"
```

## 📝 Notes importantes

1. **Toujours appeler `LED_BUILTIN_UPDATE()`** dans votre `loop()` pour le mode non-bloquant
2. Les LED RGB nécessitent la bibliothèque **Adafruit_NeoPixel** (installation optionnelle - warning si absente)
3. Sur ESP8266, la plupart des LED sont **inversées** (LOW = allumé)
4. Sur ESP32, la plupart des LED sont **standard** (HIGH = allumé)
5. Le mode compatibilité utilise `yield()` pour rester relativement responsive
6. La bibliothèque fonctionne sans dépendance pour les LED standard

## 🐛 Dépannage

### La LED ne clignote pas
- Vérifiez que vous appelez `LED_BUILTIN_UPDATE()` dans `loop()`
- Vérifiez que `ENABLE_LED_BUILTIN()` a été appelé dans `setup()`

### LED RGB ne fonctionne pas
- Installez la bibliothèque **Adafruit_NeoPixel** (requis pour RGB)
  - PlatformIO : ajoutez `adafruit/Adafruit NeoPixel@^1.12.0` dans lib_deps
  - Arduino IDE : Gestionnaire de bibliothèques → "Adafruit NeoPixel"
- Vérifiez que votre carte est bien détectée (M5Stack ATOM)
- Si vous voyez un warning sur NeoPixel, c'est normal - installez simplement la bibliothèque

### LED reste allumée/éteinte en permanence
- Vérifiez la polarité de votre carte
- Utilisez `#define LED_BUILTIN_POLARITY` pour forcer la polarité

### Mauvais GPIO détecté
- Définissez manuellement `LED_BUILTIN` avant l'include
- Vérifiez le nom de votre carte dans l'IDE Arduino

## 📄 Licence

GPL-3.0 license

## 🤝 Contribution

Les contributions sont les bienvenues ! N'hésitez pas à :
- Signaler des bugs
- Proposer de nouvelles fonctionnalités
- Ajouter le support de nouvelles cartes
- Améliorer la documentation

## 📧 Support

Pour toute question ou problème, ouvrez une issue sur GitHub.

---

**Version 2.0** - Bibliothèque non-bloquante avec support LED RGB
