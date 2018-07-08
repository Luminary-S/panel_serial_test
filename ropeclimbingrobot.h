#ifndef ROPECLIMBINGROBOT_H
#define ROPECLIMBINGROBOT_H
#include "cleaningrobotwindow.h"
#include "ui_cleaningrobotwindow.h"
#include "datastruct.h"

//#define UP 1
//#define DOWN -1
//#define STOP 0

using namespace std;

struct cleaningrobot
{
    float speed = 0.0;
    float height = 0.0;
    bool status = STOP;
    int direction  = STOP;
};


class ropeClimbingRobot
{
public:
    ropeClimbingRobot(){}
    ropeClimbingRobot(int i)
    {
        this->speed = 0;
        this->direction = STOP;
        this->id = i;
        //printf("i am a new RCR %d",  id);
        printf("i am a new RCR");
    }

    void setSpeed(float);
    float getSpeed();
    void setHeight(float);
    float getHeight();
    void setDirection(int);
    int getDirection();

private:
    float speed;
    float height;
    int direction;
    int id;
};

#endif // ROPECLIMBINGROBOT_H
