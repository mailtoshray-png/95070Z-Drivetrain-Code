#include "lift.h"
#include "robot-config.h"
using namespace vex;


lift::lift(int Lift1Port, int Lift2Port, vex::triport::port pistonPort) :
Lift1(Lift1Port), Lift2(Lift2Port), DoubleActingPiston(pistonPort) {}

void lift::liftArm(double deg, double speed) {
    Lift1.spinToPosition(deg, degrees, speed);
    Lift2.spinToPosition(deg, degrees, speed);
}

void lift::clamp() {
    if (DoubleActingPiston.value() == 0) {
        DoubleActingPiston.set(true);
    }
    else if(DoubleActingPiston.value() == 1) {
        DoubleActingPiston.set(false);
    }
}