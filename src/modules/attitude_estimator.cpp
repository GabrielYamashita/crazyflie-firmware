
#include "attitude_estimator.h"
#include <cmath>

// Constructor
AttitudeEstimator::AttitudeEstimator() : imu(IMU_SDA, IMU_SCL) {
    phi, theta, psi = 0; // euler angles [rad]
    p, q, r = 0; // angular velocities [rad/s]
    p_bias, q_bias, r_bias = 0;
}

// Initialize Class
void AttitudeEstimator::init() {
    imu.init();

    float sum_p, sum_q, sum_r;
    for (int i = 0; i < 500; i++) {
        imu.read();

        sum_p += imu.gx;
        sum_q += imu.gy;
        sum_r += imu.gz;

        wait(dt);
    }

    p_bias = sum_p/500.0;
    q_bias = sum_q/500.0;
    r_bias = sum_r/500.0;
}

// estimate euler angles [rad] and angular velocity [rad/s]
void AttitudeEstimator::estimate() {
    // Leitura do Sensor
    imu.read();

    // Leitura com Erro Sistemático
    p = imu.gx - p_bias;
    q = imu.gy - q_bias;
    r = imu.gz - r_bias;


    // 
    float phi_g = phi + (p + sin(phi)*tan(theta)*q + cos(phi)*tan(theta)*r)*dt;
    float phi_a = atan2(-imu.ay, -imu.az);

    float theta_g = theta + (cos(phi)*q - sin(phi)*r)*dt;
    float theta_a = atan2(imu.ax, -((imu.az > 0) - (imu.az < 0)) * sqrt(pow(imu.ay, 2) + pow(imu.az, 2)));

    float psi_g = psi + (sin(phi) * (1.0/cos(theta)) * q + cos(phi) * (1.0/cos(theta)) * r)*dt;

    // Estimação de Altitude
    phi = (1.0-alfa) * phi_g + alfa*phi_a;
    theta = (1.0-alfa) * theta_g + alfa*theta_a;
    psi = psi_g;
}

