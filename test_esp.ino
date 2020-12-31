//void setup() {
//  // put your setup code here, to run once:
//  Serial.begin(115200);
//  setupESPMaster();
//}
//
//void loop() {
//  // put your main code here, to run repeatedly:
//  uint8_t a[] = {1, 2, 3, 4};
//  sendData(a);
//  delay(1000);
//}

void recieve_data(const uint8_t *mac_addr, const uint8_t *data, int data_len){
  Serial.println(data[0]);
  
}

void setup(){
  Serial.begin(115200);
  setupESPSlave();
  registerReceiveFunc(recieve_data);
  
}



void loop(){

}


//date: 2020, 28, Dec.
//Author: Shinnosuke Fukai
//Purpose: To go to SUKIYA to eat gyudon
//
