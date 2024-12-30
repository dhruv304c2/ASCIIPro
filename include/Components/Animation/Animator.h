#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "../../ECS/Component.h"
#include <vector>

class KeyFrame{
public:
    virtual void executeFrame();
    virtual float holdTime();
};

class Clip{
public:
    void useFrames(std::vector<KeyFrame*> frames){
        this -> frames = frames;
        active_frame_it = frames.begin();
    }
    bool looping;
    bool end;
    void playFrame(){
        auto frame = *active_frame_it;
        frame -> executeFrame();
    }
protected:
    std::vector<KeyFrame*> frames;
    std::vector<KeyFrame*>::iterator active_frame_it;
};

class Animator : public Component {
public:
    Animator();
    ~Animator();
    void playClip(Clip* clip);
protected:
    Clip* active_clip;
};

#endif
