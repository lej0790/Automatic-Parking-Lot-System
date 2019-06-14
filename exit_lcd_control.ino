#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);


//출구 lcd 출력용 소프트웨어시리얼
#include <SoftwareSerial.h>             // 소프트웨어 시리얼 통신 라이브러리 설정 
SoftwareSerial No2Arduino(2, 3);        // 수신 RX: D2, 송신 TX: D3 설정
//No2Arduino는 정해져있는 이름이 아니라 사용자가 지정해주는 것이다.

//출구 lcd 출력용 소프트웨어시리얼 플래그 및 스트링
boolean flag = false;
String str = "";
int count = 0;

void setup() {
  lcd.init();
  lcd.init();//하드웨어 준비 상태 확인.
  lcd.backlight();//백라이트 켜기


  //출구 lcd 출력용 소프트웨어시리얼
  No2Arduino.begin(9600);

  Serial.begin(9600);

}

void loop() {

  
  while (No2Arduino.available()) { // arduino3_exit_lcd에서 수신값이 있다면,
    //즉, arduino3_exit_lcd의 시리얼 모니터에 주차요금이 표시되었다면
    char a;
    lcd.setCursor(count, 0);
    int intvalue = No2Arduino.read();
    if (intvalue == 10 || intvalue == 13) {
    //아스키코드에서 10(줄바꿈)과 13(줄의 끝에서 시작 위치로 되돌아감)에 해당하는 문자는 걸러주기 위한 if문

    } else {
      //10과 13이 없다면 char형으로 형변환하여 a에 저장한 후 lcd에 출력
      a = (char)intvalue;
      lcd.print(a);
      count++;
    }
    flag = true;
  }

  if (flag) {
    count = 0;
    delay(3000);
    lcd.clear();
    flag = false;
  }


}
