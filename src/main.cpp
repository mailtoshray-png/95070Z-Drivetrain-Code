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
bool buttonR1Held = false;
bool buttonR2Held = false;
bool buttonHeld = false;
bool buttonXHeld = false;
bool clawIsOpen = false;

// User control function
void usercontrol(void) {

  while (true) {

    // ========== DRIVE CONTROL ========== //
  double verticalPower = Controller.Axis3.position();// Controls movement forwards-backwards.
  double horizontalPower = Controller.Axis1.position();// Controls movements turning left-right.

  // 0.7 is to slow down the drivetrain.
  double right = ((verticalPower) - (horizontalPower)) * 0.7;
  double left = ((verticalPower) + (horizontalPower)) * 0.7;

  if (fabs(verticalPower) < 10 && fabs(horizontalPower) < 10) { //10 is for the dead zone
    leftDrive.stop(coast);
    rightDrive.stop(coast);
  }
  else {
    leftDrive.spin(forward, left, percent);
    rightDrive.spin(forward, right, percent);
  }

    // ========== Lift CONTROL ========== //
    // Hold down the L1 and L2 buttons to use the lift
    if (Controller.ButtonL1.pressing()) {
      Lift1.spin(forward, 75, percent);
      Lift2.spin(forward, 75, percent);
    }
    else if (Controller.ButtonL2.pressing()) {
      Lift1.spin(reverse, 75, percent);
      Lift2.spin(reverse, 75, percent);
    } 
    else {
      Lift1.stop(hold);
      Lift2.stop(hold);
    }

    // ========== INTAKE ========== //
    // Tap the R1 and R2 buttons to set the intake speed. Tap the same button again to stop //

    //commented out because it was cause problems with the claw code and we  cdon't need the intake code
    // if (Controller.ButtonR1.pressing() && intakeSpeed != 100 && !buttonR1Held) {
    //   intakeMotor.spin(forward, 100, percent);
    //   intakeSpeed = 100;
    //   buttonR1Held = true;
    // } 
    // else if(Controller.ButtonR1.pressing() && intakeSpeed == 100 && !buttonR1Held) {
    //   intakeMotor.stop(coast);
    //   intakeSpeed = 0;
    //   buttonR1Held = true;
    // }
    // else if (Controller.ButtonR2.pressing() && intakeSpeed != -100 && !buttonR2Held) {
    //   intakeMotor.spin(reverse, 100, percent);
    //   intakeSpeed = -100;
    //   buttonR2Held = true;
    // } 
    // else if (Controller.ButtonR2.pressing() && intakeSpeed == -100 && !buttonR2Held){
    //   intakeMotor.stop(coast);
    //   intakeSpeed = 0;
    //   buttonR2Held = true;
    // }

    // if(!Controller.ButtonR1.pressing()) {
    //   buttonR1Held = false;
    // }
    // if(!Controller.ButtonR2.pressing()) {
    //   buttonR2Held = false;
    // }

    //========== MOTOR CLAW CONTROL ==========//

    //Commented out because we don't need the motor claw code, but might use it later if we want to switch back to a motor claw instead of a piston claw.//
    
    // Use R1 to control the claw to open and close. //
    // if (Controller.ButtonR1.pressing() && buttonHeld == false) {
    //   // Toggle the claw state
    //   if(clawIsOpen) {
    //       intakeMotor.spinToPosition(-20, deg, false); //closes claw(number depends on what's needed)
    //       clawIsOpen = false;
    //   }
    //   else {
    //       intakeMotor.spinToPosition(-100, deg, false); //opens claw(number depends on what's needed)
    //       clawIsOpen = true;
    //   }
    //   buttonHeld = true;
    // }
    // // prevent button holding by checking if the button is released
    // else if (!Controller.ButtonR1.pressing()) {
    //       buttonHeld = false;
    // }

    //========== PISTON CLAW CONTROL ==========//
    if (Controller.ButtonR1.pressing() && buttonHeld == false) {
      // Toggle the claw state
      if (clawIsOpen) { // If the claw is open, close it
        DoubleActingPiston.set(false);
        clawIsOpen = false;
      }
      else if(!clawIsOpen) { // If the claw is closed, open it
        DoubleActingPiston.set(true);
        clawIsOpen = true;
      }
      buttonHeld = true;
    }
    
    // prevent button holding by checking if the button is released
    else if (!Controller.ButtonR1.pressing()) {
          buttonHeld = false;
    }

    // ========== COLOR SENSOR ========== //
    // Commented out because we don't have a color sensor, but might use it later if we want to use the color sensor. //
    // color detectedColor = OpticalSensor.color();

    // if (detectedColor == color::blue) {
    //   Brain.Screen.printAt(50, 50, "Blue Detected!");
    // } 
    
    // else if (detectedColor == color::red) {
    //   Brain.Screen.printAt(50, 50, "Red Detected!");
    // } 

    // else {
    //   Brain.Screen.printAt(50, 50, "No specific color detected.");
    // }

    // ========== PNEUMATICS ========== //
    // Use the X button to toggle the piston position //
    // Commented out because we don't need the piston code. //
    // if(Controller.ButtonX.pressing() && !buttonXHeld) {
    //   DoubleActingPiston.set(!DoubleActingPiston.value());
    //   buttonXHeld = true;
    // }
    // else if(!Controller.ButtonX.pressing()) {
    //   buttonXHeld = false;
    // }

    // ========== LOOP DELAY ========== //
    wait(20, msec);
  }
}

// Entry point
int main() {

  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  
  pre_auton();
  Competition.test_auton();
  Competition.test_driver();


  while (true) {
    wait(100, msec);
  }
}