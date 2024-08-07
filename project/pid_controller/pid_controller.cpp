#include "pid_controller.h"
#include <cmath>

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kpi, double Kii, double Kdi, double output_lim_maxi, double output_lim_mini) {
    Kp = Kpi;
    Ki = Kii;
    Kd = Kdi;
    output_lim_max = output_lim_maxi;
    output_lim_min = output_lim_mini;
    p_error = 0.0;
    i_error = 0.0;
    d_error = 0.0;
    delta_time = 1.0;  // Assume a default delta_time of 1 second
}

void PID::UpdateError(double cte) {
    d_error = (cte - p_error) / delta_time; // Differential error
    p_error = cte; // Proportional error
    i_error += cte * delta_time; // Integral error
}

double PID::TotalError() {
    double control = Kp * p_error + Ki * i_error + Kd * d_error;
    if (control > output_lim_max) control = output_lim_max;
    if (control < output_lim_min) control = output_lim_min;
    return control;
}

double PID::UpdateDeltaTime(double new_delta_time) {
    delta_time = new_delta_time;
    return delta_time;
}
