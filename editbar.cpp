


#include "mainwindow.h"

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

    this->p_basicTools = new BasicTools(this);
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


    NewBtn(p_undoBtn,   "    Undo  ");
    NewBtn(p_saveBtn,   " Save  ");
    NewBtn(p_saveAsBtn, "Save as");
    NewBtn(p_printBtn,  "    Print ");

    p_undoBtn->setGeometry  (30, self_.height() + 50,   110, 30);
    p_saveBtn->setGeometry  (20, self_.height() + 82,   60, 30);
    p_saveAsBtn->setGeometry(95, self_.height() + 82,   60, 30);
    p_printBtn->setGeometry (30, self_.height() + 122,  110, 30);

    connect(p_resizeBtn, SIGNAL(clicked()), this, SLOT(slots_resize()));
    connect(p_effectBtn, SIGNAL(clicked()), this, SLOT(slots_effects()));
    connect(p_rotateLBtn, SIGNAL(clicked()), this, SLOT(slots_rotateL()));
    connect(p_rotateRBtn, SIGNAL(clicked()), this, SLOT(slots_rotateR()));

    connect(p_saveBtn, SIGNAL(clicked()), this, SLOT(slots_save()));
    connect(p_undoBtn, SIGNAL(clicked()), this, SLOT(slots_undo()));
    connect(p_saveAsBtn, SIGNAL(clicked()), this, SLOT(slots_saveAs()));

    connect(p_printBtn, SIGNAL(clicked()), this, SLOT(slots_print()));
}
#undef NewBtn

EditBar::~EditBar() {
    delete ui;
}

void EditBar::slots_rotateL() {
    this->p_basicTools->rotateImage(true);
}
void EditBar::slots_rotateR() {
    this->p_basicTools->rotateImage(false);
}

void EditBar::slots_resize() {

}
void EditBar::slots_effects() {

}
void EditBar::slots_saveAs() {
  //  p_parent->resize(p_parent->geometry().width() - 30, p_parent->geometry().height());
    this->setVisible(false);
}
void EditBar::slots_save() {

}
void EditBar::slots_undo() {

}

void EditBar::slots_print()
{
    const QPixmap *image = p_parent->p_maxImage->pixmap();

    QPrintDialog printDialog(&printer, this);
    if (printDialog.exec())
    {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = image->size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(image->rect());
        painter.drawPixmap(0, 0, *image);
    }
}

const QPixmap* EditBar::getPixmap() const {
    return p_parent->p_maxImage->pixmap();
}
void EditBar::setPixmap(const QPixmap& pm) {
    p_parent->p_maxImage->setPixmap(pm);
}

