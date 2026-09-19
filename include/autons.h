/* Helps prevent header files from being included multiple times*/
#pragma once
#include "drive.h"
#include "intake.h"

extern drive Chassis;
extern intake Intake;

//Autons//
void rightAuton();
void leftAuton();
void skillsAuton();