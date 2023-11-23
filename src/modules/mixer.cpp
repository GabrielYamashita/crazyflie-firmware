
#include "mixer.h"
#include "crazyflie.h"

// Inicialização da Classe
Mixer::Mixer() : motor_1(MOTOR1), motor_2(MOTOR2), motor_3(MOTOR3), motor_4(MOTOR4), ledRR(LED_RED_R, !false), ledRL(LED_RED_L, !false), ledGR(LED_GREEN_R, !false), ledGL(LED_GREEN_L, !false) {
    motor_1.period(1.0/500.0);
    motor_2.period(1.0/500.0);
    motor_3.period(1.0/500.0);
    motor_4.period(1.0/500.0);

    motor_1 = 0.0;
    motor_2 = 0.0;
    motor_3 = 0.0;
    motor_4 = 0.0;
}

// Ativa os Motores
void Mixer::actuate(float ft, float tauPhi, float tauTheta, float tauPsi) {
    if (armed) {
        mixer(ft, tauPhi, tauTheta, tauPsi);
        motor_1 = controlMotor(omega_1);
        motor_2 = controlMotor(omega_2);
        motor_3 = controlMotor(omega_3);
        motor_4 = controlMotor(omega_4);
    }
    else {
        notArmed();
        
        while(true);
    }
}

// Ativa os Motores, com um Timer
void Mixer::actuate(float ft, float tauPhi, float tauTheta, float tauPsi, int time) {
    if (armed) {
        mixer(ft, tauPhi, tauTheta, tauPsi);
        motor_1 = controlMotor(omega_1);
        motor_2 = controlMotor(omega_2);
        motor_3 = controlMotor(omega_3);
        motor_4 = controlMotor(omega_4);
        wait(time);
    }
    else {
        notArmed();
        while(true);
    }
}

// Aviso do Drone de não Armado
void Mixer::notArmed() {
    ledGL = !ledGL;
    ledRR = !ledRR;
    wait(0.5);
    ledGL = !ledGL;
    ledRR = !ledRR;

    ledGR = !ledGR;
    ledRL = !ledRL;
    wait(0.5);
    ledGR = !ledGR;
    ledRL = !ledRL;

    ledGL = !ledGL;
    ledRR = !ledRR;
    wait(0.5);
    ledGL = !ledGL;
    ledRR = !ledRR;

    ledGR = !ledGR;
    ledRL = !ledRL;
    wait(0.5);
    ledGR = !ledGR;
    ledRL = !ledRL;

    ledGL = !ledGL;
    ledRR = !ledRR;
    wait(0.5);
    ledGL = !ledGL;
    ledRR = !ledRR;

    ledGR = !ledGR;
    ledRL = !ledRL;
    wait(0.5);
    ledGR = !ledGR;
    ledRL = !ledRL;
}

// Arma o Drone para Voo
void Mixer::arm() {
    // Sequência de LED, para ligar (verde)
    ledGL=! ledGL;
    ledGR=! ledGR;
    wait(0.3);
    ledGL=! ledGL;
    ledGR=! ledGR;
    wait(0.3);

    ledGL=! ledGL;
    ledGR=! ledGR;
    wait(0.3);
    ledGL=! ledGL;
    ledGR=! ledGR;
    wait(0.3);

    ledGL=! ledGL;
    ledGR=! ledGR;
    wait(1.8);
    
    ledGL = !ledGL;
    ledGR = !ledGR;

    armed = true; // arma o drone
}

// Desarma o Drone para Voo
void Mixer::disarm() {
    actuate(0, 0, 0, 0); // Desativa os Motores
    armed = false; // desarma o drone

    // Sequência de LED, para desligar (vermelho)
    ledRL=! ledRL;
    ledRR=! ledRR;
    wait(0.3);
    ledRL=! ledRL;
    ledRR=! ledRR;
    wait(0.3);

    ledRL=! ledRL;
    ledRR=! ledRR;
    wait(0.3);
    ledRL=! ledRL;
    ledRR=! ledRR;
    wait(0.3);

    ledRL=! ledRL;
    ledRR=! ledRR;
    wait(1.8);
    
    ledRL = !ledRL;
    ledRR = !ledRR;

}

// Calcula Saída dos Ômegas
void Mixer::mixer(float ft, float tauPhi, float tauTheta, float tauPsi) {
    omega_1 = (1.0/(4.0*kl))*ft - (1.0/(4.0*kl*l))*tauPhi - (1.0/(4.0*kl*l))*tauTheta - (1.0/(4.0*kd))*tauPsi;
    omega_2 = (1.0/(4.0*kl))*ft - (1.0/(4.0*kl*l))*tauPhi + (1.0/(4.0*kl*l))*tauTheta + (1.0/(4.0*kd))*tauPsi;
    omega_3 = (1.0/(4.0*kl))*ft + (1.0/(4.0*kl*l))*tauPhi + (1.0/(4.0*kl*l))*tauTheta - (1.0/(4.0*kd))*tauPsi;
    omega_4 = (1.0/(4.0*kl))*ft + (1.0/(4.0*kl*l))*tauPhi - (1.0/(4.0*kl*l))*tauTheta + (1.0/(4.0*kd))*tauPsi;


    // omega_1
    if (omega_1 < 0.0) {
        omega_1 = 0.0;
    }
    else {
        omega_1 = sqrt(omega_1);
    }

    // omega_2
    if (omega_2 < 0.0){
        omega_2 = 0.0;
    }
    else {
        omega_2 = sqrt(omega_2);
    }

    //omega_3
    if (omega_3 < 0.0){
        omega_3 = 0.0;
    }
    else {
        omega_3 = sqrt(omega_3);
    }

    //omega_4
    if (omega_4 < 0.0){
        omega_4 = 0.0;
    }
    else {
        omega_4 = sqrt(omega_4);
    }
}

// Calcula Rotação do Motor, a patir do Ômega
float Mixer::controlMotor(float omega) {
    float result = a2 * omega * omega;
    return result;
}