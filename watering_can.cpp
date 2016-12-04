/*http://2m3g1.com/2693.html*/

/** 自動水やりプログラム **/
 
#include <avr/sleep.h>
#include <avr/wdt.h>
#define BEAT 300   // 音の長さを指定
#define PINNO 12   // 圧電スピーカを接続したピン番号
 
int led = 13;                           // LEDピン
 
void setup() {                
  pinMode(led, OUTPUT);     
}
 
void loop() {
  tone(PINNO,262,BEAT) ;  // ド
  delay(BEAT) ;
  tone(PINNO,294,BEAT) ;  // レ
  delay(BEAT) ;
  tone(PINNO,330,BEAT) ;  // ミ
  delay(BEAT) ;
  tone(PINNO,262,BEAT) ;  // ド
  delay(BEAT) ;
  tone(PINNO,294,BEAT) ;  // レ
  delay(BEAT) ;
  tone(PINNO,330,BEAT) ;  // ミ
  delay(BEAT) ;
  tone(PINNO,392,BEAT) ;  // ソ
  delay(BEAT) ;    
  tone(PINNO,330,BEAT) ;  // ミ
  delay(BEAT) ;
  tone(PINNO,294,BEAT) ;  // レ
  delay(BEAT) ;
  tone(PINNO,262,BEAT) ;  // ド
  delay(BEAT) ;
  tone(PINNO,294,BEAT) ;  // レ
  delay(BEAT) ;
  tone(PINNO,330,BEAT) ;  // ミ
  delay(BEAT) ;
  tone(PINNO,294,BEAT) ;  // レ
  delay(BEAT) ;
  delay(1000) ;           // 1秒待つ
 
  digitalWrite(led,HIGH); //11番ピンの出力をHIGH = 5Vにする
  delay(5000); //ポンプ動作時間＝水やり時間
  digitalWrite(led,LOW); //11番ピンの出力をLOW = 0Vにする
 
  //24時間待機ウォッチドックタイマを使ったシャットダウンプログラム
   
   
  int var = 0;
  while(var < 10800){
    delayWDT(9);     // 8秒間のシャットダウン                  
    var++;           // 10800回繰り返し＝24時間                  
  } 
}
 
void delayWDT(unsigned long t) {        // パワーダウンモードでdelayを実行
  delayWDT_setup(t);                    // ウォッチドッグタイマー割り込み条件設定
  ADCSRA &= ~(1 << ADEN);               // ADENビットをクリアしてADCを停止（120μA節約）
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  // パワーダウンモード
  sleep_enable();
 
  sleep_mode();                         // ここでスリープに入る
 
  sleep_disable();                      // WDTがタイムアップでここから動作再開 
  ADCSRA |= (1 << ADEN);                // ADCの電源をON (|=が!=になっていたバグを修正2014/11/17)
 
}
 
void delayWDT_setup(unsigned int ii) {  // ウォッチドッグタイマーをセット。
  // 引数はWDTCSRにセットするWDP0-WDP3の値。設定値と動作時間は概略下記
  // 0=16ms, 1=32ms, 2=64ms, 3=128ms, 4=250ms, 5=500ms
  // 6=1sec, 7=2sec, 8=4sec, 9=8sec
  byte bb;
  if (ii > 9 ){                         // 変な値を排除
    ii = 9;
  }
  bb =ii & 7;                           // 下位3ビットをbbに
  if (ii > 7){                          // 7以上（7.8,9）なら
    bb |= (1 << 5);                     // bbの5ビット目(WDP3)を1にする
  }
  bb |= ( 1 << WDCE );
 
  MCUSR &= ~(1 << WDRF);                // MCU Status Reg. Watchdog Reset Flag ->0
  // start timed sequence
  WDTCSR |= (1 << WDCE) | (1<<WDE);     // ウォッチドッグ変更許可（WDCEは4サイクルで自動リセット）
  // set new watchdog timeout value
  WDTCSR = bb;                          // 制御レジスタを設定
  WDTCSR |= _BV(WDIE);
} 
 
ISR(WDT_vect) {                         // WDTがタイムアップした時に実行される処理
  //  wdt_cycle++;                        // 必要ならコメントアウトを外す
}
