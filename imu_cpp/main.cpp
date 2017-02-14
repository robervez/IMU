#include "mainwindow.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindowVA w;
    w.Init();
    w.show();
    return a.exec();
}
