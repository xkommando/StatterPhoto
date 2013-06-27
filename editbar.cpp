#include "editbar.h"
#include "ui_editbar.h"



#undef NewBtn
#define NewBtn(name, text)\
    name = new QPushButton(this);\
    name->setText(text);\
    name->setFont(font);\
    name->setPalette(palette);\
    name->setStyleSheet("QPushButton{border-image: url(:/images/btn_bg.png);}"\
        "QPushButton:hover{border-image: url(:/images/bg.png);}"\
        "QPushButton:pressed{border-image: url(:/images/bg.png);}")


EditBar::EditBar(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::EditBar),
    p_parent(static_cast<MainWindow*>(this->parentWidget()))
{
    ui->setupUi(this);
    setStyleSheet("QFrame{border-image: url(:/images/sidebar_bg.png);}");
    QFont font = p_parent->getButtonFont();
    QPalette palette = p_parent->getButtonPalette();

    this->self_ = geometry();
//qDebug() << self_.height() << "   " << self_.width() << '\n';
//              300                         400

    NewBtn(p_rotateRBtn,"Rotate Right |");
    NewBtn(p_rotateLBtn,"Left");
    p_rotateRBtn->setGeometry(20, 30, 110, 40);
    p_rotateLBtn->setGeometry(125, 30, 45, 40);

    NewBtn(p_resizeBtn, "Resize");
    NewBtn(p_effectBtn, "Effects");
    p_resizeBtn->setGeometry(40, 80, 90, 40);
    p_effectBtn->setGeometry(40, 130, 90, 40);


    NewBtn(p_undoBtn,   "  Undo  ");
    NewBtn(p_SaveBtn,   " Save  ");
    NewBtn(p_SaveAsBtn, "Save as");
    p_undoBtn->setGeometry(40, self_.height() + 70, 90, 40);
    p_SaveBtn->setGeometry(20, self_.height() + 110, 60, 40);
    p_SaveAsBtn->setGeometry(95, self_.height() + 110, 60, 40);

    connect(p_SaveAsBtn, SIGNAL(clicked()), this, SLOT(slots_goBack()));
}
#undef NewBtn

EditBar::~EditBar()
{
    delete ui;
}

void EditBar::slots_goBack() {
  //  p_parent->resize(p_parent->geometry().width() - 30, p_parent->geometry().height());
    this->setVisible(false);
}
