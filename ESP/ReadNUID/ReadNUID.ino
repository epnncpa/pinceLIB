// lecture badge avec module RFID-RC522


// https://www.aranacorp.com/fr/utilisation-dun-module-rfid-avec-un-esp32/
// ESP32 WROOM 32 -> Outils - ESP32 - ESP32 Dev Module
/*
    Vcc <-> 3V3 (ou Vin(5V) selon la version du module)
    RST (Reset) <-> D0
    GND (Masse) <-> GND
    MISO (Master Input Slave Output) <-> 19
    MOSI (Master Output Slave Input) <-> 23
    SCK (Serial Clock) <-> 18
    SS/SDA (Slave select) <-> 5
*/



//Libraries
#include <SPI.h>//https://www.arduino.cc/en/reference/SPI
#include <MFRC522.h>//https://github.com/miguelbalboa/rfid

//Constants
#define SS_PIN 5
#define RST_PIN 0

//Parameters
const int ipaddress[4] = {103, 97, 67, 25};

//Variables
byte nuidPICC[4] = {0, 0, 0, 0};
MFRC522::MIFARE_Key key;
MFRC522 rfid = MFRC522(SS_PIN, RST_PIN);

void setup() {
 	//Init Serial USB
 	Serial.begin(115200);
 	Serial.println(F("Initialize System"));
 	//init rfid D8,D5,D6,D7
 	SPI.begin();
 	rfid.PCD_Init();

 	Serial.print(F("Reader :"));
 	rfid.PCD_DumpVersionToSerial();
}

void loop() {
 	readRFID();
}

void readRFID(void ) { /* function readRFID */
 	////Read RFID card

 	for (byte i = 0; i < 6; i++) {
 			key.keyByte[i] = 0xFF;
 	}
 	// Look for new 1 cards
 	if ( ! rfid.PICC_IsNewCardPresent())
 			return;

 	// Verify if the NUID has been readed
 	if ( 	!rfid.PICC_ReadCardSerial())
 			return;

 	// Store NUID into nuidPICC array
 	for (byte i = 0; i < 4; i++) {
 			nuidPICC[i] = rfid.uid.uidByte[i];
 	}

 	Serial.print(F("RFID In dec: "));
 	printDec(rfid.uid.uidByte, rfid.uid.size);
 	Serial.println();

 	// Halt PICC
 	rfid.PICC_HaltA();

 	// Stop encryption on PCD
 	rfid.PCD_StopCrypto1();

}


/**
 		Helper routine to dump a byte array as hex values to Serial.
*/
void printHex(byte *buffer, byte bufferSize) {
 	for (byte i = 0; i < bufferSize; i++) {
 			Serial.print(buffer[i] < 0x10 ? " 0" : " ");
 			Serial.print(buffer[i], HEX);
 	}
}

/**
 		Helper routine to dump a byte array as dec values to Serial.
*/
void printDec(byte *buffer, byte bufferSize) {
 	for (byte i = 0; i < bufferSize; i++) {
 			Serial.print(buffer[i] < 0x10 ? " 0" : " ");
 			Serial.print(buffer[i], DEC);
 	}
}

