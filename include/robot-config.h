/* Helps prevent header files from being included multiple times*/
#pragma once

#include "vex.h" //use the contents of vex.h in this file

//extern keyword lets the compiler know that the variable is defined elsewhere 
//in this case, the variable definitions are in robot-config.cpp
extern vex::brain Brain;
extern vex::controller Controller;
extern vex::competition Competition;

extern vex::motor LB;
extern vex::motor LM;
extern vex::motor LF;
extern vex::motor RB;
extern vex::motor RM;
extern vex::motor RF;

extern vex::motor_group leftDrive; //all motors on left side of drivetrain
extern vex::motor_group rightDrive; //all motors on right side of drivetrain

extern vex::motor intakeMotor;
extern vex::motor middleIntakeMotor;
extern vex::motor bottomIntakeMotor;

extern vex::motor_group intakeMotors;

//extern vex::drivetrain Drivetrain;

extern vex::motor Lift1;
extern vex::motor Lift2;

extern vex::inertial InertialSensor;
extern vex::optical OpticalSensor;

extern vex::digital_out DoubleActingPiston;
extern vex::digital_out SingleActingPiston;

void vexcodeInit();




