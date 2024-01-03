/**********************************************
 * Self-Driving Car Nano-degree - Udacity
 *  Created on: December 11, 2020
 *      Author: Mathilde Badoual
 **********************************************/

#include "pid_controller.h"
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd, double output_lim_max, double output_lim_min) {
   /**
   * TODO: Initialize PID coefficients and errors, if needed
   **/
   kP = Kp;
   kI = Ki;
   kD = Kd;
   output_limMax = output_lim_max;
   output_limMin = output_lim_min;
   p_error = 0.0;
   i_error = 0.0;
   d_error = 0.0;
   delta_time = 0;
}

void PID::UpdateError(double cte) {
  /**
  * TODO: Update PID errors based on cte.
  **/
   // Calculate the differential error (error derivative)
   if (delta_time > 0) {
     d_error = (cte - p_error) / delta_time;
   } else {
     d_error = 0.0;
   }

   // Update the integral error
   i_error += cte * delta_time;

   // Update the proportional error
   p_error = cte;

}

double PID::TotalError() {
   /**
   * TODO: Calculate and return the total error
    * The code should return a value in the interval [output_lim_mini, output_lim_maxi]
   */
    double totalError;
    totalError = kP * p_error + kI * i_error + kD * d_error;
    if (totalError < output_limMin) {
      totalError = output_limMin;
    } else if (totalError > output_limMax) {
      totalError = output_limMax;
    }
    return totalError;
}

double PID::UpdateDeltaTime(double new_delta_time) {
   /**
   * TODO: Update the delta time with new value
   */
   delta_time = new_delta_time;
   return delta_time;
}
