#include "vex.h"
#include "intake.h"

using namespace vex;

intake::intake(vex::motor_group IntakeMotors) :
intakeMotors(IntakeMotors) {}

void intake::startIntake() {
    intakeMotors.spin(forward, 90, percent);
}

void intake::extake() {
    intakeMotors.spin(reverse, 90, percent);
}

void intake::stopIntake() {
    intakeMotors.stop(coast);
}