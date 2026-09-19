#include "vex.h"
#include "auton-selector.h"
#include "robot-config.h"

using namespace vex;

int autonSelector::autonNumber;
int autonSelector::totalAutons;

autonSelector::autonSelector(int startingAuton, int numAutons) {
  autonNumber = startingAuton;
  totalAutons = numAutons;
}

int autonSelector::getSelectedAuton() {
  return autonNumber;
}

void autonSelector::chooseAuton() {

  std::string autonNames[] = {"right", "left", "skills"};

  Controller.Screen.clearLine(3);
  Controller.Screen.setCursor(3, 1);
  Controller.Screen.print("Auton: %s", autonNames[autonNumber - 1].c_str());

  bool buttonHeld = false;

  while (true) {

    if(Controller.ButtonA.pressing()) {
      break;
    }
  
    if(buttonHeld == true && !(Controller.ButtonLeft.pressing() || Controller.ButtonRight.pressing())) {
      buttonHeld = false;
    }

    if(!buttonHeld && (Controller.ButtonLeft.pressing() || Controller.ButtonRight.pressing())) {
      if (Controller.ButtonLeft.pressing() && autonNumber > 1) {
        autonNumber--;
      }
      else if(Controller.ButtonLeft.pressing()) {
        autonNumber = totalAutons;
      }
      else if(Controller.ButtonRight.pressing() && autonNumber < totalAutons) {
        autonNumber++;
      }
      else if(Controller.ButtonRight.pressing()) {
        autonNumber = 1;
      }
      buttonHeld = true;
      Controller.Screen.clearLine(3);
      Controller.Screen.setCursor(3, 1);
      Controller.Screen.print("Auton: %s", autonNames[autonNumber - 1].c_str());
    } 

    wait(20, msec);
  }

  Controller.Screen.clearLine(3);
  Controller.Screen.setCursor(3, 1);
  Controller.Screen.print("Auton selected: ");
  Controller.Screen.print(autonNames[autonNumber - 1].c_str());
  wait(2, sec);
  Controller.Screen.clearLine(3);
}