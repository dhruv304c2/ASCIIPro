#include "Core/Profiler.h"
#include "Core/Time.h"
#include <queue>

Profiler::Profiler(GameClock* clock) {
    m_game_clock = clock;
    m_frames = 0;

    m_game_clock->on_frame_recorded.addListener([&](){this->evaluate();});
}

Profiler::~Profiler() {}

Profile Profiler::getProfile(){
    Profile profile;
    profile.game_duration_s = m_total_duration_s;
    profile.frames = m_frames;
    profile.average_fps = m_average_fps;
    profile.smoothed_fps = m_smoothed_fps;
    return profile;
}

float calculateSmoothedFps(std::queue<float> &mfps_buffer){
    float sum = 0;
    std::queue<float> temp; 

    while (!mfps_buffer.empty()) {
        float val = mfps_buffer.front();
        sum += val;
        temp.push(val);
        mfps_buffer.pop();
    }

    mfps_buffer = temp;
    return (float)SMOOTH_FPS_BUFFER_SIZE/sum;
}

void Profiler::evaluate(){
    m_total_duration_s = m_game_clock->time().time();
    m_delta_s = m_game_clock->time().delta();
    m_frames++;
    m_average_fps = m_frames / m_total_duration_s;

    if(m_fps_buffer.size() >= SMOOTH_FPS_BUFFER_SIZE){
	m_fps_buffer.pop();
    }
    m_fps_buffer.push(m_delta_s);
    m_smoothed_fps = calculateSmoothedFps(m_fps_buffer);
}
