/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       katherinezeng                                             */
/*    Created:      5/27/2025, 10:30:19 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/


#include "vex.h"
#include "robot-config.h"
#include "PID.h"
#include "autons.h"
#include "auton-selector.h"
#include "lift.h"
#include "functions.h"
#include "drive.h"
#include "intake.h"

using namespace vex;

// A global instance of competition
competition Competition;


/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...


  vexcodeInit();
  autonSelector selector(1, 3);
  selector.chooseAuton();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  
  switch (autonSelector::getSelectedAuton()) {

    case 1:
      rightAuton();
      break;

    case 2:
      leftAuton();
      break;

    case 3:
      skillsAuton();
      break;

    default:
      Brain.Screen.print("No valid auton selected!");
      break;
  }


}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

bool inauton = false;

// Drivetrain functions in functions.cpp
// Declarations are kept here so this file can use the drivetrain helpers even
// when their header does not expose them.
void spinLeftDT(double power);
void spinRightDT(double power);


//Variables used in driver control
double intakeSpeed = 0;
bool buttonL1Held = false;
bool buttonL2Held = false;

bool buttonXHeld = false;

// User control function
void usercontrol(void) {

  bool slowModeActive = false;
  const double DRIVER_SPEED_FACTOR = 0.6; //can adjust your driver speed here
  while (true) {

    // ========== DRIVE CONTROL ========== //
    double fwd = Controller.Axis3.position(percent);
    double turn = Controller.Axis1.position(percent);

    double leftPower  = fwd + turn;
    double rightPower = fwd - turn;

    spinLeftDT(leftPower * DRIVER_SPEED_FACTOR);
    spinRightDT(rightPower * DRIVER_SPEED_FACTOR);

    // ========== Lift CONTROL ========== //
    // Hold down the R1 and R2 buttons to use the lift //
    if (Controller.ButtonR1.pressing()) {
      Lift1.spin(forward, 75, percent);
      Lift2.spin(forward, 75, percent);
    }
    else if (Controller.ButtonR2.pressing()) {
      Lift1.spin(reverse, 75, percent);
      Lift2.spin(reverse, 75, percent);
    } 
    else {
      Lift1.stop(hold);
      Lift2.stop(hold);
    }

    // ========== INTAKE ========== //
    // Tap the L1 and L2 buttons to set the intake speed. Tap the same button again to stop //
    if (Controller.ButtonL1.pressing() && intakeSpeed != 100 && !buttonL1Held) {
      intakeMotor.spin(forward, 100, percent);
      intakeSpeed = 100;
      buttonL1Held = true;
    } 
    else if(Controller.ButtonL1.pressing() && intakeSpeed == 100 && !buttonL1Held) {
      intakeMotor.stop(coast);
      intakeSpeed = 0;
      buttonL1Held = true;
    }
    else if (Controller.ButtonL2.pressing() && intakeSpeed != -100 && !buttonL2Held) {
      intakeMotor.spin(reverse, 100, percent);
      intakeSpeed = -100;
      buttonL2Held = true;
    } 
    else if (Controller.ButtonL2.pressing() && intakeSpeed == -100 && !buttonL2Held){
      intakeMotor.stop(coast);
      intakeSpeed = 0;
      buttonL2Held = true;
    }

    if(!Controller.ButtonL1.pressing()) {
      buttonL1Held = false;
    }
    if(!Controller.ButtonL2.pressing()) {
      buttonL2Held = false;
    }
 
    // ========== COLOR SENSOR ========== //
    color detectedColor = OpticalSensor.color();

    /*if (detectedColor == color::blue) {
      Brain.Screen.printAt(50, 50, "Blue Detected!");
    } 
    
    else if (detectedColor == color::red) {
      Brain.Screen.printAt(50, 50, "Red Detected!");
    } 

    else {
      Brain.Screen.printAt(50, 50, "No specific color detected.");
    }*/

    double hue = OpticalSensor.hue();
    double brightness = OpticalSensor.brightness();
    Brain.Screen.printAt(50, 70, "Hue: %.2f", hue);
    Brain.Screen.printAt(50, 90, "Brightness: %.2f", brightness);
    Brain.Screen.clearScreen();

    // ========== PNEUMATICS ========== //
    // Use the X button to toggle the piston position //
    if(Controller.ButtonX.pressing() && !buttonXHeld) {
      DoubleActingPiston.set(!DoubleActingPiston.value());
      buttonXHeld = true;
    }
    else if(!Controller.ButtonX.pressing()) {
      buttonXHeld = false;
    }

    // ========== LOOP DELAY ========== //
    wait(20, msec);
  }
}



  

// Entry point
int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  
  pre_auton();
  //Competition.test_auton();
  //Competition.test_driver();


  while (true) {
    wait(100, msec);
  }
}