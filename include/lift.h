/* Helps prevent header files from being included multiple times*/
#pragma once
#include "vex.h"

class lift {

    public:
        lift(int Lift1Port, int Lift2Port, vex::triport::port pistonPort);

        vex::motor Lift1;
        vex::motor Lift2;
        vex::digital_out DoubleActingPiston;

        void liftArm(double degrees, double speed);
        void clamp();
};
