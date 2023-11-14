#include "mbed.h"
#include "crazyflie.h"

PwmOut motor_1(MOTOR1);
PwmOut motor_2(MOTOR2);
PwmOut motor_3(MOTOR3);
PwmOut motor_4(MOTOR4);


float omega_1;
float omega_2;
float omega_3;
float omega_4;


float control_motor(float omega) {
    float result = a2*omega*omega;
    return result;
}


void mixer(float f_t, float tau_phi, float tau_theta, float tau_psi) {
    //omega_1
    omega_1 = (1/(4*kl))*f_t - (1/(4*kl*l))*tau_phi - (1/(4*kl*l))*tau_theta - (1/(4*kd))*tau_psi;
    if (omega_1 < 0){
        omega_1 = 0.0;
    }
    else {
        omega_1 = sqrt(omega_1);
    }

    //omega_2
    omega_2 = (1/(4*kl))*f_t - (1/(4*kl*l))*tau_phi + (1/(4*kl*l))*tau_theta + (1/(4*kd))*tau_psi;
    if (omega_2 < 0){
        omega_2 = 0.0;
    }
    else {
        omega_2 = sqrt(omega_2);
    }

    //omega_3
    omega_3 = (1/(4*kl))*f_t + (1/(4*kl*l))*tau_phi + (1/(4*kl*l))*tau_theta - (1/(4*kd))*tau_psi;
    if (omega_3 < 0){
        omega_3 = 0.0;
    }
    else {
        omega_3 = sqrt(omega_3);
    }

    //omega_4
    omega_4 = (1/(4*kl))*f_t + (1/(4*kl*l))*tau_phi - (1/(4*kl*l))*tau_theta + (1/(4*kd))*tau_psi;
    if (omega_4 < 0){
        omega_4 = 0.0;
    }
    else {
        omega_4= sqrt(omega_4);
    }
}

void actuate(float f_t, float tau_phi, float tau_theta, float tau_psi) {
    mixer(f_t, tau_phi, tau_theta, tau_psi);
    motor_1 = control_motor(omega_1);
    motor_2 = control_motor(omega_2);
    motor_3 = control_motor(omega_3);
    motor_4 = control_motor(omega_4);
}

int main() {
    motor_1.period(1.0/500.0);
    motor_2.period(1.0/500.0);
    motor_3.period(1.0/500.0);
    motor_4.period(1.0/500.0);


    actuate(0, 0, 0, 0.001);
    wait(10);
    actuate(0, 0, 0, 0);

    while (true) {
    }
}

