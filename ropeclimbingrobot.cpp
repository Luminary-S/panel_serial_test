#include "ropeclimbingrobot.h"
#include "cleaningrobotwindow.h"
#include "ui_cleaningrobotwindow.h"
#include <QApplication>
#include "datastruct.h"
//#define UP 1
//#define DOWN -1
//#define STOP 0

using namespace std;



void ropeClimbingRobot::setSpeed(float s)
{
    this->speed = s;
}

float ropeClimbingRobot::getSpeed()
{
    return this->speed;
}

void ropeClimbingRobot::setHeight(float h)
{
    this->height = h;
}

float ropeClimbingRobot::getHeight()
{
    return this->height;
}

void ropeClimbingRobot::setDirection(int i)
{
    this->direction = i;
}

int ropeClimbingRobot::getDirection()
{
    return this->direction;
}

