#include "functions.h"
#include "robot-config.h"
#include "vex.h"

using namespace vex;

double inchesToDegrees(double inches, double gearRatio, double wheelDiameter) {
    return ((inches / (M_PI * wheelDiameter)) * 360 * gearRatio);
}

double degreesToInches(double deg, double gearRatio, double wheelDiameter) {
    return ((deg / (360 * gearRatio)) * (M_PI * wheelDiameter));
}

void setDTPosition(double inches, double gearRatio, double wheelDiameer) {

    double deg = inchesToDegrees(inches, gearRatio, wheelDiameer);

    leftDrive.setPosition(deg, degrees);
    rightDrive.setPosition(deg, degrees);
}

void stopDT() {
    leftDrive.stop(brake);
    rightDrive.stop(brake);
}


void spinRightDT(double velocity) {
    rightDrive.spin(forward, velocity, percent);
}

void spinLeftDT(double velocity) {
    leftDrive.spin(forward, velocity, percent);
}

void spinDT(double velocity) {
    spinRightDT(velocity);
    spinLeftDT(velocity);
}

void spinDTPosition(double rpmVelocity, double targetInches, double gearRatio, double wheelDiameter){

    setDTPosition(0, gearRatio, wheelDiameter);
    double targetDegrees = inchesToDegrees(targetInches, gearRatio, wheelDiameter);

    leftDrive.spinToPosition(targetDegrees, degrees, rpmVelocity, rpm, false);
    rightDrive.spinToPosition(targetDegrees, degrees, rpmVelocity, rpm, true);
}

void turnForTime(double velocity, double time) {
    spinRightDT(-velocity);
    spinLeftDT(velocity);
    wait(time, msec);
    stopDT();
} 

void runIntake(){
    intakeMotor.spin(forward, 100, percent);
}

void runOutake(){
    intakeMotor.spin(reverse, 100, percent);
}

void stopIntake(){
    intakeMotor.stop(coast);
}