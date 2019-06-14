//입구 RFID 라이브러리 해더
#include <SPI.h>
#include <MFRC522.h>

// SS(Chip Select)과 RST(Reset) 핀 설정
#define SS_PIN 10
#define RST_PIN 9

// 입구 RFID 라이브러리 생성
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key;



void setup() {

  Serial.begin(9600);

  // SPI 시작
  SPI.begin(); // Init SPI bus
  
  // RFID 시작
  rfid.PCD_Init(); // Init MFRC522

  //초기 키 ID 초기화
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }


}

void loop() {

  // 입구쪽 RFID에 카드가 인식되었다면 다음으로 넘어가고 아니면 더이상 
  // 실행 안하고 리턴
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // ID가 읽혀졌다면 다음으로 넘어가고 아니면 더이상 
  // 실행 안하고 리턴
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  //카드 아이드를 10진수로 변환하는 함수  
  printDec(rfid.uid.uidByte, rfid.uid.size);
  Serial.println();

  
  // PICC 종료
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}


void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i], DEC);
  }
}
