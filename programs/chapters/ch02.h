#include "mbed.h"
#include "crazyflie.h"

// Define all motors as PWM objects
PwmOut motor1(MOTOR1);
PwmOut motor2(MOTOR2);
PwmOut motor3(MOTOR3);
PwmOut motor4(MOTOR4);

float control_motor(float omega) {
    float result = a2*omega*omega;
    return result;
}

// Main program
int main()
{
    // Frequência de 500 Hz
    motor1.period(1.0/500.0);
    motor2.period(1.0/500.0);
    motor3.period(1.0/500.0);
    motor4.period(1.0/500.0);

    float w = 2000.0;

    for(int i = 0; i < 3; i++) {
        // Motor com w = 1000 rad/s
        motor1 = control_motor(w);
        motor2 = control_motor(w);
        motor3 = control_motor(w);
        motor4 = control_motor(w);
        wait(5);

        // Desliga Motoress
        motor1 = 0.0;
        motor2 = 0.0;
        motor3 = 0.0;
        motor4 = 0.0;
        wait(10);
    }

    
    // Blink green LEDs indicating end of program
    while(true)
    {
        
    }
}
