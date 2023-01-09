#include "Autonomous.h"

MechaAuto::MechaAuto(double startNanos) :
    startTime(startNanos) {
    // Do anything we need to initialize the autonomous
}

void MechaAuto::StartAuto(double nanos, std::string key) {
    startTime = nanos;
    this->OverwriteKey(key);

    // Update our queue with instructions
    if (tasksToPreform.pos == StartPos::DISABLE) {
        taskQueue.push(AutoState::IDLE);
        return;
    }
    taskQueue.push(AutoState::INIT);
    if (tasksToPreform.score) {
        taskQueue.push(AutoState::SCORE_MOVE);
        taskQueue.push(AutoState::SCORE_ENGAGE);
        taskQueue.push(AutoState::SCORE_SCORE);
        taskQueue.push(AutoState::SCORE_RETRACT);
        taskQueue.push(AutoState::SCORE_RETRACT);
    }
    if (tasksToPreform.dock) {
        taskQueue.push(AutoState::DOCK);
    }
    if (tasksToPreform.mobility) {
        taskQueue.push(AutoState::MOBILITY_GO);
        taskQueue.push(AutoState::MOBILITY_RETURN);
    }
    if (tasksToPreform.engage) {
        taskQueue.push(AutoState::ENGAGE_BALANCE);
    }
    taskQueue.push(AutoState::IDLE);
}

void MechaAuto::OverwriteKey(std::string key) {
    switch (key[0]) {
        case 'F':
            tasksToPreform.pos = StartPos::FAR;
            break;
        case 'M':
            tasksToPreform.pos = StartPos::MIDDLE;
            break;
        case 'S':
            tasksToPreform.pos = StartPos::STATION_ADJACENT;
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

void MechaAuto::AutoUpdate(double currentNanos) {
    std::queue<AutoState> q(taskQueue);
    for (;!q.empty(); q.pop()) {
        std::cout << q.front() << ", ";
    }
    std::cout << "\b\b" << std::endl;
}

void MechaAuto::HandleInit() {

}