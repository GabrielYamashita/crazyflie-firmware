#include "vertical_controller.h"

VerticalController::VerticalController() {
    f_t = 0;
}

void VerticalController::control(float z_r, float z, float w) {
    f_t = m*(g + control_siso(z_r, z, w, kp_vert, kd_vert));
}

float VerticalController::control_siso(float pos_r, float pos, float vel, float kp, float kd) {
    float vel_r = 0;
    return kp_vert*(pos_r-pos) + kd_vert*(vel_r-vel);
}