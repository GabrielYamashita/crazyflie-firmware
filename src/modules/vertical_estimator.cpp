#include "vertical_estimator.h"

VerticalEstimator::VerticalEstimator() : range(E_SDA, E_SCL) {
    z = 0;
    w = 0;
}

void VerticalEstimator::init() {
    range.init();
}

void VerticalEstimator::predict(float f_t) {
    z = z + w*dt;

    if (z > 0.05) {
       w = w + ( f_t/m - g )*dt;
    }
}

void VerticalEstimator::correct(float phi, float theta) {
    range.read();

    if (range.d < 2.0) {
        float z_m = range.d * cos(phi) * cos(theta);
        w = w + l1_vert*dt_range*(z_m - z);
        z = z + l2_vert*dt_range*(z_m - z);
    }
}