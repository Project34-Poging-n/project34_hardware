#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

// Define array to store authorized card numbers
byte authorizedCards[][4] = {
  {0xDE, 0xAD, 0xBE, 0xEF}, // Add your authorized card numbers here
  {0x12, 0x34, 0x56, 0x78},
  {0x98, 0x76, 0x54, 0x32}
};

void setup() {
  Serial.begin(9600); // Initialize serial communication
  SPI.begin(); // Initialize SPI bus
  mfrc522.PCD_Init(); // Initialize MFRC522
}

void loop() {
  // Look for new cards
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    Serial.print("Scanned card UID:");
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println();

    // Check if card UID matches an authorized card
    boolean authorized = false;
    for (byte i = 0; i < sizeof(authorizedCards) / 4; i++) {
      if (memcmp(mfrc522.uid.uidByte, authorizedCards[i], 4) == 0) {
        authorized = true;
        break;
      }
    }
    if (authorized) {
      Serial.println("Access granted!");
    } else {
      Serial.println("Access denied.");
    }

    // Halt PICC
    mfrc522.PICC_HaltA();
    // Stop encryption on PCD
    mfrc522.PCD_StopCrypto1();
  }
}
