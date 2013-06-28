

//#include "instruments/abstractinstrument.h"
//#include "instruments/pencilinstrument.h"
//#include "instruments/lineinstrument.h"
//#include "instruments/eraserinstrument.h"
//#include "instruments/rectangleinstrument.h"
//#include "instruments/ellipseinstrument.h"
//#include "instruments/fillinstrument.h"
//#include "instruments/sprayinstrument.h"
//#include "instruments/magnifierinstrument.h"
//#include "instruments/colorpickerinstrument.h"
//#include "instruments/selectioninstrument.h"
//#include "instruments/curvelineinstrument.h"
//#include "instruments/textinstrument.h"

//#include "effects/abstracteffect.h"
//#include "effects/negativeeffect.h"
//#include "effects/grayeffect.h"
//#include "effects/binarizationeffect.h"
//#include "effects/gaussianblureffect.h"
//#include "effects/gammaeffect.h"
//#include "effects/sharpeneffect.h"
//#include "effects/customeffect.h"

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
    p_parent(static_cast<MainWindow*>(this->parentWidget())),
    IsEdited(false)
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
    p_rotateRBtn->setGeometry(20, 30, 110, 30);
    p_rotateLBtn->setGeometry(125, 30, 45, 30);

    NewBtn(p_resizeBtn, "Resize");
    NewBtn(p_effectBtn, "Effects");
    p_resizeBtn->setGeometry(40, 85, 90, 30);
    p_effectBtn->setGeometry(40, 120, 90, 30);

    NewBtn(p_eff_gamma," Gamma");
    NewBtn(p_eff_gray," Gray");
    NewBtn(p_eff_binarize," Binarize");
    NewBtn(p_eff_gaussian," Gaussian");
    NewBtn(p_eff_sharpen," Sharpen");
    p_eff_gamma->setGeometry(10, 155, 70, 30);
    p_eff_gray->setGeometry(90, 155, 70, 30);
    p_eff_binarize->setGeometry(10, 190, 70, 30);
    p_eff_gaussian->setGeometry(90, 190, 70, 30);
    p_eff_sharpen->setGeometry(20, 225, 90, 30);

    p_slider = new QSlider(Qt::Horizontal, this);
    p_slider->setGeometry(10, 265, 110, 30);
    p_slider->setFont(font);
    p_slider->setPalette(palette);
    p_slider->setMaximumHeight(20);
    p_slider->setVisible(false);
    p_spinbox = new QSpinBox(this);
    p_spinbox->setGeometry(130, 260, 40, 30);
    p_spinbox->setFont(font);
    p_spinbox->setPalette(palette);
    p_spinbox->setVisible(false);
    connect(p_spinbox, SIGNAL(valueChanged(int)), p_slider, SLOT(setValue(int)));
    connect(p_slider, SIGNAL(valueChanged(int)), p_spinbox, SLOT(setValue(int)));

    NewBtn(p_eff_apply, "  Apply  ");
    NewBtn(p_undoBtn,   "  Undo  ");
    NewBtn(p_saveBtn,   " Save  ");
    NewBtn(p_saveAsBtn, "Save as");
    NewBtn(p_printBtn,  " Print ");
    NewBtn(p_quitBtn,   " Quit  ");
    p_eff_apply->setGeometry(30, self_.height() + 10,   110, 35);
    p_undoBtn->setGeometry  (30, self_.height() + 50,   110, 30);

    p_saveBtn->setGeometry  (20, self_.height() + 82,   60, 30);
    p_saveAsBtn->setGeometry(95, self_.height() + 82,   60, 30);
    p_printBtn->setGeometry (20, self_.height() + 122,  60, 30);
    p_quitBtn->setGeometry  (95, self_.height() + 122,  60, 30);


    this->disable_effectsBtns();
    connect(p_resizeBtn, SIGNAL(clicked()), this, SLOT(slot_resize()));
    connect(p_effectBtn, SIGNAL(clicked()), this, SLOT(slot_effects()));
    connect(p_rotateLBtn, SIGNAL(clicked()), this, SLOT(slot_rotateL()));
    connect(p_rotateRBtn, SIGNAL(clicked()), this, SLOT(slot_rotateR()));

    connect(p_saveBtn, SIGNAL(clicked()), this, SLOT(slot_save()));
    connect(p_undoBtn, SIGNAL(clicked()), this, SLOT(slot_undo()));
    connect(p_saveAsBtn, SIGNAL(clicked()), this, SLOT(slot_saveAs()));

    connect(p_printBtn, SIGNAL(clicked()), this, SLOT(slot_print()));
    connect(p_quitBtn, SIGNAL(clicked()),  this, SLOT(slot_quit()));
    connect(p_eff_apply, SIGNAL(clicked()), this, SLOT(slot_eff_apply()));
}
#undef NewBtn

