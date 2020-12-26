//
// Created by 後藤大介 on 2019/11/15.
//

#ifndef LINETRACESTS_PIN_H
#define LINETRACESTS_PIN_H

#include <Arduino.h>
namespace Pins {

    //PINのモード
    enum PinOption {
        //デジタル入力
        DIG_IN,
        //デジタル出力
        DIG_OUT,
        //デジタル入力（プルアップ）
        DIG_IN_PULLUP,
        //アナログ入出力
        ANALOG
    };

    //Arduinoのいずれかのピンを示すクラス
    class Pin {
    private:
        //ピン番号
        uint8_t pinNumber;
        //ピンのモード
        PinOption pinOption;

    public:
        //コンストラクタ
        Pin(uint8_t pinNumber, PinOption pinOption);
        //ピン番号を取得
        uint8_t getPinNumber();
    };
}



#endif //LINETRACESTS_PIN_H
