//lcd 라이브러리 해더
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

//서보모터 라이브러리 해더
#include <Servo.h>
//입구 쪽 서보모터(주차장 차단기)
Servo myservo;
//출구 쪽 서보모터(주차장 차단기)
Servo myservo1;

//출구 RFID 라이브러리 해더
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

//출구 RFID 라이브러리
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;

//입구 쪽 RFID에서 인식한 카드 아이디 받아오기 위한 변수
String gettingid = "";

//입구 쪽 RFID에서 인식한 카드 아이디와 시간 저장하는 변수들
String cardid1 = "";
unsigned long  time1 = 0;
String cardid2 = "";
unsigned long  time2 = 0;
String cardid3 = "";
unsigned long  time3 = 0;

//입구의 주차차단기와 lcd를 컨트롤하기 위한 flag
boolean flag = false;

//출구의 RFID에 카드를 찍었을 때 카드 아이디를 저장하는 변수
String checkoutcardid = "";

#include <SoftwareSerial.h>             // 소프트웨어 시리얼 통신 라이브러리 설정 
SoftwareSerial No2Arduino(2, 3);        // 수신 RX: D2, 송신 TX: D3 설정
//No2Arduino는 정해져있는 이름이 아니라 사용자가 지정해주는 것이다.

void setup() {
  //lcd초기화 및 백라이트켜기
  lcd.init();
  lcd.init();
  lcd.backlight();

  myservo.attach(7);
  myservo.write(180);
  myservo1.attach(6);
  myservo1.write(180);

  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  No2Arduino.begin(9600);               // 아두이노 No1과의 통신 속도 설정
  Serial.begin(9600);                   // 시리얼 모니터에 표시할 통신 속도 설정

}

