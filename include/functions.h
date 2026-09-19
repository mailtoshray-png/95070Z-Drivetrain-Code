/* Helps prevent header files from being included multiple times*/
#pragma once

/*
 * Function declarations should be in header (.h) files
 * Specify return type, function name, and parameters
*/

extern const double GEAR_RATIO; //drivetrain gear ratio
extern const double WHEEL_DIAMETER; //drivetrain wheel diameter

double inchesToDegrees(double inches, double gearRatio, double wheelDiameter);
double degreesToInches(double deg, double gearRatio, double wheelDiameter);

void setDTPosition(double inches, double gearRatio, double wheelDiameter); //Good practice to use verb phrases as function names
void spinDT(double velocity);
void stopDT();
void spinRightDT(double velocity);
void spinLeftDT(double velocity);
void spinDTPosition(double velocity, double targetInches, double gearRatio, double wheelDiameter);
void turnForTime(double velocity, double time);
void runIntake();
void stopIntake();
void runoutake();

void spinDTPosition(double velocity, double targetInches);
void turnForTime(double velocity, double time);



