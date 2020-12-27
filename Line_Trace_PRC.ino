#include "Pins.h"
using nameSensor_pinpace PinSensor_pin;
int area;
int msg = "line_trace";
int black = "";
int white = "";
const int f;
const int straight_zone[6] = [0, 2, 4, 6, 12, 14]
const int performance_zone[4] = [3, 5, 9, 13]

void all_black(){
  for (i = 0; i < 6; i ++){
    if (Sensor_color[i] == "B"){
      int msg = "change";
    }else{
      int msg = "";
      break;
    }
  }if (msg == "change"){
    area ++;
  }
}

void half_black(){
  for (i = 3; i < 6; i ++){
    if (Sensor_color[i] == "B"){
      int msg = "change";
    }else{
      int msg = "";
      break;
    }
  }if (msg == "change"){
    area ++;
  }
}

void color(col, list){
  if (col == "white"){
   white = "True"
    for (i = 3; i < sizeof list / sizeof list[0] + 1; i ++){
      if (Sensor_color[list[i]] == "W"){
        white = "";
        break;
      }
    }if (white == "True"){
      return 1;
    }else{
      return 0;
    }
} else if (col == "black"){
   black = "True"
    for (i = 3; i < sizeof list / sizeof list[0] + 1; i ++){
      if (Sensor_color[list[i]] == "W"){
        black = "";
        break;
      }
    }if (black == "True"){
      return 1;
    }else{
      return 0;
    }
}

void change_area(){
  global area;
  if (area == 0){
    all_black();
  }else if (area == 2){
    all_black();
  }else if (area == 4){
    all_black();
  }else if (area == 6){
    half_black();
  }else if (area == 12){
    all_black();
  }else if (area == 14){
    all_black();
  }
}

void include(name, list){
  int include = 0;
  for (i = 0; i < sizeof list / sizeof list[0] + 1; i++ ){
    if (list == name){
      include = "True";
      break;
    }
  }
  if (include = "True"){
    return 1
  }else{
    return 0
  }
}

void linetrace(){
    int right_forward;
    int right_back;
    int left_forward;
    int left_back;
    int th; //低いと黒、高いと白
    int Sensor_pin[6];
    int Sensor_color[6] = ["W", "W", "W", "W", "W", "W"];
    int Sensor_value[6]= [-3, -2, -1, 1, 2, 3];
    int sum = 0;

    for (int p = 0; p < 6; p ++){
      Sensor_pin[p] = analogRead(PIN_Sensor_pinENSensor_pinORSensor_pin[i]);
      }

    for (int i = 0; i < 6; i ++){
      if (Sensor_pin[i] < th){
          Sensor_color[i] = "B";
     }else{
      Sensor_value = 0;
     }
   }
  if  (include(area, straight_zone) == 1){
      if (sum > 0){
        analogWrite(left_forward, 0);
        analogWrite(right_forward, f * sum);
      }else if(Sensor_pinum < 0){
        analogWrite(right_forward, 0);
        analogWrite(left_forward, f * abSensor_pin(Sensor_pinum));
      }else{
        analogWrite(right_forward, f);
        analogWrite(left_forward, f);
    }
  }else if (include(area, performance_zone) == 1){
    if (msg == "line_trace"){
      msg = "performance"
    }else{
      analogWrite(right_forward, f);
      analogWrite(left_forward, f);
    }area ++;
     msg = "line_trace"
  }else  if (area == 7 || area == 11 || (area == 9 && msg == "line_trace")){
    if(!(color("white", [0, 1, 4, 5]))){
      analogWrite(right_forward, 0);
      analogWrite(right_back, 0);
      analogWrite(left_forward, 0);
      analogWrite(left_back, 0);
      analogWrite(left_forward, f);
      analogWrite(right_back, f);
    }else{
      analogWrite(right_forward, 0);
      analogWrite(right_back, 0);
      analogWrite(left_forward, 0);
      analogWrite(left_back, 0);
      area ++;
     }
   }else if
delay(100);
}
