#ifndef RSERIALPORT_H
#define RSERIALPORT_H
#include "qserialport.h"
#include "qserialportinfo.h"
#include "qdebug.h"
//#include <QWidget>
#include <QObject>
#include "datastruct.h"

class RserialPort : public QObject
{
    Q_OBJECT
public:
   RserialPort();
    ~RserialPort();
        void initPort();

        void readPortCOM();
        void setSerialPort();
        void clearSerialPort();

        bool checkValue(QByteArray, char, int, int);
        QStringList portList;
        QStringList baudList;
        QStringList parityList;
        QStringList dataBitsList;
        QStringList stopBitsList;

        void setPortName(QString);
        void setBaudRate(int);

        void setSendBuff(QByteArray);
        void toReceiveBuff(QByteArray);
        void writeComData();
        QByteArray getReceiveBuff();
        bool isRserialOpen();

   public slots:
        void readComDataSlot();


    private:

        QString portname;
        int baudrate;
        QSerialPort  *my_serialport;


        QByteArray receiveBuff;
        QByteArray sendBuff;

};

#endif // RSERIALPORT_H
