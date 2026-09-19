#pragma once
#include "vex.h"

class drive {

    private:
        double wheelDiameter;
        double gearRatio;

        //default tuning constants for straight line driving
        double drive_kP = 2;
        double drive_kI = 0.05;
        double drive_kD = 0.2;
        double drive_tolerance = 1;

        //default tuning constants for turning
        double turn_kP = 0.5;
        double turn_kI = 0.01;
        double turn_kD = 0.05;
        double turn_tolerance = 2;

        double xCoord;
        double yCoord;
    
    public:
        vex::motor_group driveL;
        vex::motor_group driveR;
        vex::inertial Inertial;

        drive(double WheelDiameter, double GearRatio, vex::motor_group DriveL, vex::motor_group DriveR, int inertialPort);

        //Start angle should be given relative to the vertical side of the field, increasing clockwise (same as Inertial heading)
        drive(double WheelDiameter, double GearRatio, double startX, double startY, double startAngle, vex::motor_group DriveL, vex::motor_group DriveR, int inertialPort);

        void driveStop();

        void driveDistance(double distance);
        void driveDistance(double distance, double tolerance);
        void driveDistance(double distance, double tolerance, double kP, double kI, double kD);

        void turnAngle(double angle);
        void turnAngle(double angle, double tolerance);
        void turnAngle(double angle, double tolerance, double kP, double kI, double kD);

        void turnHeading(double heading);
        void turnHeading(double heading, double tolerance);
        void turnHeading(double heading, double tolerance, double kP, double kI, double kD);

        void turnToPoint(double targetX, double targetY, double tolerance, double kP, double kI, double kD);
        
        void forwardsToPoint(double targetX, double targetY);
        void forwardsToPoint(double targetX, double targetY, double turnTolerance, double turnkP, double turnkI, double turnkD, double driveTolerance, double drivekP, double drivekI, double drivekD);

        void backwardsToPoint(double targetX, double targetY);
        void backwardsToPoint(double targetX, double targetY, double turnTolerance, double turnkP, double turnkI, double turnkD, double driveTolerance, double drivekP, double drivekI, double drivekD);

        void printCoordInfo();
};