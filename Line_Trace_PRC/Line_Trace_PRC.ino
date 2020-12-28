int right_forward;
int right_back;
int left_forward;
int left_back;
int th;
int a, b, c, d, e, f, 
int S1;
int S2;
int S3;
int S4;
int S5;
int S6;
int S[6] = [S1, S2, 3, S4, S5, S6]
int judge[6]
int sum = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  judge[6] = [-3, -2, -1, 1, 2, 3]
  for (int i = 0; i < 6; i ++){
    if (S[i] < th){
      judge[i] = 0;
    }
  for (int k = 0; k < 6; k ++){
    sum += judge[k];
  }
  if (sum > 0){
    analogWrite(right_forward, f * sum);
  }else{
    analogWrite(left_forward, f * -1 * sum);
  }
  }
  
}
