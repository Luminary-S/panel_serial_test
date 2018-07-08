#ifndef CLEANINGROBOTWINDOW_H
#define CLEANINGROBOTWINDOW_H

#include <QMainWindow>
#include <QList>
#include "datastruct.h"
#include "ropeclimbingrobot.h"
#include "datapack.h"
#include "rserialport.h"
#include "qdebug.h"

using namespace std;
namespace Ui {
class CleaningRobotWindow;
}

class CleaningRobotWindow : public QMainWindow
{
     Q_OBJECT

public:
    explicit CleaningRobotWindow(QWidget *parent = 0);
    ~CleaningRobotWindow();
   //std::vector<class ropeClimbingRobot> *RCR;
    void rcleanInit();
    void setAllData();


    QString getStatus(int);

    void setSerialNonSelectable();
    void setSerialSelectable();
    void initSerialPort();
    void sendRdata();
    void showDetailData();

private slots:
    void on_resetButton_clicked();

    void on_okButton_clicked();

    void on_upButton_clicked();

    void on_downButton_clicked();

    void on_StopButton_clicked();

    void on_serialOpenButton_clicked();

    void on_serialSetButton_clicked();

    void on_clearButton_clicked();

    void on_clearRCR1Button_clicked();

    void on_clearRCR2Button_clicked();

    void on_clearRCR3Button_clicked();

    void on_clearRCR4Button_clicked();

private:
    Ui::CleaningRobotWindow *ui;
    cleanBotInfo Rclean;
    DataPack  datapack;
    RserialPort Rport;

};
#endif // CLEANINGROBOTWINDOW_H
