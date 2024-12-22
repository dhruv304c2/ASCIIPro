#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "../ECS/Component.h"

struct Vector2D{
    public:
        int x;
        int y;
        Vector2D(int x = 0, int y = 0){
            this -> x = x;
            this -> y = y;
        }

        Vector2D operator+(Vector2D const& p){
            int x = p.x + this -> x;
            int y = p.y + this -> y;
            return Vector2D(x,y);
        }

        Vector2D operator-(Vector2D const& p){
            int x = this -> x - p.x;
            int y = this -> y - p.y;
            return Vector2D(x,y);
        }
};

class Transform : public Component{
public:
    Transform();
    ~Transform();
    Vector2D position;
};

#endif
