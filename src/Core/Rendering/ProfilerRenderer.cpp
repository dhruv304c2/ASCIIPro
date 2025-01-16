#include "Core/Rendering/ProfilerRenderer.h"
#include "Core/Game.h"
#include "Core/Profiler.h"
#include "Core/Rendering/Renderer.h"
#include "Core/Viewport/Viewport.h"
#include <cstddef>
#include <string>

ProfilerRenderer::ProfilerRenderer(Viewport* viewport, Game* game, Profiler* profiler) : 
    Renderer(viewport, game),
    m_profiler(profiler){

    }

ProfilerRenderer::~ProfilerRenderer() {}

void ProfilerRenderer::render(){
    std::wstring log = this->log();
    int logIndex = 0;

    for (int i = 1; i < _viewport->height(); i++) {
        for (int j = 1; j < _viewport->width(); j++) {
            if(logIndex < log.size()){
                wchar_t c = log[logIndex];
                logIndex++;
                if (c == L'\n' || c == L'\0') {
                    break;
                }
                _viewport->buffer[i][j] = c;
            }
        }
    }
}

std::wstring ProfilerRenderer::log(){
    float smooth_fps = m_profiler->getProfile().smoothed_fps;
    float average_fps = m_profiler->getProfile().average_fps;
    float delta = m_profiler->getProfile().delta_s;
    float time = m_profiler->getProfile().game_duration_s;
    std::size_t allocated = m_profiler->getProfile().allocations_bits;
    std::wstring log;
    std::wstring smooth_fps_str = std::to_wstring(smooth_fps);
    std::wstring average_fps_str = std::to_wstring(average_fps);
    std::wstring delta_str = std::to_wstring(delta);
    std::wstring time_str = std::to_wstring(time);
    std::wstring allocated_str = std::to_wstring(allocated);
    log += L"Smooth FPS: ";
    log += smooth_fps_str;
    log += L"\n";
    log += L"Average FPS: ";
    log += average_fps_str;
    log += L"\n";
    log += L"Delta: ";
    log += delta_str;
    log += L"\n";
    log += L"Game Duration: ";
    log += time_str;
    log += L"\n";
    log += L"Memory Allocations: ";
    log += allocated_str;
    log += L"\n";
    return log;
}


