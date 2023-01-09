// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/TimedRobot.h>
#include <frc/PowerDistribution.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/Joystick.h>
#include <ctre/phoenix/motorcontrol/can/VictorSPX.h>
#include <ctre/phoenix/motorcontrol/NeutralMode.h>
typedef ctre::phoenix::motorcontrol::can::VictorSPX VictorSPX;
typedef ctre::phoenix::motorcontrol::VictorSPXControlMode VictorSPXControlMode;
typedef ctre::phoenix::motorcontrol::NeutralMode NeutralMode;
typedef frc::PowerDistribution PDP;

#include <string>
#include <utility>
#include <iostream>
#include "config.h"
#include "utils.h"

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void TestInit() override;
  void TestPeriodic() override;

 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "-----";
  std::string m_autoSelected;

  bool userControlEnabled = true;
  std::pair<double, double> lastDrivePowers {0.0, 0.0}; // LEFT, RIGHT

  frc::Joystick stick     {JOYSTICK_PORT};
  PDP pdp                 {ID_PDP, PDP_TYPE};
  VictorSPX mRight        {ID_RMOTOR1};
  VictorSPX mRight2       {ID_RMOTOR2};
  VictorSPX mLeft         {ID_LMOTOR1};
  VictorSPX mLeft2        {ID_LMOTOR2};

  void handleDrive();
  void updateDriveMotors(double lPower, double rPower);

  void initPDP();
  void initDriveControllers(NeutralMode m);
};
