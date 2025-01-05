#ifndef TIME_H
#define TIME_H

#include <chrono>

using namespace std::chrono;

class Time {
public:
    Time(float time, float delta);
    ~Time();
    float time();
    float delta();
private:
    float _time;
    float _delta;
};

class GameClock {
public:
    GameClock();
    ~GameClock();
    Time time();
    void recordStartGameTime();
    void recordFrame();
private:
    time_point<system_clock> _game_start_time;
    time_point<system_clock> _frame_start_time;
};

#endif
