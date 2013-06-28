#include "sidebar.h"
#include "ui_sidebar.h"
#include <QFont>
#include <QColor>
#include <QPalette>
#include <QFileDialog>
#include <QPrintDialog>
#include <QPainter>
#include <QRect>
#include <QSize>


SideBar::SideBar(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SideBar),
    p_parent(static_cast<MainWindow*>(this->parentWidget()))
{
    ui->setupUi(this);
    setStyleSheet("QFrame{border-image: url(:/images/sidebar_bg.png);}");


    p_returnBtn = new QPushButton(this);
    p_openBtn = new QPushButton(this);
    p_browseBtn = new QPushButton(this);

    p_AboutBtn = new QPushButton(this);
    p_QuitBtn = new QPushButton(this);

//    p_returnBtn->setGeometry(20, 20, 35, 35);
//    p_openBtn->setGeometry(0, 80, 140, 45);
//    p_browseBtn->setGeometry(0, 125, 140, 45);
//    p_AboutBtn->setGeometry(0, 170, 140, 45);
//    p_QuitBtn->setGeometry(0, 215, 140, 45);

    p_returnBtn->setGeometry(20, 20, 35, 35);
    p_openBtn->setGeometry(0, 85, 140, 45);
    p_browseBtn->setGeometry(0, 135, 140, 45);
    p_AboutBtn->setGeometry(0, 185, 140, 45);
    p_QuitBtn->setGeometry(0, 235, 140, 45);


    QFont font = p_parent->getButtonFont();;
    QPalette palette = p_parent->getButtonPalette();

    p_openBtn->setText("Open          ");
    p_openBtn->setFont(font);
    p_openBtn->setPalette(palette);

    p_browseBtn->setText("Browse       ");
    p_browseBtn->setFont(font);
    p_browseBtn->setPalette(palette);

    p_AboutBtn->setText("About         ");
    p_AboutBtn->setFont(font);
    p_AboutBtn->setPalette(palette);

    p_QuitBtn->setText("Quit           ");
    p_QuitBtn->setFont(font);
    p_QuitBtn->setPalette(palette);



    p_returnBtn->setStyleSheet("QPushButton{border-image: url(:/images/return.png);}"
                             "QPushButton:hover{border-image: url(:/images/return_on.png);}"
                             "QPushButton:pressed{border-image: url(:/images/return.png);}");
    p_openBtn->setStyleSheet("QPushButton{border-image: url(:/images/btn_bg.png);}"
                             "QPushButton:hover{border-image: url(:/images/bg.png);}"
                             "QPushButton:pressed{border-image: url(:/images/bg.png);}");
    p_browseBtn->setStyleSheet("QPushButton{border-image: url(:/images/btn_bg.png);}"
                             "QPushButton:hover{border-image: url(:/images/bg.png);}"
                             "QPushButton:pressed{border-image: url(:/images/bg.png);}");

    p_AboutBtn->setStyleSheet("QPushButton{border-image: url(:/images/btn_bg.png);}"
                             "QPushButton:hover{border-image: url(:/images/bg.png);}"
                             "QPushButton:pressed{border-image: url(:/images/bg.png);}");
    p_QuitBtn->setStyleSheet("QPushButton{border-image: url(:/images/btn_bg.png);}"
                             "QPushButton:hover{border-image: url(:/images/bg.png);}"
                             "QPushButton:pressed{border-image: url(:/images/bg.png);}");
    connect(p_returnBtn, SIGNAL(clicked()), this, SLOT(returnBtnClicked()));
    connect(p_openBtn, SIGNAL(clicked()), this, SLOT(openBtnClicked()));
    connect(p_browseBtn, SIGNAL(clicked()), this, SLOT(browseBtnClicked()));
    connect(p_AboutBtn, SIGNAL(clicked()), this, SLOT(aboutBtnClicked()));
    connect(p_QuitBtn, SIGNAL(clicked()), p_parent, SLOT(close()));
    connect(this, SIGNAL(directoryChangedSignal(QString)), p_parent, SLOT(loadImage(QString)));

}

SideBar::~SideBar()
{
    delete ui;
}

void SideBar::returnBtnClicked()
{
    this->setVisible(false);
}

void SideBar::browseBtnClicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                "/home",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    if(!dir.isEmpty())
    {
        emit directoryChangedSignal(dir);
    }
}

void SideBar::openBtnClicked()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open Image"), "/home",
                                                tr("Images(*.png *.xpm *.jpg)"));
    if (file != NULL)
    {
        QPixmap pixmap(file);
        p_parent->p_maxImage->setPixmap(pixmap);
        p_parent->p_maxImage->setVisible(true);
    }
}

void SideBar::aboutBtnClicked()
{
    p_parent->p_aboutBar->setVisible(true);
}





















