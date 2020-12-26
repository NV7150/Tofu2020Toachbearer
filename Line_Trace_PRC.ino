

void linetrace(){
    int right_forward;
    int right_back;
    int left_forward;
    int left_back;
    int th;
    int S[6];
    int judge[6]= [-3, -2, -1, 1, 2, 3];
    int sum = 0;

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
