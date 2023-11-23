
#include "horizontal_controller.h"

HorizontalController::HorizontalController() {
    theta_r = 0;
    phi_r = 0;
}

void HorizontalController::control(float x_r, float y_r, float x, float y, float u, float v) {
    theta_r = (1.0/g) * control_siso(x_r, x, u, kp_h, kd_h);
    phi_r = - (1.0/g) * control_siso(y_r, y, v, kp_h, kd_h);
}

float HorizontalController::control_siso(float pos_r, float pos, float vel, float kp, float kd) {
    float vel_r = 0;
    return kp*(pos_r - pos) + kd*(vel_r - vel);
}