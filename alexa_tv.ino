#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <fauxmoESP.h>

fauxmoESP fauxmo;

#include <IRremoteESP8266.h>
#include <IRsend.h>



IRsend irsend(14);//赤外線送信PINを定義

int flagTV =0;
int flagA = 0;
int flagB = 0;
int flagC = 0;
int flagD = 0;
int flagE = 0;


//テレビリモコンの各ボタンの赤外線信号を定義
int standard=0x555A;
int btn_onoff=0x555AF148688B;
int btn_1=0x555AF148724C;
int btn_2=0x555AF148F244;
int btn_4=0x555AF1488A4B;
int btn_5=0x555AF1484A47;
int btn_6=0x555AF148CA4F;
int btn_7=0x555AF1482A41;
int btn_8=0x555AF148AA49;
int btn_change=0x555AF148C881;
//上記は、リモコンの赤外線信号検出の結果（panasonic）


//esp8266に認識させるwifiを設定
const char *ssid ="";//your wifi ssid 
const char *password ="";//your wifi password

//デバイス名を定義
#define IDtv "テレビ" //テレビをオンオフする
#define IDchA "chA" //チャンネルを４、５にする
#define IDchB "chB" //チャンネルを６，８にする
//注意：alexa第三世代の場合　３つまで
//３つ以上だとデバイス検出時に認識しません

void setup() { 
  Serial.begin(115200);
  if (connectWifi()) {
    // Setup fauxmo
     Serial.println("Adding TV device");
     fauxmo.setPort(80);  
     fauxmo.enable(true);
     fauxmo.addDevice(IDtv);
     fauxmo.addDevice(IDchA);
     fauxmo.addDevice(IDchB);
     //注意：ここもalexa第三世代の場合　３つまで
     //３つ以上だとデバイス検出時に認識しません
     }
  
  irsend.begin();
     fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
        Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);

        if (strcmp(device_name,IDtv)==0) {
            if(state){
              flagTV = 1;
            }else{
              flagTV = 2;
            }
             }else if (strcmp(device_name,IDchA)==0) {
            if(state){
              flagA = 1;
            }else{
              flagA = 2;
            }
        }else if (strcmp(device_name,IDchB)==0) {
            if(state){
              flagB = 1;
            }else{
              flagB = 2;
            }
        }
     });
}
void loop() {
  fauxmo.handle();

  if(flagTV == 1){
      tvOn();
      flagTV = 0;
    }
    else if(flagTV == 2){
      tvOff();
      flagTV = 0;
    }
    
    if(flagA == 1){
      ch4();
      flagA = 0;
    }else if(flagA == 2){
      ch5();
      flagA = 0;
    }

    if(flagB == 1){
      ch6();
      flagB = 0;
    }else if(flagB == 2){
      ch8();
      flagB = 0;
    }
}

void tvOn() {
  Serial.print("TV turn on ...");
  irsend.sendPanasonic(standard,btn_onoff);
  delay(10);
  irsend.sendPanasonic(standard,btn_onoff);
}

void tvOff() {
  Serial.print("TV turn off ...");
  irsend.sendPanasonic(standard,btn_onoff);
}

void ch1() {
  Serial.print("ch1 on ...");
  irsend.sendPanasonic(standard,btn_1);
}

void ch2() {
  Serial.print("ch2 on ...");
  irsend.sendPanasonic(standard,btn_2);
}

void ch4() {
  Serial.print("ch4 on ...");
  irsend.sendPanasonic(standard,btn_4);
}

void ch5() {
  Serial.print("ch5 on ...");
  irsend.sendPanasonic(standard,btn_5);
}

void ch6() {
  Serial.print("ch6 on ...");
  irsend.sendPanasonic(standard,btn_6);
}

void ch7() {
  Serial.print("ch7 on ...");
  irsend.sendPanasonic(standard,btn_7);
}

void ch8() {
  Serial.print("ch8 on ...");
  irsend.sendPanasonic(standard,btn_8);
}

void change() {
  Serial.print("change on ...");
  irsend.sendPanasonic(standard,btn_change);
  delay(3000);
  irsend.sendPanasonic(standard,btn_change);
  delay(100);
  irsend.sendPanasonic(standard,btn_change);
  delay(100);
  irsend.sendPanasonic(standard,btn_change);
}

boolean connectWifi() {
  // wifi接続↓↓
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(".......");
  Serial.println("WiFi Connected....IP Address:");
  Serial.println(WiFi.localIP());
  return true;
}
