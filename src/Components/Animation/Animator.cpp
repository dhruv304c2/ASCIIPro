#include "Components/Animation/Animator.h"
#include "ECS/Component.h"

Animator::Animator(void* ent_ptr) : Component(ent_ptr) {}

Animator::~Animator() {}

void Animator::playClip(Clip* clip){
    active_clip = clip; 
}
