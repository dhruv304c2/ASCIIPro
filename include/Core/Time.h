#ifndef TIME_H
#define TIME_H

class Time {
public:
    Time();
    ~Time();
    int getTime();
    int getDelta();
    void setDelta(float delta);
    void waitDelta();
private:
    float time;
    float delta;
};

#endif
