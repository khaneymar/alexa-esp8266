
# alexa第三世代とESP-WROOM-02を使って、声でテレビを操作するためのコードです。

赤外線受信機、送信機を使いました。

赤外線信号を飛ばすので、エアコン等、さまざまな機器に応用可能です。

各種ライブラリは随時インクルードしてください。

## 使用した機器
### ・Alexa第三世代
### ・ESP-WROOM02
### ・赤外線受信機
### ・赤外線送信LED
### ・ブレッドボード
### ・ジャンパ線3本
### ・USBケーブル


## 手順
### １．ArduinoIDEを起動
![arduino_start](https://user-images.githubusercontent.com/55695847/74086018-5184f400-4ac2-11ea-83ca-975005b63a1b.jpeg)

### ２．IRremoteESP8266のライブラリーをインクルードする

### ３．「スケッチ例」→「IRRemoteESP8266」→「IRrecvDumpV2」を開く
![Screenshot from 2020-02-08 21-43-38](https://user-images.githubusercontent.com/55695847/74086888-ae84a800-4aca-11ea-8d6b-40d71347b22c.png)



### ４．ESP-WROOM02と赤外線受信機（コード無変更なら１４番PIN）を配線する。
![IMG_1072](https://user-images.githubusercontent.com/55695847/74086903-cceaa380-4aca-11ea-8ab5-681e9f16dd13.jpg)



### ５．配線したら、IRrecvDumpV2を開き、ESP-WROOM02にコンパイル＆書き込み

### ６．シリアルモニタを開いて、右下の書き込み速度を115200bpsに設定する

### ７．リモコンで使いそうなボタンを受信機に向かって押し、赤外線信号を調べておく

### ８．alexa_tv.inoを開き、wifiに接続する部分のコードにalexaとおなじwifiのssid,passwordを設定する

### ９．先程調べておいたそれぞれのボタンの赤外線信号を書き込む(コード２３行目で定義)
        ※リモコンがパナソニックで無い場合は、他の関数を定義する必要があります
        
### １０．ESP-WROOM02と赤外線送信機（コード無変更なら１４番PIN）を配線する
![IMG_1072](https://user-images.githubusercontent.com/55695847/74086741-37024900-4ac9-11ea-87fc-28b9b56e77fc.jpg)


### １１．配線したら、alexa_tv.inoを開き、ESP-WROOM02にコンパイル＆書き込み

### １２．スマートフォンからamazon alexaアプリを開く

### １３．開いたら、「デバイス」→「右上＋のボタンを押す」→「デバイスを追加」→「その他」→「デバイスを検出」
![IMG_1068](https://user-images.githubusercontent.com/55695847/74086752-69ac4180-4ac9-11ea-8a5f-23606e1a6259.jpg)
![IMG_1070](https://user-images.githubusercontent.com/55695847/74086764-847eb600-4ac9-11ea-919e-e0d093a92710.jpg)
![IMG_1071](https://user-images.githubusercontent.com/55695847/74086768-8fd1e180-4ac9-11ea-9336-778a68b430d2.jpg)

### １４．コード無変更なら「テレビ」、「chA」、「chB」が検出される

### １５．アプリから定形アクションに移動し、「アクションを追加」から「スマートホーム」で先程追加したデバイスを選択

### １６．定形アクションを設定できたら、実際に声で操作してみる

### １７．テレビや、デバイスが意図したように動けば成功です

#### ※赤外線が反応していないときがあるので近づけてみたり、角度を調節してください。

