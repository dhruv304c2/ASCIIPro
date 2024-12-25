#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "../ECS/Component.h"

template <typename T>
class Vector2D{
    public:
        T x;
        T y;
        Vector2D(T x = 0, T y = 0){
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

        template<typename TCast>
        operator Vector2D<TCast>() const {
            TCast x = static_cast<TCast>(this ->x);
            TCast y = static_cast<TCast>(this ->y);
            return Vector2D<TCast>(x,y);
        }
};

class Transform : public Component{
public:
    Transform();
    ~Transform();
    Vector2D<float> position;
};

#endif
