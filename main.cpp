#include "cleaningrobotwindow.h"
#include <QApplication>
#include "ropeclimbingrobot.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CleaningRobotWindow w;

    w.show();

    return a.exec();
}
