#include <SoftwareSerial.h>

SoftwareSerial IM920Serial(8, 9); // ソフトウエアシリアル
int busy;
unsigned char cnt = 0;
String inputstr = "";
char sendPacket[24] = "";


void setup() {
 IM920Serial.begin(19200); // ソフトウエアシリアル 初期化
 Serial.begin(19200);
 pinMode(10, INPUT);// Busy 信号 Pin10 入力
  while (!IM920Serial & !Serial ) { ; }
 delay(1000);
 Serial.print("ID:");

 IM920Serial.println("RDID");
  while (IM920Serial.available()) {
    readPacket();
 Serial.println("debug");
  };
 delay(1000);

}

void loop() {
  do {
    busy = digitalRead(10); // Busy 信号 読み取り
  } while (busy != 0); // Busy なら Loop
  
 IM920Serial.print("TXDT"); // 送信コマンド
 cnt = (0x00ff & (cnt + 1));  //カウンター。0xffで0x00に戻る
 
 sprintf(sendPacket, "%02x%s", cnt, "1122334455667788");
 IM920Serial.println(sendPacket); // アナログ値を HEX フォーマットで送信
Serial.println(sendPacket); //デバッグ用

 // 受信成功時にでる"OK"を拾いたい場合、以下を有効に
while (IM920Serial.available()) { 
Serial.write(IM920Serial.read());
}
   //uint8_t len = sizeof(sendPacket);
  // Serial.println(len);
   
 delay(2000);
}

void readPacket() {
  inputstr += (char)IM920Serial.read();;
}
