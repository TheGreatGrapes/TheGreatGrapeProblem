#include "Timer.h"

Timer::Timer() {
    now = time(0);
    ltm_n = localtime(&now);
    timeNow = ltm_n->tm_sec;
}

Timer::~Timer() {
}

void Timer::timeInit() {
    after = time(0);
    ltm_a = localtime(&after);
    timeAfter = ltm_a->tm_sec;
}

int Timer::measureTime() {
    return timeAfter - timeNow;
}

void Timer::resetTimer() {
    timeNow = timeAfter;
}

void Timer::check() {
    if(timeAfter == 59) {
        timeNow = -1;
    }
}