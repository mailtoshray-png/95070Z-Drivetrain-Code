#include "autons.h"
#include "robot-config.h"
#include "vex.h"
#include "functions.h"
#include "PID.h"

using namespace vex;


PID::PID(double startError, double kp, double ki, double kd) {
  error = startError;
  kP = kp;
  kI = ki;
  kD = kd;
}

PID::PID(double startError, double kp, double ki, double kd, double Tolerance) {
  error = startError;
  kP = kp;
  kI = ki;
  kD = kd;
  tolerance = Tolerance;
}

PID::PID(double startError, double kp, double ki, double kd, double Tolerance, double WindupTheshold, double UpdateTime) {
  error = startError;
  kP = kp;
  kI = ki;
  kD = kd;
  tolerance = Tolerance;
  windupThreshold = WindupTheshold;
  updateTime = UpdateTime;
}

double PID::calculateTotal(double currentError) {
  error = currentError;

  if(fabs(error) < windupThreshold) {
    integral += error * ((double)updateTime / 1000);
  }

  derivative = (error - prevError) / ((double)updateTime / 1000);
  prevError = error;

  total = error * kP + integral * kI + derivative * kD;
  return total;

}

double PID::getUpdateTime() {
  return updateTime;
}