#include "rserialport.h"
#include <QMainWindow>


RserialPort::RserialPort()
{    
    my_serialport = new QSerialPort;
    sendBuff = 0;
    receiveBuff = 0;
    initPort();
}

RserialPort::~RserialPort()
{

}

void RserialPort::initPort()
{
    baudList<<"50"<<"75"<<"100"<<"134"<<"150"<<"200"<<"300"
           <<"600"<<"1200"<<"1800"<<"2400"<<"4800"<<"9600"
          <<"14400"<<"19200"<<"38400"<<"56000"<<"57600"
         <<"76800"<<"115200"<<"128000"<<"256000";

    parityList<<"no"<<"odd"<<"even";
    parityList<<"mark";
    parityList<<"space";

    dataBitsList<<"5"<<"6"<<"7"<<"8";
    stopBitsList<<"1";
    stopBitsList<<"1.5";
    stopBitsList<<"2";

}

void RserialPort::readPortCOM()
{
    //read the serial com info
    portList.clear();
        foreach (const QSerialPortInfo &info,  QSerialPortInfo::availablePorts() )
        {
            qDebug()<<"Name:"<<info.portName();
            qDebug()<<"Description:"<<info.description();
            qDebug()<<"Manufacturer:"<<info.manufacturer();

            //here the program automatically gets all the serial port in the window, if you select any the selected will be used
            QSerialPort serial;

            serial.setPort(info);
            if(serial.open(QIODevice::ReadWrite))
            {
                //add serial com port to item cmbPortName
                portList<<info.portName();
                //close serial port to wait for openning operation
                serial.close();
            }
        }
}

void RserialPort::setSerialPort()
{
    //设置串口号
    my_serialport->setPortName( portname );
    //以读写方式打开串口
    my_serialport->open(QIODevice::ReadWrite);

    //设置波特率
    my_serialport->setBaudRate( baudrate );
    //设置数据位
    my_serialport->setDataBits(QSerialPort::Data8);
    //设置校验位
    my_serialport->setParity(QSerialPort::NoParity);
    //设置流控制
    my_serialport->setFlowControl(QSerialPort::NoFlowControl);
    //设置停止位
    my_serialport->setStopBits(QSerialPort::OneStop);
    QObject::connect( my_serialport, SIGNAL( readyRead() ), this, SLOT( readComDataSlot() ) );

    //QObject::connect( my_serialport, &QSerialPort::readyRead, this, &RserialPort::readComDataSlot );
}

void RserialPort::clearSerialPort()
{
    try{
    my_serialport->clear();
    my_serialport->close();
    //my_serialport->deleteLater();
    }catch( QString ex )
    {
       qDebug()<<"Clear error:  maybe you don't set up your serialport"<<ex;
       return;
   }
}

bool RserialPort::checkValue( QByteArray qarr, char val, int pos, int num)
{
    for( int i = 0; i< num; i++){
        if ( qarr.at(pos+i) == val ){
            continue;
        }else{
            return false;
        }
    }
    return true;
}

void RserialPort::setPortName(QString str)
{
    portname = str;
}

void RserialPort::setBaudRate(int num)
{
    baudrate = num;
}

void RserialPort::setSendBuff(QByteArray qarr)
{
    sendBuff = qarr;
}

void RserialPort::toReceiveBuff(QByteArray buf)
{
    //int s_position = 0;
    //check buf and set it to receiveBuff
    if ( buf.length() >= LENGTH_DATA  ){
        for(int i = 0 ; i < (buf.length() - LENGTH_DATA + 1); i++){
            if ( checkValue(buf, HEADVALUE, i, 4) &&  checkValue(buf, HEADVALUE, (i+LENGTH_DATA-TAILNUM), 4) ){

                //s_position = i;
                //e_position = i
                receiveBuff = buf.mid(i,LENGTH_DATA);
            }
        }
    }
}

/***** read  data from serial com ****/
void RserialPort::readComDataSlot()
{
    QByteArray buf;
    //int e_position = 0;
    while (my_serialport->waitForReadyRead(10))
    {
        buf += my_serialport->readAll();
    }
    toReceiveBuff(buf);
    //清除缓冲区
    buf.clear();
}

/***** send  data to serial com ****/
void RserialPort::writeComData()
{
    try{
        if ( my_serialport != Q_NULLPTR && !sendBuff.isEmpty() ) {
                 my_serialport->write(sendBuff);
         }
     }catch( QString ex )
     {
        qDebug()<<"Send error: "<<ex;
        //return;
    }
}

QByteArray RserialPort::getReceiveBuff()
{
    return receiveBuff;
}

bool RserialPort::isRserialOpen()
{
      return my_serialport->isOpen();
}
