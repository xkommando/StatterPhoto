#include "mainwindow.h"
#include <QApplication>
#include <QRect>
#include <QPixmap>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowIcon(QIcon(QPixmap(":/resources/mydog.png")));

    w.resize(900,600);
    w.setMinimumSize(300,200);

    w.setP_MaxImage(argv[1]);
    int retVal = 0;
    try {
        w.show();
        retVal = a.exec();
    }
    catch(std::bad_alloc& mem_except) {
        qDebug() << " run out of memory " << mem_except.what() << '\n';
    }
    catch(std::exception& except) {
        qDebug() << except.what() << '\n';
    }
    catch(...) {
        qDebug() << " unknown exception \n";
    }
    return retVal;
}


