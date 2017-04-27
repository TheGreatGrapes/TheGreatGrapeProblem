#ifndef TIMER_H
#define TIMER_H
#include <ctime>

class Timer {
public:
    Timer();
    ~Timer();

    int measureTime();
    void resetTimer();
    void check();
    void timeInit();

private:
    time_t now;
    time_t after;

    tm* ltm_n;
    tm* ltm_a;

    int timeNow;
    int timeAfter;
};

#endif // TIMER_H
