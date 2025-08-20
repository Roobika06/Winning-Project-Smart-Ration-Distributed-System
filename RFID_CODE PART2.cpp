#include <SPI.h> 
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 myRFID(SS_PIN, RST_PIN);   // Create MFRC522 instance.



void setup() 
{
  Serial.begin(9600);
  
  SPI.begin();          // Initiate SPI bus
  myRFID.PCD_Init();    // Initiate MFRC522
  Serial.println("Please scan your RFID card...");
  Serial.println();

}

void loop() 
{
  // Wait for RFID cards to be scanned
  if (!myRFID.PICC_IsNewCardPresent()) 
  {
    return;
  }

  // An RFID card has been scanned but no UID 
  if (!myRFID.PICC_ReadCardSerial()) 
  {
    return;
  }

  // Read UID
  String content = "";
  Serial.print("USER ID tag :");
  for (byte i = 0; i < myRFID.uid.size; i++) 
  {
    Serial.print(myRFID.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(myRFID.uid.uidByte[i], HEX);
    content.concat(String(myRFID.uid.uidByte[i] < 0x10 ? "0" : ""));
    content.concat(String(myRFID.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println();

  // Check if UID matches your card
  if (content == "63D1F0DA")  // ← your specific card number goes here (no spaces)
  {
    Serial.println("MONITORS IN STOCKROOM");
  
    Serial.println("Access granted");
    Serial.println("WHEAT CARD       ");
    Serial.print("MAN:16/MAY/2025");
    delay(300);

  }
  else if (content == "63231BDB")  // ← your specific card number goes here (no spaces)
  {
    Serial.println("MONITORS IN STOCKROOM");
  
    Serial.println("Access granted");
    Serial.println("SUGAR CARD        ");
    Serial.print("MAN:03/APRIL/2025");
    delay(300);

  }
  else
  {
    
    Serial.println("Access denied");
   
  
  }

  delay(1000);
}