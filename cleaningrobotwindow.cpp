#include "cleaningrobotwindow.h"
#include "ui_cleaningrobotwindow.h"
#include "ropeclimbingrobot.h"
#include "QMessageBox"
#include "datastruct.h"
#include "datapack.h"

CleaningRobotWindow::CleaningRobotWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CleaningRobotWindow)
{
    rcleanInit();
    ui->setupUi(this);

}

CleaningRobotWindow::~CleaningRobotWindow()
{
    delete ui;
}

void CleaningRobotWindow::rcleanInit()
{
    for (int j = 1; j < RCRNUM+1 ; j++)
    {
        ropeBotInfo rcr;
        rcr.id = j;
        Rclean.RCR.push_back(rcr);
    }

}

void CleaningRobotWindow::setAllData()
{
    ui->rcr1SpeedEdit->setText( QString("%1").arg( Rclean.RCR.at(0).speed ) );
    ui->rcr1HeightEdit->setText( QString("%1").arg( Rclean.RCR.at(0).height ) );

    ui->rcr2SpeedEdit->setText( QString("%1").arg( Rclean.RCR.at(1).speed ) );
    ui->rcr2HeightEdit->setText( QString("%1").arg( Rclean.RCR.at(1).height ) );

    ui->rcr3SpeedEdit->setText( QString("%1").arg( Rclean.RCR.at(2).speed ) );
    ui->rcr3HeightEdit->setText( QString("%1").arg( Rclean.RCR.at(2).height ) );

    ui->rcr4SpeedEdit->setText( QString("%1").arg( Rclean.RCR.at(3).speed ) );
    ui->rcr4HeightEdit->setText( QString("%1").arg( Rclean.RCR.at(3).height ) );
}

QString CleaningRobotWindow::getStatus(int status)
{
    switch(status){
        case UP:
                return "UP";
                break;
        case DOWN:
                return "DOWN";
                break;
        case MOVEMOVE:
                return "MOVING";
                break;
        default :
               return "STOP";
               break;
    }
}

void CleaningRobotWindow::on_resetButton_clicked()
{

    ui->rcr1SpeedEdit->setText( "0" );
    ui->rcr1HeightEdit->setText( "0" );
    ui->rcr1CheckBox->setChecked(Qt::Unchecked);

    ui->rcr2SpeedEdit->setText( "0" );
    ui->rcr2HeightEdit->setText( "0" );
    ui->rcr2CheckBox->setChecked(Qt::Unchecked);

    ui->rcr3SpeedEdit->setText( "0" );
    ui->rcr3HeightEdit->setText( "0" );
    ui->rcr3CheckBox->setChecked(Qt::Unchecked);

    ui->rcr4SpeedEdit->setText( "0" );
    ui->rcr4HeightEdit->setText( "0" );
    ui->rcr4CheckBox->setChecked(Qt::Unchecked);

    ui->RStatusEdit->setText( " Your Robot is 0000!" );

}

