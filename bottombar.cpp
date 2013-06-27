#include "bottombar.h"
#include "ui_bottombar.h"

BottomBar::BottomBar(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::BottomBar)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet("QFrame{border-image: url(:/images/sidebar_bg.png);}");

    p_nextBtn = new QPushButton(this);
    p_previousBtn = new QPushButton(this);
    initialChild();

}

void BottomBar::initialChild()
{
    p_nextBtn->setStyleSheet("QPushButton{border-image: url(:/images/next.png);}"
                             "QPushButton:hover{border-image: url(:/images/next_on.png);}"
                             "QPushButton:pressed{border-image: url(:/images/next.png);}");

    p_previousBtn->setStyleSheet("QPushButton{border-image: url(:/images/previous.png);}"
                             "QPushButton:hover{border-image: url(:/images/previous_on.png);}"
                             "QPushButton:pressed{border-image: url(:/images/previous.png);}");

    //p_nextBtn->setGeometry(this->parentWidget()->width() / 2 - 10, 20, 30, 30);
    //p_previousBtn->setGeometry(this->parentWidget()->width() / 2 + 10, 20, 30, 30);


    int initWidth = g_bottomBarRect.width();
    int initHeight = g_bottomBarRect.height();


    p_nextBtn->setGeometry(0, 50, 75, 75);

}

BottomBar::~BottomBar()
{
    delete ui;
}
