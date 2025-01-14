#ifndef mixer_h
#define mixer_h

#include "mbed.h"
#include "crazyflie.h"

class Mixer {
    public:
        Mixer();
        void actuate(float ft, float tauPhi, float tauTheta, float tauPsi);
        void actuate(float ft, float tauPhi, float tauTheta, float tauPsi, int time);
        void arm();
        void disarm();

    private:
        bool armed;

        PwmOut motor_1, motor_2, motor_3, motor_4;
        DigitalOut ledRR, ledRL, ledGR, ledGL;

        float omega_1, omega_2, omega_3, omega_4;

        void mixer(float ft, float tauPhi, float tauTheta, float tauPsi);
        float controlMotor(float omega);
        
        void notArmed();
};

#endif