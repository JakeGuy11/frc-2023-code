# pragma once
#include <string>
#include <iostream>
#include <queue>
#include "utils.h"

enum StartPos {
  DISABLE,
  FAR,
  MIDDLE,
  STATION_ADJACENT
};

enum AutoState {
  INIT,
  SCORE_MOVE,
  SCORE_ENGAGE,
  SCORE_SCORE,
  SCORE_RETRACT,
  SCORE_RETURN,
  DOCK,
  MOBILITY_GO,
  MOBILITY_RETURN,
  ENGAGE_BALANCE,
  IDLE
};

typedef struct {
  StartPos pos;
  bool score;
  bool dock;
  bool mobility;
  bool engage;
} SelectedAutoFeatures;

class MechaAuto {
 public:
  MechaAuto(double startNanos);
  void StartAuto(double nanos, std::string key);
  void AutoUpdate(double currentNanos);
  AutoState GetState();

 private:
  AutoState currentState = AutoState::INIT;
  std::queue<AutoState> taskQueue;
  SelectedAutoFeatures tasksToPreform;
  double startTime;

  void OverwriteKey(std::string);
  void HandleInit();
};