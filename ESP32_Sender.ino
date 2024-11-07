#include <WiFi.h>
#include <PubSubClient.h>
#include <CryptoAES_CBC.h>
#include <AES.h>

// Configuration WiFi
const char* ssid = "*****";
const char* password = "*****";

// Configuration MQTT
const char* mqtt_server = "test.mosquitto.org"; // Broker MQTT public
const char* mqtt_topic = "esp32/encrypted_message";

WiFiClient espClient;
PubSubClient client(espClient);

AES128_ESP aes;
byte key[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '1', '2', '3', '4'}; // 16-byte key

String message = "Hello, ESP32!abc";

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
  while (!client.connected()) {
    if (client.connect("ESP32_Sender")) {
      Serial.println("Connected to MQTT broker");
    } else {
      delay(5000);
    }
  }

  aes.setKey(key, 16); // Initialisation de la clé AES
}

void loop() {
  // Préparer le texte clair
  unsigned char cleartext[16]; // Taille du bloc AES
  memset(cleartext, 0, sizeof(cleartext)); // Réinitialiser
  message.getBytes(cleartext, sizeof(cleartext)); // Copier le message dans cleartext

  // Chiffrement AES
  unsigned char ciphertext[16]; // Taille du bloc AES
  aes.encryptBlock(ciphertext, cleartext);

  // Envoyer le message chiffré via MQTT
  client.publish(mqtt_topic, ciphertext, sizeof(ciphertext));
  Serial.println("Message sent");

  // Afficher le message chiffré en hexadécimal
  Serial.print("Encrypted message: ");
  for (int i = 0; i < sizeof(ciphertext); i++) {
    Serial.print(ciphertext[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  delay(5000); // Attendre avant de renvoyer
}
