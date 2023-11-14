#include "mbed.h"
#include "crazyflie.h"

// Define all LEDs as digital output objects

// Define all motors as PWM objects
PwmOut motor(MOTOR3);

// Main program
int main() {
    double PWM = 0.1;

    for(int i=0; i < 10; i++) {
        // Primeiro Teste
        motor = PWM;
        wait(10);

        motor = 0;
        wait(3);

        // Segundo Teste
        motor = PWM;
        wait(10);

        motor = 0;
        wait(3);

        // Terceiro Teste
        motor = PWM;
        wait(10);

        motor = 0;
        wait(3);

        // Aumenta PWM
        PWM += 0.1;
        wait(7);
    }
}
