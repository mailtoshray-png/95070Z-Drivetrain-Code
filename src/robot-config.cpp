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
motor LB(PORT16, ratio18_1, false); //Left Back Motor(from brain perspective)
motor LM(PORT18, ratio18_1, false); //Left Middle Motor(from brain perspective)
motor LF(PORT19, ratio18_1, false); //Left Front Motor(from brain perspective)
motor RB(PORT15, ratio18_1, true); //Right Back Motor(from brain perspective)
motor RM(PORT14, ratio18_1, true); //Right Middle Motor(from brain perspective)
motor RF(PORT13, ratio18_1, true); //Right Front Motor(from brain perspective)


motor_group leftDrive(LF, LM, LB);
motor_group rightDrive(RF, RM, RB);

motor Lift1(PORT10, gearSetting::ratio18_1, true); //Left Lift motor(from brain perspective)
motor Lift2(PORT1, gearSetting::ratio18_1, false); //Right Lift motor(from brain perspective)

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