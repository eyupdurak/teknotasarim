// Kütüphaneleri ekleyelim
#include <SPI.h>                       
#include <MFRC522.h>                      

int RST_PIN = 9;                          
int SS_PIN = 10;                          

// Kard id!
MFRC522 rfid(SS_PIN, RST_PIN);            
byte ID[4] = {84, 239, 237, 34};           

void setup() { 
  Serial.begin(9600);                     
  SPI.begin();                            
  rfid.PCD_Init();                        
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

}
 
void loop() {
  digitalWrite(4, HIGH);
  if ( ! rfid.PICC_IsNewCardPresent())  
    return;

  if ( ! rfid.PICC_ReadCardSerial())      
    return;

  if (rfid.uid.uidByte[0] == ID[0] &&     
    rfid.uid.uidByte[1] == ID[1] && 
    rfid.uid.uidByte[2] == ID[2] && 
    rfid.uid.uidByte[3] == ID[3] ) {
        Serial.println("Yeşil Led Yandi");
        ekranaYazdir();
        digitalWrite(5, HIGH);
        digitalWrite(4, LOW);
        delay(3000);
        digitalWrite(5, LOW);
        digitalWrite(4, HIGH);
        delay(3000);
    }
    else{                                
      Serial.println("Hatali Kart");
        digitalWrite(3, HIGH);
        digitalWrite(4, LOW);
        delay(3000);
        digitalWrite(3, LOW);
        digitalWrite(4, HIGH);
        delay(3000);
      ekranaYazdir();
    }
  rfid.PICC_HaltA();
}
void ekranaYazdir(){
  Serial.print("ID Numarasi: ");
  for(int sayac = 0; sayac < 4; sayac++){
    Serial.print(rfid.uid.uidByte[sayac]);
    Serial.print(" ");
  }
  Serial.println("");
}
