#include "vex.h"
#include "robot-config.h"
#include "functions.h"
#include "drive.h"
#include "PID.h"

using namespace vex;

drive::drive(double WheelDiameter, double GearRatio, vex::motor_group driveLeft, vex::motor_group driveRight, int inertialPort) :
driveL(driveLeft), driveR(driveRight), Inertial(inertialPort) {
    wheelDiameter = WheelDiameter;
    gearRatio = GearRatio;
}

drive::drive(double WheelDiameter, double GearRatio, double startX, double startY, double startAngle, vex::motor_group driveLeft, vex::motor_group driveRight, int inertialPort) :
driveL(driveLeft), driveR(driveRight), Inertial(inertialPort) {
    wheelDiameter = WheelDiameter;
    gearRatio = GearRatio;
    xCoord = startX;
    yCoord = startY;
    Inertial.setHeading(startAngle, degrees);
}

void drive::driveStop() {
    driveL.stop(brake);
    driveR.stop(brake);
}

void drive::driveDistance(double distance) {
    driveDistance(distance, drive_tolerance, drive_kP, drive_kI, drive_kD);
}

void drive::driveDistance(double distance, double tolerance) {
    driveDistance(distance, tolerance, drive_kP, drive_kI, drive_kD);
}

void drive::driveDistance(double distance, double tolerance, double kP, double kI, double kD) {
    setDTPosition(0, gearRatio, wheelDiameter);
    double error = distance;

    PID drivePID(distance, kP, kI, kD, tolerance);

    double avgPos = degreesToInches((driveL.position(degrees) + driveR.position(degrees))/2, gearRatio, wheelDiameter);
    
    while(fabs(error) > tolerance) {
        avgPos = degreesToInches((driveL.position(degrees) + driveR.position(degrees))/2, gearRatio, wheelDiameter);
        error = distance - avgPos;

        double driveTotal = drivePID.calculateTotal(error);

        /*Brain.Screen.clearScreen();
        Brain.Screen.setCursor(1, 1);
        Brain.Screen.print(error);*/

        driveL.spin(forward, driveTotal, percent);
        driveR.spin(forward, driveTotal, percent);
        wait(drivePID.getUpdateTime(), msec);
    }

    driveStop();
    wait(50, msec);

    double xAxisAngle = (Inertial.heading() * -1) + 90;
    while(xAxisAngle < 360) xAxisAngle += 360;
    xAxisAngle *= M_PI / 180; //convert deg to rad

    xCoord += cos(xAxisAngle) * (distance - error);
    yCoord += sin(xAxisAngle) * (distance - error);

    printCoordInfo();
}

void drive::turnAngle(double angle) {
    turnAngle(angle, turn_tolerance, turn_kP, turn_kI, turn_kD);
}

void drive::turnAngle(double angle, double tolerance) {
    turnAngle(angle, tolerance, turn_kP, turn_kI, turn_kD);
}

void drive::turnAngle(double angle, double tolerance, double kP, double kI, double kD) {
    Inertial.setRotation(0, degrees);
    double error = angle;

    PID turnPID(angle, kP, kI, kD, tolerance);

    double measuredAngle = Inertial.rotation(degrees);

    while(fabs(error) > tolerance) {
        measuredAngle = Inertial.rotation(degrees);
        error = angle - measuredAngle;

        double turnTotal = turnPID.calculateTotal(error);

        driveL.spin(forward, turnTotal, percent);
        driveR.spin(reverse, turnTotal, percent);
        wait(turnPID.getUpdateTime(), msec);
    }

    driveStop();
    wait(50, msec);
}

void drive::turnHeading(double heading) {
    turnHeading(heading, 2, turn_kP, turn_kI, turn_kD);
}

void drive::turnHeading(double heading, double tolerance) {
    turnHeading(heading, tolerance, turn_kP, turn_kI, turn_kD);
}

