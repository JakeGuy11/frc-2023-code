#include "Autonomous.h"

// Constructor for the autonomous class
MechaAuto::MechaAuto(double startNanos) :
    startTime(startNanos) {
    // Do anything we need to initialize the autonomous
}

// Do whatever we need to do to get ready for (and start) autonomous mode
void MechaAuto::StartAuto(double nanos, std::string key) {
    // Update the start time and update the key (what we'll be doing)
    startTime = nanos;
    this->OverwriteKey(key);

    // Update our queue with instructions
    if (tasksToPreform.pos == StartPos::DISABLE) {
        taskQueue.push(AutoState::IDLE);
        return;
    }
    // We have actual auto content to preform; add INIT
    taskQueue.push(AutoState::INIT);
    // Do we score?
    if (tasksToPreform.score) {
        taskQueue.push(AutoState::SCORE_MOVE);
        taskQueue.push(AutoState::SCORE_ENGAGE);
        taskQueue.push(AutoState::SCORE_SCORE);
        taskQueue.push(AutoState::SCORE_RETRACT);
        taskQueue.push(AutoState::SCORE_RETRACT);
    }
    // Do we dock?
    if (tasksToPreform.dock) {
        taskQueue.push(AutoState::DOCK);
    }
    // Do we get mobility points?
    if (tasksToPreform.mobility) {
        taskQueue.push(AutoState::MOBILITY_GO);
        taskQueue.push(AutoState::MOBILITY_RETURN);
    }
    // Do we engage?
    if (tasksToPreform.engage) {
        taskQueue.push(AutoState::ENGAGE_BALANCE);
    }
    // Done parsing flags; add IDLE
    taskQueue.push(AutoState::IDLE);
}

// This is our main handler; It will be run each loop and must decide what to do
void MechaAuto::AutoUpdate(double currentNanos) {
    std::queue<AutoState> q(taskQueue);
    std::ostringstream msg;
    for (;!q.empty(); q.pop()) {
        msg << "Preforming task " << taskQueue.front() << ", ";
    }
    msg << "\b\b";
    print(msg.str());

    switch (taskQueue.front()) {
        case AutoState::INIT:
            HandleInit();
            break;
        case AutoState::SCORE_MOVE:
            HandleScoreMove();
            break;
        case AutoState::SCORE_ENGAGE:
            HandleScoreEngage();
            break;
        case AutoState::SCORE_SCORE:
            HandleScoreScore();
            break;
        case AutoState::SCORE_RETRACT:
            HandleScoreRetract();
            break;
        case AutoState::SCORE_RETURN:
            HandleScoreReturn();
            break;
        case AutoState::DOCK:
            HandleDock();
            break;
        case AutoState::MOBILITY_GO:
            HandleMobilityGo();
            break;
        case AutoState::MOBILITY_RETURN:
            HandleMobilityReturn();
            break;
        case AutoState::ENGAGE_BALANCE:
            HandleEngageBalance();
            break;
        default:
            HandleIdle();
            break;
    }
}

// Return which state we're currently in
AutoState MechaAuto::GetState() {
    return taskQueue.front();
}

// Parse a string containing our key and update which tasks we will be performing based on it
void MechaAuto::OverwriteKey(std::string key) {
    switch (key[0]) {
        case 'F':
            tasksToPreform.pos = StartPos::FAR;
            scoreDistance = FAR_SCORE_DIST;
            mobilityDistance = FAR_MOBILITY_DIST;
            break;
        case 'M':
            tasksToPreform.pos = StartPos::MIDDLE;
            scoreDistance = MIDDLE_SCORE_DIST;
            dockDistance = MIDDLE_DOCK_DIST;
            mobilityDistance = MIDDLE_MOBILITY_DIST;
            break;
        case 'S':
            tasksToPreform.pos = StartPos::STATION_ADJACENT;
            scoreDistance = STATIONADJ_SCORE_DIST;
            mobilityDistance = STATIONADJ_MOBILITY_DIST;
            break;
        default:
            tasksToPreform.pos = StartPos::DISABLE;
    }
    switch (key[1]) {
        case 'S':
            tasksToPreform.score = true;
            break;
        default:
            tasksToPreform.score = false;
    }
    switch (key[2]) {
        case 'D':
            tasksToPreform.dock = true;
            break;
        default:
            tasksToPreform.dock = false;
    }
    switch (key[3]) {
        case 'M':
            tasksToPreform.mobility = true;
            break;
        default:
            tasksToPreform.mobility = false;
    }
    switch (key[4]) {
        case 'E':
            tasksToPreform.engage = true;
            break;
        default:
            tasksToPreform.engage = false;
    }
}

void MechaAuto::TransitionState() {
    std::ostringstream msg;
    msg << "Finished task " << taskQueue.front();
    print(msg.str());
    taskQueue.pop();
}

/*
    All functions below here are for handling specific states of autonomous
*/

// For handling the initialization state
void MechaAuto::HandleInit() {
    // Literally nothing to do here
    print("*vine boom*");
    TransitionState();
}

// For handling the state when moving to score
void MechaAuto::HandleScoreMove() {
    // Do stuff here to move into position for scoring
    // go forward scoreDistance
    TransitionState();
}

// For handling the state when engaging the scoring mechanism
void MechaAuto::HandleScoreEngage() {
    // Engage whatever mechanism needs to be to position for the score
    TransitionState();
}

// For handling the state when scoring
void MechaAuto::HandleScoreScore() {
    // Release the piece I guess, just score the point
    TransitionState();
}

// For handling the state when retracting the scoring mechanism
void MechaAuto::HandleScoreRetract() {
    // Retract the scoring mechanism
    TransitionState();
}

// For handling the state when moving back from scoring
void MechaAuto::HandleScoreReturn() {
    // Go back scoreDistance
    TransitionState();
}

// For handling the state when going to dock
void MechaAuto::HandleDock() {
    // Go forward dockDistance
    TransitionState();
}

// For handling the state when moving to score mobility points
void MechaAuto::HandleMobilityGo() {
    // Go forward mobilityDistance
    TransitionState();
}

// For handling the state when returing from scoring mobility points
void MechaAuto::HandleMobilityReturn() {
    // Go back mobilityDistance
    TransitionState();
}

// For handling the state when balancing to score engage points
void MechaAuto::HandleEngageBalance() {
    // Do some weird gyroscope shit
    TransitionState();
}

// For handling the state when every other task is finished
void MechaAuto::HandleIdle() { /* Done auto routine */ }
