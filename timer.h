#ifndef TIMER
#define TIMER

#include <chrono>
using namespace std::chrono;

struct Timer {
    void start();
    long long end();

private:
    steady_clock::time_point start_time;
};

#endif
