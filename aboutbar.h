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
