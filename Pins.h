//
// Created by NV7150 on 2020/12/23.
//

#ifndef TOFU2020TORCHBEARER_PINS_H
#define TOFU2020TORCHBEARER_PINS_H

#include "Pin.h"
namespace Pins{
    const Pin* MOTOR_R = new Pin(1, ANALOG);
    const Pin** SENSORS = [new Pin(2, ANALOG)];
}

#endif //TOFU2020TORCHBEARER_PINS_H
