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

//スレーブの最大数
const int NUMSLAVES = 20;
//通信するチャンネル
const int CHANNEL_MASTER = 1;
//スキャンした結果をシリアルに表示数するか
const bool PRINTSCANRESULTS  = true;

//スレーブの情報が入った配列
esp_now_peer_info_t slaves[NUMSLAVES] = {};
//スレーブの数
int slaveCount = 0;

// Scan for slaves in AP mode
void ScanForSlave() {
  int8_t scanResults = WiFi.scanNetworks();
  //reset slaves
  memset(slaves, 0, sizeof(slaves));
  slaveCount = 0;
  if (scanResults == 0) {
    Serial.println("No WiFi devices in AP Mode found");
  } else {
    Serial.print("Found "); Serial.print(scanResults); Serial.println(" devices ");
    for (int i = 0; i < scanResults; ++i) {
      // Print SSID and RSSI for each device found
      String SSID = WiFi.SSID(i);
      int32_t RSSI = WiFi.RSSI(i);
      String BSSIDstr = WiFi.BSSIDstr(i);

      if (PRINTSCANRESULTS) {
        Serial.print(i + 1); Serial.print(": "); Serial.print(SSID); Serial.print(" ["); Serial.print(BSSIDstr); Serial.print("]"); Serial.print(" ("); Serial.print(RSSI); Serial.print(")"); Serial.println("");
      }
      delay(10);
      Serial.print(SSID);Serial.println(SSID.indexOf(SLAVE_SSID));
      // Check if the current device starts with `Slave`
      if (SSID.indexOf(SLAVE_SSID) == 0) {
        // SSID of interest
        Serial.print(i + 1); Serial.print(": "); Serial.print(SSID); Serial.print(" ["); Serial.print(BSSIDstr); Serial.print("]"); Serial.print(" ("); Serial.print(RSSI); Serial.print(")"); Serial.println("");
        // Get BSSID => Mac Address of the Slave
        int mac[6];

        if ( 6 == sscanf(BSSIDstr.c_str(), "%x:%x:%x:%x:%x:%x",  &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5] ) ) {
          for (int ii = 0; ii < 6; ++ii ) {
            slaves[slaveCount].peer_addr[ii] = (uint8_t) mac[ii];
          }
        }
        slaves[slaveCount].channel = CHANNEL_MASTER; // pick a channel
        slaves[slaveCount].encrypt = 0; // no encryption
        slaveCount++;
      }
    }
  }

  if (slaveCount > 0) {
    Serial.print(slaveCount); Serial.println(" Slave(s) found, processing..");
  } else {
    Serial.println("No Slave Found, trying again.");
  }

  // clean up ram
  WiFi.scanDelete();
}

// Check if the slave is already paired with the master.
// If not, pair the slave with master
void manageSlave() {
  if (slaveCount > 0) {
    for (int i = 0; i < slaveCount; i++) {
      Serial.print("Processing: ");
      for (int ii = 0; ii < 6; ++ii ) {
        Serial.print((uint8_t) slaves[i].peer_addr[ii], HEX);
        if (ii != 5) Serial.print(":");
      }
      Serial.print(" Status: ");
      // check if the peer exists
      bool exists = esp_now_is_peer_exist(slaves[i].peer_addr);
      if (exists) {
        // Slave already paired.
        Serial.println("Already Paired");
      } else {
        // Slave not paired, attempt pair
        esp_err_t addStatus = esp_now_add_peer(&slaves[i]);
        if (addStatus == ESP_OK) {
          // Pair success
          Serial.println("Pair success");
        } else if (addStatus == ESP_ERR_ESPNOW_NOT_INIT) {
          // How did we get so far!!
          Serial.println("ESPNOW Not Init");
        } else if (addStatus == ESP_ERR_ESPNOW_ARG) {
          Serial.println("Add Peer - Invalid Argument");
        } else if (addStatus == ESP_ERR_ESPNOW_FULL) {
          Serial.println("Peer list full");
        } else if (addStatus == ESP_ERR_ESPNOW_NO_MEM) {
          Serial.println("Out of memory");
        } else if (addStatus == ESP_ERR_ESPNOW_EXIST) {
          Serial.println("Peer Exists");
        } else {
          Serial.println("Not sure what happened");
        }
        delay(100);
      }
    }
  } else {
    // No slave found to process
    Serial.println("No Slave found to process");
  }
}

// send data
void sendData(uint8_t* data) {
  manageSlave();

  for (int i = 0; i < slaveCount; i++) {
    const uint8_t *peer_addr = slaves[i].peer_addr;
    if (i == 0) { // print only for first slave
      Serial.print("Sending: ");
    }
    esp_err_t result = esp_now_send(peer_addr, data, sizeof(data));
    Serial.print("Send Status: ");
    if (result == ESP_OK) {
      Serial.println("Success");
    } else if (result == ESP_ERR_ESPNOW_NOT_INIT) {
      // How did we get so far!!
      Serial.println("ESPNOW not Init.");
    } else if (result == ESP_ERR_ESPNOW_ARG) {
      Serial.println("Invalid Argument");
    } else if (result == ESP_ERR_ESPNOW_INTERNAL) {
      Serial.println("Internal Error");
    } else if (result == ESP_ERR_ESPNOW_NO_MEM) {
      Serial.println("ESP_ERR_ESPNOW_NO_MEM");
    } else if (result == ESP_ERR_ESPNOW_NOT_FOUND) {
      Serial.println("Peer not found.");
    } else {
      Serial.println("Not sure what happened");
    }
    delay(10);
  }
}


void setupESPMaster(){
  WiFi.mode(WIFI_STA);
  InitESPNow();
  ScanForSlave();
}