void CleaningRobotWindow::on_okButton_clicked()
{
    QString str="";

    // get the choosen robots
    //          if ( ui->rcr1CheckBox->isChecked() )  {
    //                Rclean.RCR.at(0).status = MOVEMOVE;
    //            } else
    //            {
    //                Rclean.RCR.at(0).status = STOP;
    //            }
    //          if ( ui->rcr2CheckBox->isChecked() )  {
    //                Rclean.RCR.at(1).status = MOVEMOVE;
    //            } else
    //            {
    //                Rclean.RCR.at(1).status = STOP;
    //            }
    //          if ( ui->rcr3CheckBox->isChecked() )  {
    //                Rclean.RCR.at(2).status = MOVEMOVE;
    //            } else
    //            {
    //                Rclean.RCR.at(2).status = STOP;
    //            }
    //          if ( ui->rcr4CheckBox->isChecked() )  {
    //                Rclean.RCR.at(3).status = MOVEMOVE;
    //            } else
    //            {
    //                Rclean.RCR.at(3).status = STOP;
    //            }
    int i = 0;
    foreach ( QObject* ctrl  , ui->chooseRobotGroup->children())
    {
        str = QString::fromLatin1(ctrl->metaObject()->className());
        //str = str + QString::fromLatin1(ctrl->objectName());
        //printf( QString::fromLatin1(ctrl->metaObject()->className()).toStdString() );
        //QMessageBox::about(this,"about me", str);
        if( str == "QCheckBox")
        {
            QCheckBox* cb=(QCheckBox*)ctrl;
            if (cb->isChecked())
            {
                Rclean.RCR.at(i).status = MOVEMOVE;
            } else
            {
                Rclean.RCR.at(i).status = STOP;
            }
        }
        i++;
    }

    // get data from the lineEdits
    if ( Rclean.RCR.at(0).status == MOVEMOVE)
    {
        Rclean.RCR.at(0).speed =  ( ui->rcr1SpeedEdit->text( ) ).toFloat();
        Rclean.RCR.at(0).height = ( ui->rcr1HeightEdit->text( ) ).toFloat();
    }
    if ( Rclean.RCR.at(1).status == MOVEMOVE)
    {
        Rclean.RCR.at(1).speed =  ( ui->rcr2SpeedEdit->text( ) ).toFloat();
        Rclean.RCR.at(1).height = ( ui->rcr2HeightEdit->text( ) ).toFloat();
    }
    if ( Rclean.RCR.at(2).status == MOVEMOVE)
    {
        Rclean.RCR.at(2).speed =  ( ui->rcr3SpeedEdit->text( ) ).toFloat();
        Rclean.RCR.at(2).height = ( ui->rcr3HeightEdit->text( ) ).toFloat();
    }
    if ( Rclean.RCR.at(3).status == MOVEMOVE)
    {
        Rclean.RCR.at(3).speed =  ( ui->rcr4SpeedEdit->text( ) ).toFloat();
        Rclean.RCR.at(3).height = ( ui->rcr4HeightEdit->text( ) ).toFloat();
    }
    //update the robot direction
    str = "";
    for ( int i = 0; i < RCRNUM; i++)
    {
        if( Rclean.RCR.at(i).status == MOVEMOVE ){
            Rclean.RCR.at(i).status = Rclean.status;
            str = str + " RCR" + QString::number(i+1) + " ";
        }
    }
    //show the info
    //           if (str == ""){
    //               ui->RStatusEdit->setText( "no RCR is choosen!" );
    //           }else{
    //               ui->RStatusEdit->setText( str + "is " +  getStatus(Rclean.status) );
    //           }
    //dataArr.append(49);
    cleanBotInfo rclean;
    datapack.pack(Rclean);
    rclean = datapack.unpack();
    for ( int i =0; i < RCRNUM ; i++ )
    {
        QString str;
        str = str + "RCR " + QString::number( i+1) + " :\n " ;
        str = str + "status: ";
        str += QString::number( rclean.RCR.at(i).status );
        //str = str + "\n  ";
        str = str + "; speed: ";
        str += QString::number(rclean.RCR.at(i).speed);
        //str = str + "\n  ";
        str = str + "; height: ";
        str +=QString::number(rclean.RCR.at(i).height);
        //str = str + "\n  ";
        ui->RStatusEdit->append( str );
    }

    // send data
    sendRdata();
}



void CleaningRobotWindow::on_upButton_clicked()
{
    Rclean.status = UP;
    ui->RStatusEdit->append( " set direction UP; " );
}

void CleaningRobotWindow::on_downButton_clicked()
{
    Rclean.status = DOWN;
    ui->RStatusEdit->append( " set direction DOWN; " );
}

void CleaningRobotWindow::on_StopButton_clicked()
{
    Rclean.status = STOP;
    Rclean.speed = 0;
    for (int i = 0; i< RCRNUM; i++)
    {
        Rclean.RCR.at(i).speed = 0;
        Rclean.RCR.at(i).status = STOP;
    }
    sendRdata();
    ui->RStatusEdit->setText( " EMERGENCY STOP!!!" );
}

/**  serialOpenButton function: press open, set the serial port and  **/
void CleaningRobotWindow::on_serialOpenButton_clicked()
{
    if( ui->serialOpenButton->text() == tr("Open") )
        {
            //Rport.initPort();

            initSerialPort();
            //ui->serialOpenButton->setText(tr("Close"));
            setSerialSelectable();
            ui->RStatusEdit->setText(" open serial, pls choose the port info, and press the set button...");
        }
        else
        {
            Rport.clearSerialPort();
            setSerialNonSelectable();
            ui->RStatusEdit->setText(" close serial, byebye......");
        }
}

