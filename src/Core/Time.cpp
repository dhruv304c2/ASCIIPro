#include "../.././includes/Core/Time.h"
#include <chrono>
#include <thread>

Time::Time() {
    time = 0;
    delta = 0;
}

int Time::getTime() {
    return time;
}

int Time::getDelta() {
    return delta;
}

void Time::setDelta(float delta) {
    this ->delta = delta; 
}

void Time::waitDelta(){
    auto now = std::chrono::steady_clock().now(); 
    std::chrono::duration<float> duration(delta); 
    std::this_thread::sleep_until(now + duration);
    time += delta;
}

Time::~Time() {
}

