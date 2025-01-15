#ifndef PROFILERRENDERER_H
#define PROFILERRENDERER_H

#include "Core/Profiler.h"
#include "Core/Rendering/Renderer.h"
#include "Core/Viewport/Viewport.h"

class ProfilerRenderer : public Renderer {
public:
    ProfilerRenderer(Viewport* viewport, Game* game, Profiler* profiler);
    ~ProfilerRenderer();
    void render() override;
private:
    Profiler* m_profiler;
    std::wstring log();
};

#endif
