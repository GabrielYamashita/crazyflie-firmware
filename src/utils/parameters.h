
#ifndef parameters_h
#define parameters_h

#include <cmath>

// Physical constants
const float pi = 3.1416;
const float g = 9.81;       // m/s^2



// Time Diff
const float dt = 0.002;
const float dt_range = 0.05;



// Quadcopter dimensions
const float m = 30.0e-3;    // kg
const float I_xx = 16.0e-6; // kg.m^2
const float I_yy = 16.0e-6; // kg.m^2
const float I_zz = 29.0e-6; // kg.m^2
const float l = 33.0e-3;    // m



// Mixer
const float a2 = 1.4e-7;
const float kl = 1.696e-8;
const float kd = 1.012e-10;

// --> Phi
const float Ts_phi = 0.3;
const float OS_phi = 0.005;
const float z_phi = abs( log(OS_phi))/sqrt( pow(log(OS_phi), 2) + pow(pi, 2) );
const float Wn_phi = 4.0/(z_phi*Ts_phi);
const float kp_phi = pow(Wn_phi, 2);
const float kd_phi = 2.0*z_phi*Wn_phi;

// --> Theta
const float kp_theta = kp_phi;
const float kd_theta = kd_phi;

// --> Psi
const float Ts_psi = 0.6;
const float OS_psi = 0.005;
const float z_psi = abs( log(OS_psi))/sqrt( pow(log(OS_psi), 2) + pow(pi, 2) );
const float Wn_psi = 4.0/(z_psi*Ts_psi);
const float kp_psi = pow(Wn_psi, 2);
const float kd_psi = 2.0*z_psi*Wn_psi;



// Attitude Estimator
const float wc = 1.0;
const float alfa = (wc*dt)/(1.0 + wc*dt);

// Attitude Controller
// sem constantes



// Vertical Estimator
const float wc_range = 10;
const float z_range = sqrt(2)/2;
const float l1_vert = pow(wc_range, 2);
const float l2_vert = 2 * z_range * wc_range;

// Vertical Controller
const float kp_vert = 5.8567;
const float kd_vert = 3.4225;



// Horizontal Estimator
const float gamma_h = 42.0 * pi/180.0;
const float w_sensor_h = 420.0;

const float sigma_h = (2.0 * tan(gamma_h/2.0))/(w_sensor_h * dt);
const float l_h = 50.0;

// Horizontal Controller
const float ts_h = 2.0;
const float os_h = 0.005;

const float z_h = abs( log(os_h) )/sqrt( pow(log(os_h), 2) + pow(pi, 2) );
const float wn_h = 4/(z_h * ts_h);

const float kp_h = pow(wn_h, 2);
const float kd_h = 2*z_h*wn_h;


#endif