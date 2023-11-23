
#ifndef attitude_estimator_h
#define attitude_estimator_h

#include "mbed.h"
#include "crazyflie.h"

class AttitudeEstimator {
    public:
        AttitudeEstimator(); // constructor
        void init(); // initialize class
        void estimate(); // estimate euler angles [rad] and angular velocity [rad/s]

        float phi, theta, psi; // euler angles [rad]
        float p, q, r; // angular velocities [rad/s]
        float p_bias, q_bias, r_bias;

    private:
        BMI088 imu; // IMU sensor Object
};

#endif