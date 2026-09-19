#pragma once
#include "vex.h"

class intake{

    public:
        intake(vex::motor_group IntakeMotors);

        vex::motor_group intakeMotors;

        void startIntake();
        void extake();
        void stopIntake();

};