void loop() {
  while (No2Arduino.available()) { // arduino2_exit_read_card에서 수신값이 있다면,

    char a = (char)(No2Arduino.read());//수신값(정수값)을 char형으로 형변환해 char형 변수 a에 저장
    if ((String)a != "\n") {
      gettingid += (String)a;//a를 String 형으로 변환해서 String형의 gettingid 변수에 저장(복합대입연산자 += 를 이용)
    }
    flag = true;
  }

  //입구 쪽 RFID에 카드를 찍었을 때 이미 주차장에 들어온 차인지 확인하는 작업
  if (flag) {
    if (gettingid.toInt() == cardid1.toInt()) {
      flag = false;
      gettingid = "";
      Serial.println("이미 사용중인 카드 id 입니다");//아두이노1의 lcd에 띄워야한다

      //RFID 찍었을 때 첫 화면 (입구)
      lcd.init();
      lcd.init();
      lcd.backlight();
      lcd.setCursor(1, 0);
      lcd.print("Used card");
      delay(3000);
      lcd.clear();

      return;
    } else if (gettingid.toInt() == cardid2.toInt()) {
      flag = false;
      gettingid = "";
      Serial.println("이미 사용중인 카드 id 입니다");//아두이노1의 lcd에 띄워야한다

      //RFID 찍었을 때 첫 화면 (입구)
      lcd.init();
      lcd.init();
      lcd.backlight();
      lcd.setCursor(1, 0);
      lcd.print("Used card");
      delay(3000);
      lcd.clear();

      return;
    } else if (gettingid.toInt() == cardid3.toInt()) {
      flag = false;
      gettingid = "";
      Serial.println("이미 사용중인 카드 id 입니다");//아두이노1의 lcd에 띄워야한다

      //RFID 찍었을 때 첫 화면 (입구)
      lcd.init();
      lcd.init();
      lcd.backlight();
      lcd.setCursor(1, 0);
      lcd.print("Used card");
      delay(3000);
      lcd.clear();

      return;
    }

    //들어온 차의 카드아이디를 저장하는 과정
    if (cardid1.equals("")) {
      cardid1 = gettingid;
      gettingid = "";
      time1 = millis();

      //RFID 찍었을 때 첫 화면 (입구)
      lcd.init();
      lcd.init();
      lcd.backlight();
      lcd.setCursor(1, 0);
      lcd.print("Welcome to the");
      lcd.setCursor(1, 1);
      lcd.print("parking lot !!");
      delay(3000);
      lcd.clear();

      //입구 서보모터(주차차단기)
      myservo1.write(180);
      delay(1000);
      myservo1.write(90);
      delay(5000);
      myservo1.write(180);

      flag = false;
    } else if (cardid2.equals("")) {
      cardid2 = gettingid;
      gettingid = "";
      time2 = millis();

      //RFID 찍었을 때 첫 화면 (입구)
      lcd.init();
      lcd.init();
      lcd.backlight();
      lcd.setCursor(1, 0);
      lcd.print("Welcome to the");
      lcd.setCursor(1, 1);
      lcd.print("parking lot !!");
      delay(3000);
      lcd.clear();

      //입구 서보모터(주차차단기)
      myservo1.write(180);
      delay(1000);
      myservo1.write(90);
      delay(5000);
      myservo1.write(180);

      flag = false;
    } else if (cardid3.equals("")) {
      cardid3 = gettingid;
      gettingid = "";
      time3 = millis();

      //RFID 찍었을 때 첫 화면 (입구)
      lcd.init();
      lcd.init();
      lcd.backlight();
      lcd.setCursor(1, 0);
      lcd.print("Welcome to the");
      lcd.setCursor(1, 1);
      lcd.print("parking lot !!");
      delay(3000);
      lcd.clear();

      //입구 서보모터(주차차단기)
      myservo1.write(180);
      delay(1000);
      myservo1.write(90);
      delay(5000);
      myservo1.write(180);

      flag = false;
    } else {
      Serial.println("주차공간이 없습니다");

      //RFID 찍었을 때 첫 화면 (입구)
      lcd.init();
      lcd.init();
      lcd.backlight();
      lcd.setCursor(1, 0);
      lcd.print("There is no");
      lcd.setCursor(1, 1);
      lcd.print("parking space !!");
      delay(3000);
      lcd.clear();

      flag = false;
      gettingid = "";
    }
  }



  // 출구 쪽 RFID에 카드가 인식되었다면 다음으로 넘어가고 아니면 더이상
  // 실행 안하고 리턴
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // ID가 읽혀졌다면 다음으로 넘어가고 아니면 더이상
  // 실행 안하고 리턴
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  //카드 아이드를 10진수로 변환하는 함수
  printDec(rfid.uid.uidByte, rfid.uid.size);

  //주차된 차의 카드아이디와 출구 쪽 RFID에 찍힌 카드의 카드아이디와 비교해서 같으면
  //주차요금을 계산하는 부분. 주차요금은 계산 후 씨리얼모니터에 띄워서 arduino3_exit_lcd에 씨리얼 통신으로 보내진다.
  if (cardid1.toInt() == checkoutcardid.toInt()) {

    int price = ((millis() / 1000) - (time1 / 1000)) * 100;
    Serial.print("Fee : ");
    Serial.print(price);
    Serial.println(" won");

    time1 = 0;
    cardid1 = "";
    checkoutcardid = "";

    //출구 서보모터(주차차단기)
    myservo.write(180);
    delay(1000);
    myservo.write(90);
    delay(5000);
    myservo.write(180);

  } else if (cardid2.toInt() == checkoutcardid.toInt()) {
    int price = ((millis() / 1000) - (time2 / 1000)) * 100;
    Serial.print("Fee : ");
    Serial.print(price);
    Serial.println(" won");
    time2 = 0;
    cardid2 = "";
    checkoutcardid = "";

    //출구 서보모터(주차차단기)
    myservo.write(180);
    delay(1000);
    myservo.write(90);
    delay(5000);
    myservo.write(180);

  } else if (cardid3.toInt() == checkoutcardid.toInt()) {
    int price = ((millis() / 1000) - (time3 / 1000)) * 100;
    Serial.print("Fee : ");
    Serial.print(price);
    Serial.println(" won");

    time3 = 0;
    cardid3 = "";
    checkoutcardid = "";

    //출구 서보모터(주차차단기)
    myservo.write(180);
    delay(1000);
    myservo.write(90);
    delay(5000);
    myservo.write(180);

  } else {
    checkoutcardid = "";
    Serial.println("Unregisted card !");
  }

  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}

//출구 쪽 RFID에 카드를 찍었다면 찍은 카드의 카드아이디를 checkoutcardid변수에 저장하는 부분
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    byte b = buffer[i];
    if ((String)b != "\n") {
      checkoutcardid += (String)b;
    }
  }
}
