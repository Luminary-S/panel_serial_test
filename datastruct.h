#ifndef DATASTRUCT_H
#define DATASTRUCT_H
#include <QList>

/*********  constant define  *********/
#define UP 1
#define DOWN 2
#define STOP 0
#define MOVEMOVE 3
#define RCRNUM 4
#define HEADNUM 4
#define TAILNUM 4
#define LENGTH_SPEED 4
#define LENGTH_HEIGHT 4
#define LENGTH_STATUS 1
#define LENGTH_PACK (LENGTH_SPEED+LENGTH_HEIGHT+LENGTH_STATUS)
#define LENGTH_CHECKSUM 1
#define LENGTH_DATA (HEADNUM+RCRNUM*LENGTH_PACK+LENGTH_CHECKSUM+TAILNUM)
#define CHECK_POSITION 1
#define HEADVALUE 0x0f
#define TAILVALUE 0x0f

using namespace std;

/*                 rope climbing robot              */
struct ropeBotInfo
{
    float speed = 0.0;
    float height = 0.0;
    int status = STOP;
    int direction  = STOP;
    int id;
};

/*******  cleaning robot  ***********/
struct cleanBotInfo
{
    float speed = 0.0;
    float height = 0.0;
    int status = STOP;
    int direction  = STOP;
    std::vector<ropeBotInfo> RCR;

};




#endif // DATASTRUCT_H
