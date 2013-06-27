#include "editbar.h"
#include "ui_editbar.h"

EditBar::EditBar(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::EditBar),
    p_parent(static_cast<MainWindow*>(this->parentWidget()))
{
    ui->setupUi(this);
    setStyleSheet("QFrame{border-image: url(:/images/sidebar_bg.png);}");
    QFont font = p_parent->getButtonFont();;
    QPalette palette = p_parent->getButtonPalette();

    this->self_ = geometry();
qDebug() << self_.height() << "   " << self_.width() << '\n';
//              300                         400
    p_undoBtn = new QPushButton(this);
    p_SaveBtn = new QPushButton(this);
    p_SaveAsBtn = new QPushButton(this);

    p_undoBtn->setGeometry(5, 5, 80, 35);
    p_SaveBtn->setGeometry(5, 40, 40, 35);
    p_SaveAsBtn->setGeometry(15, 75, 40, 35);

    p_undoBtn->setText("Undo    ");
    p_undoBtn->setFont(font);
    p_undoBtn->setPalette(palette);
    p_SaveBtn->setText("Save    ");
    p_SaveBtn->setFont(font);
    p_SaveBtn->setPalette(palette);
    p_SaveAsBtn->setText("Save as");
    p_SaveAsBtn->setFont(font);
    p_SaveAsBtn->setPalette(palette);

    p_undoBtn->setStyleSheet("QPushButton{border-image: url(:/images/btn_bg.png);}"
                                 "QPushButton:hover{border-image: url(:/images/bg.png);}"
                                 "QPushButton:pressed{border-image: url(:/images/bg.png);}");
    p_SaveBtn->setStyleSheet("QPushButton{border-image: url(:/images/btn_bg.png);}"
                                 "QPushButton:hover{border-image: url(:/images/bg.png);}"
                                 "QPushButton:pressed{border-image: url(:/images/bg.png);}");
    p_SaveAsBtn->setStyleSheet("QPushButton{border-image: url(:/images/btn_bg.png);}"
                                 "QPushButton:hover{border-image: url(:/images/bg.png);}"
                                 "QPushButton:pressed{border-image: url(:/images/bg.png);}");
    connect(p_SaveAsBtn, SIGNAL(clicked()), this, SLOT(slots_goBack()));
}

EditBar::~EditBar()
{
    delete ui;
}

void EditBar::slots_goBack() {
    p_parent->resize(p_parent->geometry().width() - 45, p_parent->geometry().height());
    this->setVisible(false);
}
