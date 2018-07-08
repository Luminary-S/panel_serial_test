#ifndef DATAPACK_H
#define DATAPACK_H
#include "QByteArray"
#include "datastruct.h"


/*
要点提示:
1. float和unsigned long具有相同的数据结构长度
2. union据类型里的数据存放在相同的物理空间
*/
typedef union
{
    float fdata;
    unsigned long ldata;
}FloatLongType;


class DataPack
{


public:
    DataPack();
    ~DataPack();
    cleanBotInfo unpack();
    bool checkBuff();
    void pack(cleanBotInfo);

    QString ucharArrToQString(uchar[]);
    void setBuff(char[]);
    QString getBuffToQstring();
    //QStringToBuff();
    QByteArray getBuff();

    void Float_to_Byte(float ,unsigned char []);
    void Byte_to_Float(float *,unsigned char []);


private:
    //datapackage dpack;
    uchar buff[ HEADNUM + LENGTH_PACK * RCRNUM + 1 + TAILNUM ];
    uchar status_buff[LENGTH_STATUS];
    uchar speed_buff[LENGTH_SPEED];
    uchar height_buff[LENGTH_HEIGHT];
    uchar sum_check_uchar;
    /***** transmit data format define , pack and unpack data ****/
//    uchar head[HEADNUM];
//    uchar tail[TAILNUM];
};

#endif // DATAPACK_H
