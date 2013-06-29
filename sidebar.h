//The MIT License (MIT)

//          this source is part of StatterPhto
//Copyright (c) 2013 Jack Yang, Bowen Cai, Liangpeng Zhou

//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:

//The above copyright notice and this permission notice shall be included in
//all copies or substantial portions of the Software.

//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//THE SOFTWARE.

#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QFrame>
#include <QPushButton>
#include <QString>
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
    void aboutBtnClicked();
    //void quitBtnClicked();

signals:
    void directoryChangedSignal(QString directoryPath);
    
private:
    Ui::SideBar *ui;

    QPushButton *p_returnBtn;
    QPushButton *p_openBtn;
    QPushButton *p_browseBtn;

    QPushButton *p_AboutBtn;
    QPushButton *p_QuitBtn;

    MainWindow *p_parent;
};

#endif // SIDEBAR_H
