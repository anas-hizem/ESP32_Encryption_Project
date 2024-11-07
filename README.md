# ESP32 Encryption Project

## Description

Ce projet utilise un ESP32 pour démontrer un système de communication sécurisé via MQTT, en utilisant le chiffrement AES (Advanced Encryption Standard). L'ESP32 agit comme un émetteur et un récepteur qui envoie et reçoit des messages chiffrés.

- **ESP32_Sender** : Le dispositif envoie des messages chiffrés via MQTT.
- **ESP32_Receiver** : Le récepteur reçoit les messages chiffrés via MQTT, les déchiffre et affiche le message en clair.

Les messages sont chiffrés à l'aide de l'algorithme AES-128 en mode CBC (Cipher Block Chaining), garantissant la confidentialité des données échangées.

## Fonctionnalités

- **Chiffrement AES-128 CBC** : Le message est chiffré avant d'être envoyé sur le réseau MQTT.
- **Communication MQTT** : Utilisation de MQTT pour l'échange de messages entre les dispositifs.
- **Affichage des messages** : Le récepteur déchiffre les messages et les affiche dans le moniteur série.
- **Wi-Fi intégré** : Connexion au réseau Wi-Fi pour la communication via MQTT.

## Matériel requis

- **ESP32** : Le microcontrôleur utilisé pour ce projet.
- **Module Wi-Fi** : L'ESP32 inclut un module Wi-Fi intégré pour la communication.
- **Broker MQTT** : Utilisation de `test.mosquitto.org`, un broker MQTT public pour la démonstration.

## Installation

### Prérequis

1. **Arduino IDE** : Ce projet utilise l'environnement de développement Arduino. Téléchargez et installez l'IDE Arduino depuis [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software).
   
2. **Bibliothèques nécessaires** :
   - `WiFi.h` : Bibliothèque pour la connexion Wi-Fi.
   - `PubSubClient.h` : Bibliothèque pour la gestion de la communication MQTT.
   - `AES.h` et `CryptoAES_CBC.h` : Bibliothèques pour le chiffrement AES.

### Étapes d'installation

1. Téléchargez ou clonez ce projet sur votre machine.
   
2. Ouvrez l'IDE Arduino, puis importez les fichiers `.ino` du projet.

3. Installez les bibliothèques nécessaires dans Arduino IDE :
   - Allez dans **Sketch** > **Include Library** > **Manage Libraries**.
   - Recherchez et installez les bibliothèques suivantes :
     - **WiFi** (pour ESP32)
     - **PubSubClient**
     - **AES** (et/ou **CryptoAES**)

4. Configurez votre réseau Wi-Fi :
   - Modifiez les variables `ssid` et `password` dans le fichier `ESP32_Sender.ino` et `ESP32_Receiver.ino` pour correspondre à votre réseau Wi-Fi.

5. Téléversez le fichier `ESP32_Sender.ino` sur votre premier ESP32 et le fichier `ESP32_Receiver.ino` sur votre second ESP32.

6. Connectez les deux ESP32 à votre réseau Wi-Fi et assurez-vous qu'ils communiquent correctement via MQTT.

## Utilisation

### ESP32_Sender

- Le dispositif émetteur enverra un message chiffré toutes les 5 secondes.
- Le message sera envoyé au broker MQTT et sera disponible pour le récepteur.
  
### ESP32_Receiver

- Le récepteur se connecte au même broker MQTT et attend les messages.
- Lorsqu'un message est reçu, il est déchiffré et affiché dans le moniteur série.

### Exemple de message échangé :

- **Message envoyé (chiffré)** : `FC 50 59 23 61 4C 9A 64 78 7E B3 AD 1A 56 49 B3`
- **Message déchiffré** : `Hello, ESP32!`


## Auteurs

- **Anas Hizem** : Créateur du projet

## Licence

Ce projet est sous licence MIT. Consultez le fichier [LICENSE](LICENSE) pour plus de détails.

## Remerciements

- Merci à [Mosquitto](https://mosquitto.org/) pour le broker MQTT.
- Merci à [Arduino](https://www.arduino.cc/) pour son excellent environnement de développement.
- Merci à la communauté de développement ESP32 pour ses bibliothèques et son support.

---