void drive::turnHeading(double heading, double tolerance, double kP, double kI, double kD) {
    
    double error = heading - Inertial.heading();
    int clockwise;

    //Determine whether robot would be faster turning clockwise (1) or counterclockwise (-1)
    if((0 <= error && error < 180) || (-360 <= error && error < -180)) clockwise = 1;
    else clockwise = -1;

    while(error < -180) error += 360;
    PID turnPID(error, kP, kI, kD, tolerance);

    while(fabs(error) > tolerance) {
        //Calculate the error, negate it if turning in opposite direction
        error = (heading - Inertial.heading()) * clockwise;
        
        //Convert negative angle to equivalent positive angle
        while(error < -180) error += 360;

        double turnTotal = turnPID.calculateTotal(error);
        turnTotal *= clockwise;

        driveL.spin(forward, turnTotal, percent);
        driveR.spin(reverse, turnTotal, percent);
        wait(turnPID.getUpdateTime(), msec);
    }

    driveStop();
    wait(50, msec);
}

void drive::turnToPoint(double targetX, double targetY, double tolerance, double kP, double kI, double kD) {

    double neededAngle = (atan2(targetX-xCoord, targetY-yCoord)) * 180 / M_PI;
    if (neededAngle < 0) neededAngle += 360;

    //If already at correct angle, wait
    if(neededAngle == Inertial.heading()) {
        wait(10, msec);
    }
    //Otherwise, turn to correct angle
    else {
        turnHeading(neededAngle, tolerance, kP, kI, kD);
    }
}

void drive::forwardsToPoint(double targetX, double targetY) {
    forwardsToPoint(targetX, targetY, turn_tolerance, turn_kP, turn_kI, turn_kD, drive_tolerance, drive_kP, drive_kI, drive_kD);
}

void drive::forwardsToPoint(double targetX, double targetY, double turnTolerance, double turnkP, double turnkI, double turnkD, double driveTolerance, double drivekP, double drivekI, double drivekD) {
    turnToPoint(targetX, targetY, turnTolerance, turnkP, turnkI, turnkD);
    
    double targetDistance = sqrt(((xCoord - targetX) * (xCoord - targetX)) + ((yCoord - targetY) * (yCoord - targetY)));
    driveDistance(targetDistance, driveTolerance, drivekP, drivekI, drivekD);
}

void drive::backwardsToPoint(double targetX, double targetY) {
    backwardsToPoint(targetX, targetY, turn_tolerance, turn_kP, turn_kI, turn_kD, drive_tolerance, drive_kP, drive_kI, drive_kD);
}

void drive::backwardsToPoint(double targetX, double targetY, double turnTolerance, double turnkP, double turnkI, double turnkD, double driveTolerance, double drivekP, double drivekI, double drivekD) {
    //turn to correct angle
    double neededAngle = (atan2(targetX-xCoord, targetY-yCoord)) * 180 / M_PI;
    neededAngle += 180; //flipping angle by a half circle to make it backwardsz
    if (neededAngle < 0) neededAngle += 360;

    //If already at correct angle, wait
    if(neededAngle == Inertial.heading()) {
        wait(10, msec);
    }
    //Otherwise, turn to correct angle
    else {
        turnHeading(neededAngle, turnTolerance, turnkP, turnkI, turnkD);
    }
    //go backwards
    double targetDistance = sqrt(((xCoord - targetX) * (xCoord - targetX)) + ((yCoord - targetY) * (yCoord - targetY)));
    driveDistance(-targetDistance, driveTolerance, drivekP, drivekI, drivekD);
}

void drive::printCoordInfo() {
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("x: ");
    Brain.Screen.print(xCoord);
    Brain.Screen.print(", y: ");
    Brain.Screen.print(yCoord);

    Brain.Screen.setCursor(3, 1);
    Brain.Screen.print("heading: ");
    Brain.Screen.print(Inertial.heading());
}