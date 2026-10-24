// src/robot-config.cpp
#include "robot-config.h"

using namespace vex;

//Configuration!

/* 
 * Reminders: 
 * Make sure that all your ports are different and correct! 
 * Make sure all of your motor + piston names are different and not confusing.
 * If it seems like some of your motors are running against eachother in the drivetrain, try switching around the true/false
*/

//DON'T CHANGE THE NAMES OF THE MOTORS OR SENSORS. Changing the ports to reflect your robot is ok.

brain Brain;
controller Controller(controllerType::primary);
motor LB(PORT18, ratio18_1, false); //Left Back Motor
motor LM(PORT19, ratio18_1, false); //Left Middle Motor
motor LF(PORT4, ratio18_1, false); //Left Front Motor
motor RB(PORT13, ratio18_1, true); //Right Back Motor
motor RM(PORT12, ratio18_1, true); //Right Middle Motor
motor RF(PORT3, ratio18_1, true); //Right Front Motor


motor_group leftDrive(LF, LM, LB);
motor_group rightDrive(RF, RM, RB);

motor Lift1(PORT1, gearSetting::ratio18_1, false); //Left Lift motor
motor Lift2(PORT8, gearSetting::ratio18_1, true); //Right Lift motor

motor_group Lifts(Lift1, Lift2);

digital_out DoubleActingPiston(Brain.ThreeWirePort.H); // claw piston

motor intakeMotor(PORT6, ratio18_1, false); // claw motor
// motor middleIntakeMotor(PORT9, ratio18_1, true);
// motor  bottomIntakeMotor(PORT12, ratio18_1, false);

motor_group intakeMotors(intakeMotor);

inertial InertialSensor(PORT7);

optical OpticalSensor(PORT21);

void vexcodeInit() {
  intakeMotor.setPosition(0, deg);
  InertialSensor.calibrate();
  DoubleActingPiston.set(false); //closed claw position
  // while (InertialSensor.isCalibrating()) {
  //   task::sleep(100);
  // }
  // Controller.rumble("...");
}