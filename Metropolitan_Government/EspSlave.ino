/**
   ESPNOW - Basic communication - Master
   Date: 26th September 2017
   Author: Arvind Ravulavaru <https://github.com/arvindr21>
   Purpose: ESPNow Communication between a Master ESP32 and multiple ESP32 Slaves
   Description: This sketch consists of the code for the Master module.
   Resources: (A bit outdated)
   a. https://espressif.com/sites/default/files/documentation/esp-now_user_guide_en.pdf
   b. http://www.esploradores.com/practica-6-conexion-esp-now/
   << This Device Master >>
   Flow: Master
   Step 1 : ESPNow Init on Master and set it in STA mode
   Step 2 : Start scanning for Slave ESP32 (we have added a prefix of `slave` to the SSID of slave for an easy setup)
   Step 3 : Once found, add Slave as peer
   Step 4 : Register for send callback
   Step 5 : Start Transmitting data from Master to Slave(s)
   Flow: Slave
   Step 1 : ESPNow Init on Slave
   Step 2 : Update the SSID of Slave with a prefix of `slave`
   Step 3 : Set Slave in AP mode
   Step 4 : Register for receive callback and wait for data
   Step 5 : Once data arrives, print it in the serial monitor
   Note: Master and Slave have been defined to easily understand the setup.
         Based on the ESPNOW API, there is no concept of Master and Slave.
         Any devices can act as master or salve.
  // Sample Serial log with 1 master & 2 slaves
      Found 12 devices
      1: Slave:24:0A:C4:81:CF:A4 [24:0A:C4:81:CF:A5] (-44)
      3: Slave:30:AE:A4:02:6D:CC [30:AE:A4:02:6D:CD] (-55)
      2 Slave(s) found, processing..
      Processing: 24:A:C4:81:CF:A5 Status: Already Paired
      Processing: 30:AE:A4:2:6D:CD Status: Already Paired
      Sending: 9
      Send Status: Success
      Last Packet Sent to: 24:0a:c4:81:cf:a5
      Last Packet Send Status: Delivery Success
      Send Status: Success
      Last Packet Sent to: 30:ae:a4:02:6d:cd
      Last Packet Send Status: Delivery Success
*/

/**
　　和訳（独自解釈込み）
　　マスター：送信側のこと
　　スレーブ：受信側のこと
   << This Device Master >>
   マスターの使用方法
   Step 1 : WiFiをSTAモードにし，ESPNowを起動
   Step 2 : ESP32のスレーブ検索 (簡単のために，スレーブに共通のSSID(注：WiFi名のこと)を設定している)
   Step 3 : 見つけたら，Peer（接続）する
   Step 4 : （削除）送信時に呼び出される関数を定義・登録
   Step 5 : マスターからスレーブへデータを送信する
   スレーブの使用方法
   Step 1 : SSIDをマスターに合わせて設定
   Step 2 : WiFiをAPモードに設定
   Step 3 : ESPNowを起動
   Step 4 : データを受信したときに呼び出される関数を定義し，登録
   Step 5 : データ受信時にStep4で登録された関数が呼び出される
   注意: 簡単のために，このサンプルではマスターとスレーブという役分けをしているが，
   どのデバイスもマスター・スレーブどちらとしても扱える。

   ＊訳注1：WiFi.mode(WIFI_AP_STA)とすることで受信送信双方向の通信が可能
   ＊訳注2：原文ではWiFiのモードを変更する前にESPNowを起動しているが，
   　　　　 プログラム上これらが逆なので訳文では逆にしている

   (あとはログのサンプルなので省略)
*/

#include <esp_now.h>
#include <WiFi.h>

//通信するチャンネル
const int CHANNEL_SLAVE = 1;

// config AP SSID
void configDeviceAP() {
  String Mac = WiFi.macAddress();
  String SSID = SLAVE_SSID + "0";
  String Password = "123456789";
  bool result = WiFi.softAP(SSID.c_str(), Password.c_str(), CHANNEL_SLAVE, 0);
  if (!result) {
    Serial.println("AP Config failed.");
  } else {
    Serial.println("AP Config Success. Broadcasting with AP: " + String(SSID));
  }
}

void registerReceiveFunc(void (*func)(const uint8_t *mac_addr, const uint8_t *data, int data_len)){
    esp_now_register_recv_cb(func);
}

void setupESPSlave(){
  WiFi.mode(WIFI_AP);
  configDeviceAP();
  InitESPNow();
}
