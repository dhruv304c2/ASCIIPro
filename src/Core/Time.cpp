#include "Core/Time.h"
#include <chrono>

using namespace std::chrono;

Time::Time(float time, float delta) {
    _time = time;
    _delta = delta;
}

Time::~Time() {}

float Time::delta(){
    return _delta;
}

float Time::time(){
    return  _time;
}

GameClock::GameClock(){};

GameClock::~GameClock(){};

void GameClock::recordStartGameTime(){
    auto now  = system_clock::now();
    _game_start_time = now;
    _frame_start_time = now;
}

void GameClock::recordFrame(){
    auto now = system_clock::now();
    duration<float> delta = now - _frame_start_time;
    if(delta.count() > 0){
	_frame_start_time = now;
    }
}

Time GameClock::time(){
    auto now  = system_clock::now();
    duration<float> delta_min = now - _frame_start_time;
    duration<float> time = now - _game_start_time;

    return  Time(time.count(), delta_min.count());
}
