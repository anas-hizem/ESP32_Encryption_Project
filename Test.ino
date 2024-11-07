#include <Crypto.h>
#include <AES.h>
#include <string.h>

// Define the AES key (128-bit)
byte key[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
                0xab, 0xf7, 0x97, 0x75, 0x46, 0x25, 0x10, 0x01};

// Plaintext message to encrypt
byte message[16] = "Hello, ESP32!";

// Initialize AES object
AES aes;

void setup() {
  // Start serial communication
  Serial.begin(115200);
  
  // Display the original message
  Serial.print("Original message: ");
  for (int i = 0; i < 16; i++) {
    Serial.print((char)message[i]);
  }
  Serial.println();

  // Encrypt the message using AES
  aes.do_aes_encrypt(message, 16, message, key, AES::AES_KEYSIZE_128, AES::CBC);

  // Display the encrypted message
  Serial.print("Encrypted message: ");
  for (int i = 0; i < 16; i++) {
    Serial.print(message[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}

void loop() {
  // Nothing to do in loop
}
