#ifndef PROFILER_H
#define PROFILER_H

#include "Core/Time.h"
#include <queue>

#define SMOOTH_FPS_BUFFER_SIZE 60

struct Profile{
public:
    float game_duration_s;
    float delta_s;
    float smoothed_fps;
    float average_fps;
    int frames;
    int allocations_bits;
};

class Profiler {
public:
    Profiler(GameClock* time);
    ~Profiler();
    Profile getProfile();
private:
    GameClock* m_game_clock;
    float m_total_duration_s;
    float m_delta_s;
    float m_smoothed_fps;
    std::queue<float> m_fps_buffer;
    float m_average_fps;
    int m_frames = 0;
    void evaluate();
};

#endif