EditBar::~EditBar() {
    delete ui;
}

void EditBar::slot_rotateL() {
    this->p_basicTools->rotateImage(true);
    this->IsEdited = true;
}
void EditBar::slot_rotateR() {
    this->p_basicTools->rotateImage(false);
    this->IsEdited = true;
}

void EditBar::slot_resize() {
    this->IsEdited = true;
}

void EditBar::slot_effects() {
    this->enable_effectsBtns();
}

void EditBar::slot_saveAs() {
  //  p_parent->resize(p_parent->geometry().width() - 30, p_parent->geometry().height());

    this->IsEdited = false;
}
void EditBar::slot_save() {
    this->IsEdited = false;
}

void EditBar::slot_undo() {
}

void EditBar::slot_print()
{
    if (IsEdited) {
            ;
    }
    else {
        do_print();
    }

}
void EditBar::do_print() {
    const QPixmap *image = p_parent->p_maxImage->pixmap();

    QPrintDialog printDialog(&printer_, this);
    if (printDialog.exec())
    {
        QPainter painter(&printer_);
        QRect rect = painter.viewport();
        QSize size = image->size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(image->rect());
        painter.drawPixmap(0, 0, *image);
    }
}
void EditBar::slot_quit() {
    if (IsEdited) {
        ;
    }
    else {
        this->setVisible(false);
    }
}
///////////////////////////////////////////////////////
void EditBar::slot_eff_gamma() {
    this->IsEdited = true;
    this->p_slider->setVisible(false);
    this->p_spinbox->setVisible(false);
}
void EditBar::slot_eff_gray() {
    this->IsEdited = true;
    this->p_slider->setVisible(false);
    this->p_spinbox->setVisible(false);
}

void EditBar::slot_binarize() {
    this->IsEdited = true;
    this->p_slider->setVisible(false);
    this->p_spinbox->setVisible(false);
}

void EditBar::slot_gaussian() {
    this->IsEdited = true;
    this->p_slider->setVisible(true);
    this->p_spinbox->setVisible(true);
}

void EditBar::slot_sharpen() {
    this->IsEdited = true;
    this->p_slider->setVisible(true);
    this->p_spinbox->setVisible(true);
}
void EditBar::slot_eff_apply() {
    this->IsEdited = false;
    this->p_slider->setVisible(false);
    this->p_spinbox->setVisible(false);
    this->disable_effectsBtns();
}
///////////////////////////////////////////////////////


void EditBar::enable_effectsBtns() {
    p_eff_gamma->setVisible(true);
    p_eff_gray->setVisible(true);
    p_eff_binarize->setVisible(true);
    p_eff_gaussian->setVisible(true);
    p_eff_sharpen->setVisible(true);
    connect(p_eff_gamma, SIGNAL(clicked()), this, SLOT(slot_eff_gamma()));
    connect(p_eff_gray, SIGNAL(clicked()), this, SLOT(slot_eff_gray()));
    connect(p_eff_binarize, SIGNAL(clicked()), this, SLOT(slot_binarize()));
    connect(p_eff_gaussian, SIGNAL(clicked()), this, SLOT(slot_gaussian()));
    connect(p_eff_sharpen, SIGNAL(clicked()), this, SLOT(slot_eff_sharpen()));
}

void EditBar::disable_effectsBtns() {
    p_eff_gamma->setVisible(false);
    p_eff_gray->setVisible(false);
    p_eff_binarize->setVisible(false);
    p_eff_gaussian->setVisible(false);
    p_eff_sharpen->setVisible(false);
    disconnect(p_eff_gamma, SIGNAL(clicked()), this, SLOT(slot_eff_gamma()));
    disconnect(p_eff_gray, SIGNAL(clicked()), this, SLOT(slot_eff_gray()));
    disconnect(p_eff_binarize, SIGNAL(clicked()), this, SLOT(slot_binarize()));
    disconnect(p_eff_gaussian, SIGNAL(clicked()), this, SLOT(slot_gaussian()));
    disconnect(p_eff_sharpen, SIGNAL(clicked()), this, SLOT(slot_eff_sharpen()));
}

const QPixmap* EditBar::getPixmap() const {
    return p_parent->p_maxImage->pixmap();
}
void EditBar::setPixmap(const QPixmap& pm) {
    p_parent->p_maxImage->setPixmap(pm);
}

