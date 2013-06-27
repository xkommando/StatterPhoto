#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QFrame>
#include <QPushButton>
#include <QString>
#include <QPrinter>
#include <QRect>

#include "mainwindow.h"

namespace Ui {
class SideBar;
}

class MainWindow;
class SideBar : public QFrame
{
    Q_OBJECT
    
public:
    explicit SideBar(QWidget *parent = 0);
    ~SideBar();
public slots:
    void returnBtnClicked();
    void openBtnClicked();
    void browseBtnClicked();
//    void saveBtnClicked();
//    void saveAsBtnClicked();
    void printBtnClicked();
    void aboutBtnClicked();
    //void quitBtnClicked();

signals:
    void directoryChangedSignal(QString directoryPath);
    
private:
    Ui::SideBar *ui;

    QPrinter printer;

    QPushButton *p_returnBtn;
    QPushButton *p_openBtn;
    QPushButton *p_browseBtn;

    QPushButton *p_PrintBtn;
    QPushButton *p_AboutBtn;
    QPushButton *p_QuitBtn;

    MainWindow *p_parent;
};

#endif // SIDEBAR_H
