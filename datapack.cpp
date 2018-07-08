#include "datapack.h"

#include <stdio.h>
#include <iostream>

DataPack::DataPack()
{

}

DataPack::~DataPack()
{

}

cleanBotInfo DataPack::unpack()
{
    cleanBotInfo rclean;
    if ( strlen( (char *)buff ) !=0 && checkBuff() ) {

        // unpack middle infos
        for ( int i =0; i < RCRNUM ; i++ )
        {
            float speed;
            float height;
            int status;

            // unpack info  into buff
            //1, unpack status_buff
            status_buff[0] = buff[ HEADNUM + i * LENGTH_PACK + 0 ];
            //sum_check_uchar += status_buff[0];
            //2, unpack speed_buff
            for ( int j =0; j < LENGTH_SPEED ; j++ )
            {
                speed_buff[j] = buff[ HEADNUM + i * LENGTH_PACK + 1 + j ];
                //sum_check_uchar += speed_buff[j];
            }
            //3, unpack height_buff
            for ( int j =0; j < LENGTH_HEIGHT ; j++ )
            {
                height_buff[j] = buff[ HEADNUM + i * LENGTH_PACK + 1 + LENGTH_SPEED + j ];
                //sum_check_uchar += height_buff[j];
            }
            // transfer uchar into data
            Byte_to_Float( &speed, speed_buff );
            Byte_to_Float( &height, height_buff );
            status = status_buff[0];

            ropeBotInfo rcr;
            rcr.id = i + 1;

            rcr.speed = speed;
            rcr.height = height;
            rcr.status = status;
            rclean.RCR.push_back(rcr);
        }

    }
    return rclean;
}

bool DataPack::checkBuff()
{
    sum_check_uchar = 0;
    for ( int i =0; i < RCRNUM * LENGTH_PACK ; i++ )
    {
        sum_check_uchar += buff[ HEADNUM + i ];
    }
    if ( sum_check_uchar == buff[ HEADNUM + RCRNUM * LENGTH_PACK ] ){

        return true;
    }else{
        cout<<"unpack sum check error!" <<endl;
        sum_check_uchar = 0;
        return false;
    }
}

void DataPack::pack(cleanBotInfo rclean)
{
    // add head
    for ( int i =0; i < HEADNUM ; i++ )
    {
        buff[i] = HEADVALUE;
    }
    // add middle infos
    sum_check_uchar = 0;
    for ( int i =0; i < RCRNUM ; i++ )
    {
        float speed;
        float height;
        int status;
        speed =  rclean.RCR.at(i).speed;
        height = rclean.RCR.at(i).height;
        status = rclean.RCR.at(i).status;

        // transfer the data into uchar
        Float_to_Byte( speed, speed_buff );
        Float_to_Byte( height, height_buff );
        status_buff[0] = uchar(status);

        // pack status into buff
        //1, pack status_buff
        buff[ HEADNUM + i * LENGTH_PACK + 0 ] = status_buff[0];
        sum_check_uchar += status_buff[0];
        //2,pack speed_buff
        for ( int j =0; j < LENGTH_SPEED ; j++ )
        {
            buff[ HEADNUM + i * LENGTH_PACK + 1 + j ] = speed_buff[j];
            sum_check_uchar += speed_buff[j];
        }
        //3,pack height_buff
        for ( int j =0; j < LENGTH_HEIGHT ; j++ )
        {
            buff[ HEADNUM + i * LENGTH_PACK + 1 + LENGTH_SPEED + j ] = height_buff[j];
            sum_check_uchar += height_buff[j];
        }

    }

    //add sum_check_uchar
    buff[ HEADNUM + RCRNUM * LENGTH_PACK ] = sum_check_uchar ;

    //add tail
    for ( int i =0; i < TAILNUM ; i++ )
    {
        buff[ HEADNUM + RCRNUM * LENGTH_PACK + 1 + i ] = TAILVALUE;
    }
}

/*** change buff to qstring **/
QString DataPack::ucharArrToQString(uchar  buff[])
{
      char b[] = "";
      for ( unsigned int i =0; i < sizeof(buff) ; i++ )
      {
          b[i] = char(buff[i]);
      }
      return QString(QLatin1String(b));
}

/*        set data to buff  */
void DataPack::setBuff(char data[])
{
    for ( unsigned int i =0; i < sizeof(data) ; i++ )
    {
        buff[i] = uchar(data[i]);
    }
}

QString DataPack::getBuffToQstring()
{
    if ( strlen( (char *)buff ) != 0 ){
        return ucharArrToQString( buff );
    }else{
        return "";
    }
}

QByteArray DataPack::getBuff()
{
    QByteArray qarr;
    qarr = getBuffToQstring().toLatin1();
    return qarr;
}

/*将浮点数f转化为4个字节数据存放在byte[4]中*/
void DataPack::Float_to_Byte(float f,unsigned char byte[])
{
    FloatLongType fl;
    fl.fdata=f;
    byte[0]=(unsigned char)fl.ldata;
    byte[1]=(unsigned char)(fl.ldata>>8);
    byte[2]=(unsigned char)(fl.ldata>>16);
    byte[3]=(unsigned char)(fl.ldata>>24);
}

/*将4个字节数据byte[4]转化为浮点数存放在*f中*/
void DataPack::Byte_to_Float(float *f,unsigned char byte[])
{
    FloatLongType fl;
    fl.ldata=0;
    fl.ldata=byte[3];
    fl.ldata=(fl.ldata<<8)|byte[2];
    fl.ldata=(fl.ldata<<8)|byte[1];
    fl.ldata=(fl.ldata<<8)|byte[0];
    *f=fl.fdata;
}


