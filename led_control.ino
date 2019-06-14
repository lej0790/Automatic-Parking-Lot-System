//초음파 센서를 사용하기 위한 기본 설정
#define CTM 10
#define CTM 11
#define CTM 12

const int TRIGPIN8 = 8;
const int TRIGPIN7 = 7;
const int TRIGPIN5 = 5;

const int ECHOPIN9 = 9;
const int ECHOPIN6 = 6;
const int ECHOPIN4 = 4;

int cds = A0;

void setup() {
  Serial.begin(9600);
  pinMode(TRIGPIN8, OUTPUT);
  pinMode(ECHOPIN9, INPUT);

  pinMode(TRIGPIN7, OUTPUT);
  pinMode(ECHOPIN6, INPUT);

  pinMode(TRIGPIN5, OUTPUT);
  pinMode(ECHOPIN4, INPUT);

  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);



}



void loop() {

  int dur1; // 시간 차(µ초)
  int dur2; // 시간 차(µ초)
  int dur3; // 시간 차(µ초)

  float dis1; // 거리(cm)
  float dis2; // 거리(cm)
  float dis3; // 거리(cm)

  //초음파센서1에서의 거리측정
  digitalWrite(TRIGPIN8, HIGH);
  delayMicroseconds(CTM);
  digitalWrite(TRIGPIN8, LOW);
  dur1 = pulseIn(ECHOPIN9, HIGH);
  dis1 = (float) dur1 * 0.017;

  //초음파센서2에서의 거리측정
  digitalWrite(TRIGPIN7, HIGH);
  delayMicroseconds(CTM);
  digitalWrite(TRIGPIN7, LOW);
  dur2 = pulseIn(ECHOPIN6, HIGH);
  dis2 = (float) dur2 * 0.017;

  //초음파센서3에서의 거리측정
  digitalWrite(TRIGPIN5, HIGH);
  delayMicroseconds(CTM);
  digitalWrite(TRIGPIN5, LOW);
  dur3 = pulseIn(ECHOPIN4, HIGH);
  dis3 = (float) dur3 * 0.017;

  delay(100);

  
  if (dis1 > 0 && dis1 < 7) {
    //초음파센서1에서 거리가 0cm이상 7cm 이하면 LED끄기
    digitalWrite(11, LOW);
    Serial.println(" dis1");
    Serial.print(dis1);
    Serial.println(" cm");
    delay(300);

  } else {
    //이외의 경우는 LED 켜기
    digitalWrite(11, HIGH);
    Serial.println(" dis1");
    Serial.print(dis1);
    Serial.println(" cm");
    delay(300);
  }

  if (dis2 > 0 && dis2 < 7) {
    //초음파센서2에서 거리가 0cm이상 7cm 이하면 LED끄기
    digitalWrite(12, LOW);
    Serial.println(" dis2");
    Serial.print(dis2);
    Serial.println(" cm");
    delay(300);

  } else {
    digitalWrite(12, HIGH);
    Serial.println(" dis2");
    Serial.print(dis2);
    Serial.println(" cm");
    delay(300);
  }


  if (dis3 > 0 && dis3 < 7) {
    //초음파센서3에서 거리가 0cm이상 7cm 이하면 LED끄기
    digitalWrite(13, LOW);
    Serial.println(" dis3");
    Serial.print(dis3);
    Serial.println(" cm");
    delay(300);

  } else {
    digitalWrite(13, HIGH);
    Serial.println(" dis3");
    Serial.print(dis3);
    Serial.println(" cm");
    delay(300);
  }


  //조도센서값을 읽어들여 cdsValue에 저장하는 부분
  int cdsValue = analogRead(cds);

  Serial.print("cds =  ");
  Serial.println(cdsValue);
  delay(1000);

  //cdsValue가 100보다 크면 가로등이 켜짐
  if (cdsValue > 100) {
    digitalWrite(3, HIGH);
    digitalWrite(2, HIGH);
    Serial.println("led 켜짐");
  }

  //cdsValue가 50보다 작으면 가로등이 꺼짐
  else if (cdsValue < 50) {
    digitalWrite(3, LOW);
    digitalWrite(2, LOW);
    Serial.println("led 꺼짐");
  }


}
