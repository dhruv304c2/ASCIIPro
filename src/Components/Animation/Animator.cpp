#include "../../../includes/Components/Animation/Animator.h"

Animator::Animator() {}

Animator::~Animator() {}

void Animator::playClip(Clip* clip){
    active_clip = clip; 
}
