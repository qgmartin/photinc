#include <QApplication>
#include <QSplashScreen>
#include "coordinatedialog.h"

#ifdef WIN32
    #include <windows.h>
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setOverrideCursor(Qt::WaitCursor);

    QSplashScreen photo;

    QString info("<h2><font color=white>PhotInc %1</font></h2>");
    photo.setPixmap(QPixmap(":/images/spain.png"));
    photo.show();
    photo.showMessage(info.arg(VERSION), Qt::AlignCenter);

#ifdef WIN32
    Sleep(2000);
#else
    sleep(2);
#endif

    coordinateDialog coordinate;
    coordinate.show();

    photo.hide();
    QApplication::restoreOverrideCursor();
    return a.exec();
}
