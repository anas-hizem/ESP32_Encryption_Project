#include <WiFi.h>
#include <PubSubClient.h>
#include <CryptoAES_CBC.h>
#include <AES.h>

// Configuration WiFi
const char* ssid = "*****";
const char* password = "******";

// Configuration MQTT
const char* mqtt_server = "test.mosquitto.org"; // Broker MQTT public
const char* mqtt_topic = "esp32/encrypted_message";

WiFiClient espClient;
PubSubClient client(espClient);

AES128_ESP aes;
byte key[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '1', '2', '3', '4'}; // 16-byte key

unsigned char decryptedtext[16]; // Texte déchiffré

// Fonction de callback pour gérer les messages reçus
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message reçu sur le topic: ");
  Serial.println(topic);
  
  // Déchiffrement du message reçu
  if (length == sizeof(decryptedtext)) {
    aes.decryptBlock(decryptedtext, payload); // Déchiffrement du message

    // Affichage du message déchiffré
    Serial.print("Message déchiffré: ");
    for (int i = 0; i < sizeof(decryptedtext); i++) {
      Serial.print((char)decryptedtext[i]);
    }
    Serial.println();
  } else {
    Serial.println("Erreur: Taille du message incorrecte.");
  }
}

void setup() {
  // Initialisation série
  Serial.begin(9600);

  // Connexion WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  // Connexion au serveur MQTT
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback); // Définir la fonction de rappel pour gérer les messages reçus

  while (!client.connected()) {
    if (client.connect("ESP32_Receiver")) {
      Serial.println("Connected to MQTT broker");
      client.subscribe(mqtt_topic); // S'abonner au topic
    } else {
      delay(5000);
    }
  }

  aes.setKey(key, 16); // Initialisation de la clé AES
}

void loop() {
  client.loop(); // Vérifier les messages MQTT en attente

  delay(500); // Attendre avant de vérifier à nouveau
}
