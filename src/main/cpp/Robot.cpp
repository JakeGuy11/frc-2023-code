// Copyright (c) 2022, JakeGuy11 and FRC Team 7722

#include "Robot.h"

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
}

void Robot::RobotPeriodic() { }

void Robot::AutonomousInit() { }

void Robot::AutonomousPeriodic() { }

void Robot::TeleopInit() { }

void Robot::TeleopPeriodic() { }

void Robot::DisabledInit() { }

void Robot::DisabledPeriodic() { }

void Robot::TestInit() { }

void Robot::TestPeriodic() { }

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
