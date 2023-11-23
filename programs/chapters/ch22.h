
#include "mbed.h"
#include "crazyflie.h"
#include "USBSerial.h"

USBSerial serial;

AttitudeEstimator att_est;
VerticalEstimator ver_est;
HorizontalEstimator hor_est;

Ticker tic, tic_range;
bool flag, flag_range;

void callback() { flag = true; }
void callback_range() { flag_range = true; }

int main() {
    att_est.init();
    ver_est.init();
    hor_est.init();

    tic.attach(&callback, dt);
    tic_range.attach(&callback_range, dt);

    while (true) {
        if (flag) {
            flag = false;

            att_est.estimate();
            ver_est.predict(0.0);

            if (flag_range) {
                flag_range = false;
                ver_est.correct(att_est.phi, att_est.theta);

                serial.printf(
                    "x [m]: %6.2f | y [m]: %6.2f | u [m/s]: %6.2f | v [m/s]: %6.2f\n", 
                    hor_est.x, hor_est.y, hor_est.u, hor_est.v
                );
            }
            hor_est.predict(0.0, 0.0);

            if (ver_est.z >= 0.05) {
                hor_est.correct(att_est.phi, att_est.theta, att_est.p, att_est.q, ver_est.z);
            }
        }
    }
}