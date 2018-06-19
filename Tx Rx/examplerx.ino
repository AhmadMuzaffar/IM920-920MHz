#include <SoftwareSerial.h>

SoftwareSerial IM920Serial(8, 9); // ソフトウエアシリアル
int busy = 0;
String inputstr = "";

void setup() {
 Serial.begin(19200);
 IM920Serial.begin(19200); // ソフトウエアシリアル 初期化
 pinMode(10, INPUT);       // Busy 信号 Pin10 入力

 while (!IM920Serial & !Serial ) { ; }
 delay(500);

 //デバイス登録機能。不揮発領域に書き込むので、あまり使わない
 //device_reg_process();
}

void loop() 
{ 
 do {
    busy = digitalRead(10); // Busy 信号 読み取り
 } while (busy != 0); // Busy なら Loop

  while (IM920Serial.available()) {
     
  Serial.println("debug");

    readPacket();
  };

  if (inputstr[-1] = '\n' && inputstr != "") {
//    sample:AB,0001,7C:13,57,9B,DF,02,46,8A,CE
    Serial.println(inputstr);
    inputstr = "";
  }

  delay(100);
 }

void readPacket() {
  inputstr += (char)IM920Serial.read();;
}

void sendPacket(String packet) {
  Serial.println("Send" + packet);
  IM920Serial.println(packet);
  delay(3000);
  while (IM920Serial.available() > 0) {
    readPacket();
  };
  delay(1000);
}

void device_reg_process(){
  sendPacket("ENWR");      //不揮発領域に書き込みを可能に
  sendPacket("SRID 9E46"); //受信対象の固有ID(この例では9E46)を設定
  sendPacket("DSWR");      //書き込みを再度禁止
}
