// Copyright (c) 2023, JakeGuy11 and FRC Team 7722

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
  mPrint("Entering autonomous mode...");
  autonomous.StartAuto(std::chrono::system_clock::now().time_since_epoch().count(), m_autoSelected); // 10^-9s
}

void Robot::AutonomousPeriodic() {
  //updateDriveMotors(1.0, 1.0, false);
  autonomous.AutoUpdate(std::chrono::system_clock::now().time_since_epoch().count());
}

// Runs at start of teleop
void Robot::TeleopInit() {
  mPrint("Entering teleop mode...");
}

void Robot::TeleopPeriodic() {
  handleDrive();
}

// Do all the calculations for driving
void Robot::handleDrive() {
  double x = stick.GetX() * JOYSTICK_SENS;  // In terms of arcade drive, this is turn
  double y = -stick.GetY() * JOYSTICK_SENS;  // In terms of arcade drive, this is speed

  double leftPower = (y + x) / 2;
  double rightPower = (y - x) / 2;

  updateDriveMotors(leftPower, rightPower, true);
}

// Update the drive motors
void Robot::updateDriveMotors(double lPower, double rPower, bool human) {
  if (!userControlEnabled || !human) return;

  if (lPower != lastDrivePowers.first) {
    mLeft.Set(MCONTROLLER_MODE, lPower * L_MOTOR_SENS);
    lastDrivePowers.first = lPower;
  }

  if (rPower != lastDrivePowers.second) {
    mRight.Set(MCONTROLLER_MODE, rPower * R_MOTOR_SENS);
    lastDrivePowers.second = rPower;
  }
}

// When the robot is first disabled
void Robot::DisabledInit() { mPrint("Robot Disabled."); }

// Periodically when the robot is disabled
void Robot::DisabledPeriodic() {
  // Update with PDP stats
  double v = pdp.GetVoltage();
  double temp = pdp.GetTemperature();
  std::ostringstream initMsg;
  initMsg << temp << "??C @ " << v << "V";
  mPrint(initMsg.str());
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
  initMsg << temp << "??C @ " << v << "V";

  mPrint(initMsg.str());
}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif

void Robot::TestInit() { }
void Robot::TestPeriodic() { }