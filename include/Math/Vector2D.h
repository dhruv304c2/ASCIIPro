#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <cmath>
#include <sstream>
#include <string>

template <typename T>
class Vector2D{
    public:
        T x;
        T y;
        Vector2D<T>(T x = 0, T y = 0){
            this -> x = x;
            this -> y = y;
        }

        T magnitude(){
            return sqrt(x*x + y*y);
        }

        Vector2D<T> normalize(){
            auto mag = magnitude();
            if(mag == 0) return this;
            T x = this -> x / mag;
            T y = this -> y / mag;
            return Vector2D<T>(x,y);
        }

        Vector2D<T> operator+(Vector2D<T> const& p){
            T x = p.x + this -> x;
            T y = p.y + this -> y;
            return Vector2D<T>(x,y);
        }

        Vector2D<T> operator-(Vector2D<T> const& p){
            T x = this -> x - p.x;
            T y = this -> y - p.y;
            return Vector2D<T>(x,y);
        }

        Vector2D<T> operator*(T const& mult){
            T x = this -> x * mult;
            T y = this -> y * mult;
            return Vector2D<T>(x,y);
        }

        template<typename TCast>
        operator Vector2D<TCast>() const {
            TCast x = static_cast<TCast>(this ->x);
            TCast y = static_cast<TCast>(this ->y);
            return Vector2D<TCast>(x,y);
        }

        std::string toString(){
            std::ostringstream oss;
            oss << "(" << x << "," << y << ")";
            return oss.str();
        }
};

#endif
