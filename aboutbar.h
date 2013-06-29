//The MIT License (MIT)
//
//          this source is part of StatterPhto
//
//      Copyright (c) 2013 Jack Yang, Bowen Cai, Liangpeng Zhou
//
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

#ifndef ABOUTBAR_H
#define ABOUTBAR_H

#include <QFrame>
#include <QPushButton>
#include <QTextDocument>

namespace Ui {
class AboutBar;
}

class AboutBar : public QFrame
{
    Q_OBJECT
    
public:
    explicit AboutBar(QWidget *parent = 0);
    ~AboutBar();

public slots:
    void returnBtnClicked();
    
private:
    Ui::AboutBar *ui;

    QPushButton *p_returnBtn;
    //QTextDocument *p_textDoc;

    //QTextBrowser *p_textBrowser;
    //QLabel *p_label;
};

#endif // ABOUTBAR_H
