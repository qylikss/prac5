#include "timer.h"

using namespace std;
using namespace chrono;

void Timer::start() { this->start_time = high_resolution_clock::now(); }

long long Timer::end() {
    steady_clock::time_point end_time = high_resolution_clock::now();
    microseconds duration = duration_cast<microseconds>(end_time - start_time);
    return duration.count();
}
