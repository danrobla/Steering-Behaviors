#include "mainwindow.h"
#include "setupdialog.h"
#include "initialdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    InitialDialog id;

    if (id.exec() == 0)
    {
        exit(0);
    }

    SetupDialog d;

    if (d.exec() == 0)
    {
        exit(0);
    }

    MainWindow w;
    w.show();

    return a.exec();
}
