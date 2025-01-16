#include "Core/Profiler.h"
#include "Core/Time.h"
#include <cstddef>
#include <queue>

struct AllocationTracker {
    static constexpr std::size_t MAX_ALLOCATIONS = 1024;
    void* pointers[MAX_ALLOCATIONS] = {nullptr};
    std::size_t sizes[MAX_ALLOCATIONS] = {0};
    std::size_t count = 0;

    void track(void* ptr, std::size_t size) {
        if (count < MAX_ALLOCATIONS) {
            pointers[count] = ptr;
            sizes[count] = size;
            count++;
        }
    }

    void untrack(void* ptr) {
        for (std::size_t i = 0; i < count; ++i) {
            if (pointers[i] == ptr) {
                pointers[i] = pointers[count - 1];
                sizes[i] = sizes[count - 1];
                count--;
                return;
            }
        }
    }

    std::size_t totalAllocated() const {
        std::size_t total = 0;
        for (std::size_t i = 0; i < count; ++i) {
            total += sizes[i];
        }
        return total;
    }
};

static AllocationTracker ALLOC_TRACKER;

void* operator new(std::size_t size) {
    void* ptr = malloc(size);
    if (!ptr) throw std::bad_alloc();
    ALLOC_TRACKER.track(ptr, size);
    return ptr;
}

void operator delete(void* ptr) noexcept {
    ALLOC_TRACKER.untrack(ptr);
    free(ptr);
}

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
    profile.allocations_bits = ALLOC_TRACKER.count;
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