void CleaningRobotWindow::setSerialSelectable()
{
    ui->cmbDataBits->setDisabled(false);
    ui->cmbBaudRate->setDisabled(false);
    ui->cmbFlowControl->setDisabled(false);
    ui->cmbParity->setDisabled(false);
    ui->cmbPortName->setDisabled(false);
    ui->cmbStopBits->setDisabled(false);
    ui->serialOpenButton->setText(tr("Close"));
    ui->okButton->setEnabled(false);
}

void CleaningRobotWindow::setSerialNonSelectable()
{
    ui->cmbDataBits->setDisabled(true);
    ui->cmbBaudRate->setDisabled(true);
    ui->cmbFlowControl->setDisabled(true);
    ui->cmbParity->setDisabled(true);
    ui->cmbPortName->setDisabled(true);
    ui->cmbStopBits->setDisabled(true);
    ui->serialOpenButton->setText(tr("Open"));
    ui->okButton->setEnabled(true);
}

void CleaningRobotWindow::initSerialPort()
{
    Rport.readPortCOM();
    ui->cmbPortName->clear();
    ui->cmbPortName->addItems(Rport.portList);

    ui->cmbBaudRate->clear();
    ui->cmbBaudRate->addItems(Rport.baudList);
    ui->cmbBaudRate->setCurrentIndex(12);

    ui->cmbParity->clear();
    ui->cmbParity->addItems(Rport.parityList);
    ui->cmbParity->setCurrentIndex(0);

    ui->cmbDataBits->clear();
    ui->cmbDataBits->addItems(Rport.dataBitsList);
    ui->cmbDataBits->setCurrentIndex(3);

    ui->cmbStopBits->clear();
    ui->cmbStopBits->addItems(Rport.stopBitsList);
    ui->cmbStopBits->setCurrentIndex(0);

    //open button can be pressed
    ui->serialOpenButton->setCheckable(true);
}

void CleaningRobotWindow::sendRdata()
{
    if(Rport.isRserialOpen()){
    datapack.pack(Rclean);
    Rport.setSendBuff( datapack.getBuff() );
    Rport.writeComData();
    }else{
        qDebug()<<"Send error:  you don't set up your serialport";
    }
}

void CleaningRobotWindow::showDetailData()
{
    char* qbuff = Rport.getReceiveBuff().data();
    datapack.setBuff(qbuff);
    Rclean = datapack.unpack();
    ui->RCR1Height_detaildata->append( QString::number( Rclean.RCR.at(1).height ) );
    ui->RCR1Speed_detaildata->append( QString::number( Rclean.RCR.at(1).speed ) );
    ui->RCR2Height_detaildata->append( QString::number( Rclean.RCR.at(2).height ) );
    ui->RCR2Speed_detaildata->append( QString::number( Rclean.RCR.at(2).speed ) );
    ui->RCR3Height_detaildata->append( QString::number( Rclean.RCR.at(3).height ) );
    ui->RCR3Speed_detaildata->append( QString::number( Rclean.RCR.at(3).speed ) );
    ui->RCR4Height_detaildata->append( QString::number( Rclean.RCR.at(4).height ) );
    ui->RCR4Speed_detaildata->append( QString::number( Rclean.RCR.at(4).speed ) );
}

void CleaningRobotWindow::on_serialSetButton_clicked()
{
    Rport.setPortName( ui->cmbPortName->currentText() );
    Rport.setBaudRate( ui->cmbBaudRate->currentText().toInt() );
    Rport.setSerialPort();
    ui->RStatusEdit->append(" set the port successful..");
    //setSerialNonSelectable();
    //QObject::connect( Rport, SIGNAL( readComDataSlot(),   );
}

void CleaningRobotWindow::on_clearButton_clicked()
{
    ui->RStatusEdit->setText("");
}

void CleaningRobotWindow::on_clearRCR1Button_clicked()
{
    ui->RCR1Height_detaildata->setText("");
    ui->RCR1Speed_detaildata->setText("");
}

void CleaningRobotWindow::on_clearRCR2Button_clicked()
{
    ui->RCR2Height_detaildata->setText("");
    ui->RCR2Speed_detaildata->setText("");
}

void CleaningRobotWindow::on_clearRCR3Button_clicked()
{
    ui->RCR3Height_detaildata->setText("");
    ui->RCR3Speed_detaildata->setText("");
}

void CleaningRobotWindow::on_clearRCR4Button_clicked()
{
    ui->RCR4Height_detaildata->setText("");
    ui->RCR4Speed_detaildata->setText("");
}
