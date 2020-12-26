#include "Pins.h"
using namespace Pins;

int area;

void linetrace(){

    int right_forward;
    int right_back;
    int left_forward;
    int left_back;
    int th;
    int S[6];
    int judge[6]= [-3, -2, -1, 1, 2, 3];
    int sum = 0;

    for (int i = 0; p < 6; p ++){
      S[p] = analogRead(PIN_SENSORS[i]);
    }
    for (int i = 0; i < 6; i ++){
        if (S[i] < th){
            judge[i] = 0;
        }
    }
    for (int k = 0; k < 6; k ++){
      sum += judge[k];
    }
    if (abs(sum) < 4){
      if (sum > 0){
        analogWrite(left_forward, 0);
        analogWrite(right_forward, f * sum);
      }else if{
        analogWrite(right_forward, 0);
        analogWrite(left_forward, f * abs(sum));
      }else{
        analogWrite(right_forward, f);
        analogWrite(left_forward, f);
    }
    delay(10);
}
