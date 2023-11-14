#include "mbed.h"
#include "crazyflie.h"

Mixer mixer;

int main() {
    mixer.arm();

    mixer.actuate(0.2, 0, 0, 0, 2);

    mixer.disarm();

    while (true) {
    }
} 