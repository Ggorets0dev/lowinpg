#include "mainwindow.h"

#include <QDebug>
#include <QApplication>
#include <QString>
#include <QStyle>
#include <QDesktopWidget>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow main_window;

    main_window.setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            main_window.size(),
            qApp->desktop()->availableGeometry()
        )
    );

    main_window.show();
    return a.exec();
}
