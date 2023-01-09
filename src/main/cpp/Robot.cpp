// Copyright (c) 2022, JakeGuy11 and FRC Team 7722

#include "Robot.h"

// Runs at the init of the robot
void Robot::RobotInit() {
  // Init the PDP
  initPDP();

  // Get all our autonomous options sorted out
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  std::string auto_tags[] = { "F----", "M----", "S----" };
  for (uint i = 0; i < arraySize(auto_tags); i++) {
    m_chooser.AddOption(auto_tags[i], auto_tags[i]);
  }
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
}

void Robot::RobotPeriodic() { }

// Runs at start of auto
void Robot::AutonomousInit() {
  std::cout << "Entering autonomous mode..." << std::endl;
}

void Robot::AutonomousPeriodic() { }

// Runs at start of teleop
void Robot::TeleopInit() {
  std::cout << "Entering teleop mode..." << std::endl;
}

void Robot::TeleopPeriodic() { }

// When the robot is first disabled
void Robot::DisabledInit() { std::cout << "Robot Disabled." << std::endl; }

// Periodically when the robot is disabled
void Robot::DisabledPeriodic() {
  // Update with PDP stats
  double v = pdp.GetVoltage();
  double temp = pdp.GetTemperature();
  std::ostringstream initMsg;
  initMsg << temp << "°C @ " << v << "V";
  std::cout << initMsg.str() << std::endl;
}

// Do some configuration for all the drive motors
void Robot::initDriveControllers(NeutralMode m) {
  // Set the neutral modes
  mRight.SetNeutralMode(m);
  mRight2.SetNeutralMode(m);
  mLeft.SetNeutralMode(m);
  mLeft2.SetNeutralMode(m);

  // Set the inversions
  mRight.SetInverted(false);
  mRight2.SetInverted(false);
  mLeft.SetInverted(true);
  mLeft2.SetInverted(true);

  // Set some follow stuff
  mRight2.Follow(mRight);
  mLeft2.Follow(mLeft);
}

// Do whatever we need to do to initialize the PDP. Not necessary, may be removed if needed
void Robot::initPDP() {
  frc::SmartDashboard::PutString("InitMessage", "Initializing PDP...");

  double v = pdp.GetVoltage();
  double temp = pdp.GetTemperature();

  std::ostringstream initMsg;
  initMsg << temp << "°C @ " << v << "V";

  std::cout << initMsg.str() << std::endl;
}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif

void Robot::TestInit() { }
void Robot::TestPeriodic() { }