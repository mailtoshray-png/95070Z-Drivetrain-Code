#include "robot-config.h"
#include "vex.h"
#include "PID.h"
#include "lift.h"
#include "functions.h"
#include "autons.h"
#include <iostream>

using namespace vex;

void rightAuton() {

  Controller.Screen.clearLine(3);
  Controller.Screen.setCursor(3, 1);
  Controller.Screen.print("start auton");

  drive Chassis(3.25, 3.0/5, 0, 0, 0, leftDrive, rightDrive, PORT1);
  intake intake (intakeMotors);

  //Chassis.driveDistance(24, 0.3, 2.5, 0, 0);
  //std::cout<<"drive pid done"<<std::endl;

  Chassis.turnAngle(90, 2, 0.5, 0, 0);
  std::cout<<"turn pid done"<<std::endl;  
}

void leftAuton() {
  
  //Use functions to create an auton for the left side of the field
drive Chassis(3.25, 3.0/5, 0, 0, 0, leftDrive, rightDrive, PORT1);
}

void skillsAuton() {
  
  //Use functions to create a programming skills routine
  
}