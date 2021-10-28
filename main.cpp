#include "mainwindow.h"

#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>
#include <windows.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pixmap(":/new/prefix1/Splash_1.png");
    QSplashScreen splasScreen(pixmap);
    splasScreen.show();
    a.processEvents();

    MainWindow w;

    Sleep(1000);
    splasScreen.finish(&w);

    w.show();
    return a.exec();
}
