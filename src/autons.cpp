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

  drive Chassis(3.25, 3.0/5, 0, 0, 0, leftDrive, rightDrive, PORT7);
  intake intake (intakeMotors);

  //Remember to make all distances negative forwards and positive for backwards, since the motors are reversed
  Chassis.driveDistance(-24, 0.3, 2.5, 0, 0);

  /*while(true) {
    std::cout<<InertialSensor.heading()<<std::endl;
    wait(10, msec);
  }*/

  //Chassis.turnAngle(90, 1, 0.7, 0, 0.05);

}

void leftAuton() {
  
  //Use functions to create an auton for the left side of the field
drive Chassis(3.25, 3.0/5, 0, 0, 0, leftDrive, rightDrive, PORT1);
}

void skillsAuton() {
  
  //Use functions to create a programming skills routine
  
}