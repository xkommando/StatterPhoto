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


#include "mainwindow.h"

#include "editbar.h"

#include "ui_editbar.h"


#undef NEW_BTN
#define NEW_BTN(name, text, x, y, w, h)\
    name = new QPushButton(this);\
    name->setText(text);\
    name->setFont(font);\
    name->setPalette(palette);\
    name->setStyleSheet("QPushButton{border-image: url(:/images/btn_bg.png);}"\
        "QPushButton:hover{border-image: url(:/images/bg.png);}"\
        "QPushButton:pressed{border-image: url(:/images/bg.png);}");\
    name->setGeometry(x, y, w, h)


EditBar::EditBar(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::EditBar),
    p_parent(static_cast<MainWindow*>(this->parentWidget())),
    IsEdited(false),
    HasSaved(true),
    pic_direction_(0),

    eff_bincoeff1(200),
    eff_bincoeff2(100)
{
    ui->setupUi(this);
    setStyleSheet("QFrame{border-image: url(:/images/sidebar_bg.png);}");
    setMouseTracking(true);

    QFont font = p_parent->getButtonFont();
    QPalette palette = p_parent->getButtonPalette();

  //  this->p_basicTools = new BasicTools(this);
    this->self_ = geometry();
//qDebug() << self_.height() << "   " << self_.width() << '\n';
//              300                         400

    NEW_BTN(p_rotateRBtn,"Rotate Right |",  20, 30, 110, 30);
    NEW_BTN(p_rotateLBtn,"Left",            125, 30, 45, 30);

    NEW_BTN(p_resizeBtn, "Resize",          40, 85, 90, 30);
    NEW_BTN(p_effectBtn, "Effects",         40, 120, 90, 30);

    NEW_BTN(p_eff_gamma," Gamma",       10, 155, 70, 30);
    NEW_BTN(p_eff_gray," Gray",         90, 155, 70, 30);
    NEW_BTN(p_eff_binarize," Binarize", 10, 190, 70, 30);
    NEW_BTN(p_eff_gaussian," Gaussian", 90, 190, 70, 30);
    NEW_BTN(p_eff_sharpen," Sharpen",   20, 225, 90, 30);

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

    NEW_BTN(p_eff_apply, "  Apply  ",   30, self_.height() + 10,   110, 35);
    NEW_BTN(p_undoBtn,   "  Undo  ",    30, self_.height() + 50,   110, 30);

    NEW_BTN(p_saveBtn,   " Save  ", 20, self_.height() + 82,   60, 30);
    NEW_BTN(p_saveAsBtn, "Save as", 95, self_.height() + 82,   60, 30);
    NEW_BTN(p_printBtn,  " Print ", 20, self_.height() + 122,  60, 30);
    NEW_BTN(p_quitBtn,   " Quit  ", 95, self_.height() + 122,  60, 30);

    this->disable_effectsBtns();
    connect(p_resizeBtn, SIGNAL(clicked()), this, SLOT(slot_resize()));
    connect(p_rotateLBtn, SIGNAL(clicked()), this, SLOT(slot_rotateL()));
    connect(p_rotateRBtn, SIGNAL(clicked()), this, SLOT(slot_rotateR()));

    connect(p_effectBtn, SIGNAL(clicked()), this, SLOT(slot_effects()));
    connect(p_eff_apply, SIGNAL(clicked()), this, SLOT(slot_eff_apply()));

    connect(p_saveBtn, SIGNAL(clicked()), this, SLOT(slot_save()));
    connect(p_undoBtn, SIGNAL(clicked()), this, SLOT(slot_undo()));
    connect(p_saveAsBtn, SIGNAL(clicked()), this, SLOT(slot_saveAs()));

    connect(p_printBtn, SIGNAL(clicked()), this, SLOT(slot_print()));
    connect(p_quitBtn, SIGNAL(clicked()),  this, SLOT(slot_quit()));
}
#undef NEW_BTN

EditBar::~EditBar() {
    delete ui;
}

void EditBar::slot_rotateL() {
    pic_direction_--;
    pic_direction_ = pic_direction_ == -4 ? 0: pic_direction_;
//qDebug() << pic_direction_ << '\n';
    QTransform trans;
    trans.rotate(90);
    setPixmap(getPixmap()->transformed(trans));
    if (0 != pic_direction_) {
        this->IsEdited = true;
        this->HasSaved = false;
    }
    else {
        this->IsEdited = false;
        this->HasSaved = true;
    }
}

void EditBar::slot_rotateR() {
    pic_direction_++;
    pic_direction_ = pic_direction_ == 4 ? 0: pic_direction_;
//qDebug() << pic_direction_ << '\n';
    QTransform trans;
    trans.rotate(-90);
    setPixmap(getPixmap()->transformed(trans));
    if (0 != pic_direction_) {
        this->IsEdited = true;
        this->HasSaved = false;
    }
    else {
        this->IsEdited = false;
        this->HasSaved = true;
    }
}

void EditBar::slot_resize() {
    this->p_slider->setVisible(true);
    this->p_spinbox->setVisible(true);
    currentHeight_ = getPixmap()->height();
    disconnect(p_slider, SIGNAL(valueChanged(int)),this, SLOT(do_sharpen(int)));
    disconnect(p_slider, SIGNAL(valueChanged(int)),this, SLOT(do_gaussian(int)));
    disconnect(p_slider, SIGNAL(valueChanged(int)),this, SLOT(do_gamma(int)));
    connect(p_slider, SIGNAL(valueChanged(int)),this, SLOT(do_resize(int)));

    image_ = getPixmap()->toImage();
    pixmap_ = getPixmap()->copy(getPixmap()->rect());
}
void EditBar::do_resize(int slider_value) {

    int max = p_slider->maximum();
    float ratio = (float)( max + slider_value) / max;

    setPixmap(getPixmap()->scaledToHeight(currentHeight_ * ratio));
//qDebug() << currentHeight_ << "   ratio: "<< ratio << '\n';
    this->IsEdited = true;
    this->HasSaved = false;
}

void EditBar::slot_effects() {
    p_eff_gamma->setVisible(true);
    p_eff_gray->setVisible(true);
    p_eff_binarize->setVisible(true);
    p_eff_gaussian->setVisible(true);
    p_eff_sharpen->setVisible(true);

    connect(p_eff_gamma, SIGNAL(clicked()), this, SLOT(slot_eff_gamma()));
    connect(p_eff_gray, SIGNAL(clicked()), this, SLOT(slot_eff_gray()));
    connect(p_eff_binarize, SIGNAL(clicked()), this, SLOT(slot_eff_binarize()));
    connect(p_eff_gaussian, SIGNAL(clicked()), this, SLOT(slot_eff_gaussian()));
    connect(p_eff_sharpen, SIGNAL(clicked()), this, SLOT(slot_eff_sharpen()));

    image_ = getPixmap()->toImage();
    pixmap_ = getPixmap()->copy(getPixmap()->rect());
}

///////////////////////////////////////////////////////
void EditBar::slot_eff_binarize() {
    this->IsEdited = true;
    this->p_slider->setVisible(false);
    this->p_spinbox->setVisible(false);

    for(int x = 0; x < image_.width(); x++) {
        for(int y = 0; y < image_.height(); y++) {
            QRgb pixel = image_.pixel(x, y);
            int r = qRed(pixel);
            r =
                r >= eff_bincoeff1 ? 0
                           : r >= eff_bincoeff2 && r < eff_bincoeff1 ? 255
                                        : 0;
            pixel = qRgb(r, r, r);
            image_.setPixel(x, y, pixel);
        }
    }
}
void EditBar::slot_eff_gray() {
    this->IsEdited = true;
    this->p_slider->setVisible(false);
    this->p_spinbox->setVisible(false);

    for(int x = 0; x < image_.width(); x++) {
        for(int y = 0; y < image_.height(); y++) {
            QRgb pixel = image_.pixel(x, y);
            int rgb = (int)(0.299 * qRed(pixel)
                            + 0.587 * qGreen(pixel)
                            + 0.114 * qBlue(pixel));
            pixel = qRgb(rgb, rgb, rgb);
            image_.setPixel(x, y, pixel);
        }
    }
}
///////////////////////////////////////////////////////
void EditBar::slot_eff_gamma() {
    this->IsEdited = true;
    this->p_slider->setVisible(true);
    this->p_spinbox->setVisible(true);

    disconnect(p_slider, SIGNAL(valueChanged(int)),this, SLOT(do_sharpen(int)));
    disconnect(p_slider, SIGNAL(valueChanged(int)),this, SLOT(do_gaussian(int)));
    disconnect(p_slider, SIGNAL(valueChanged(int)),this, SLOT(do_resize(int)));
    p_slider->setValue(0);
    connect(p_slider, SIGNAL(valueChanged(int)),this, SLOT(do_gamma(int)));
}

void EditBar::do_gamma(int slider_value) {
    double modificator = 3 * (double)slider_value / p_slider->maximum();
    for(int x = 0; x < image_.width(); x++) {
        for(int y = 0; y < image_.height(); y++) {
            QRgb pixel = image_.pixel(x, y);
            float r = qRed(pixel);
            r = 255 * pow(r / 255, modificator);
            float g = qGreen(pixel);
            g = 255 * pow(g / 255, modificator);
            float b = qBlue(pixel);
            b = 255 * pow(b / 255, modificator);
            image_.setPixel(x, y, qRgb(r, g, b));
        }
    }
}

void EditBar::slot_eff_gaussian() {
    this->IsEdited = true;
    this->p_slider->setVisible(true);
    this->p_spinbox->setVisible(true);
    disconnect(p_slider, SIGNAL(valueChanged(int)),this, SLOT(do_sharpen(int)));
    disconnect(p_slider, SIGNAL(valueChanged(int)),this, SLOT(do_resize (int)));
    disconnect(p_slider, SIGNAL(valueChanged(int)),this, SLOT(do_gamma(int)));
    p_slider->setValue(0);
    connect(p_slider, SIGNAL(valueChanged(int)),this, SLOT(do_gaussian(int)));
}
void EditBar::do_gaussian(int slider_value) {

    int intensity = 1 + slider_value * 6 / p_slider->maximum();

    matrix_ << 1 * intensity << 2 * intensity << 1 * intensity
           << 2 * intensity << 4 * intensity << 2 * intensity
           << 1 * intensity << 2 * intensity << 1 * intensity;

   // this->M_apply_matrix(matrix);
    connect(p_eff_apply, SIGNAL(clicked()), this, SLOT(slot_apply_matrix()));
}

void EditBar::slot_eff_sharpen() {
    this->p_slider->setVisible(true);
    this->p_spinbox->setVisible(true);
    disconnect(p_slider, SIGNAL(valueChanged(int)),this, SLOT(do_resize(int)));
    disconnect(p_slider, SIGNAL(valueChanged(int)),this, SLOT(do_gaussian(int)));
    disconnect(p_slider, SIGNAL(valueChanged(int)),this, SLOT(do_gamma(int)));
    p_slider->setValue(0);
    connect(p_slider, SIGNAL(valueChanged(int)),this, SLOT(do_sharpen(int)));
}
void EditBar::do_sharpen(int slider_value) {

    int intensity = 1 + slider_value * 8 / p_slider->maximum();
    this->matrix_ << 0            << -(intensity)        << 0
                  << -(intensity) << (intensity * 4) + 1 << -(intensity)
                  << 0            << -(intensity)        << 0;

//    this->M_apply_matrix(matrix_);
    connect(p_eff_apply, SIGNAL(clicked()), this, SLOT(slot_apply_matrix()));
}
//////////////////////////////////////////////////////////////////////////////////////////////
void EditBar::slot_eff_apply() {
    this->IsEdited = false;
    this->p_slider->setVisible(false);
    this->p_spinbox->setVisible(false);
    this->disable_effectsBtns();
    this->setPixmap(QPixmap::fromImage(image_));
}

void EditBar::slot_undo() {
    this->image_ = pixmap_.toImage();
    setPixmap(pixmap_);
}

void EditBar::disable_effectsBtns() {
    p_eff_gamma->setVisible(false);
    p_eff_gray->setVisible(false);
    p_eff_binarize->setVisible(false);
    p_eff_gaussian->setVisible(false);
    p_eff_sharpen->setVisible(false);
    disconnect(p_eff_gamma, SIGNAL(clicked()), this, SLOT(slot_eff_gamma()));
    disconnect(p_eff_gray, SIGNAL(clicked()), this, SLOT(slot_eff_gray()));
    disconnect(p_eff_binarize, SIGNAL(clicked()), this, SLOT(slot_eff_binarize()));
    disconnect(p_eff_gaussian, SIGNAL(clicked()), this, SLOT(slot_eff_gaussian()));
    disconnect(p_eff_sharpen, SIGNAL(clicked()), this, SLOT(slot_eff_sharpen()));
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditBar::slot_saveAs() {
  //  p_parent->resize(p_parent->geometry().width() - 30, p_parent->geometry().height());
    this->IsEdited = false;
}
void EditBar::slot_save() {
    this->IsEdited = false;
    this->HasSaved = true;
    QString fileName = p_parent->fileList.at(p_parent->currentPic).split('/').last();
//   // pixmap_.load(fileName);
//qDebug() << fileName << '\n';
//    image_ = getPixmap()->toImage();
    image_.save(fileName);
}

void EditBar::slot_print()
{
    if (IsEdited && HasSaved) {
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
    if (IsEdited && HasSaved) {
        ;
    }
    else {
        this->setVisible(false);
    }
}
void EditBar::mouseMoveEvent(QMouseEvent*) {
    p_parent->resetTimer();
}
const QPixmap* EditBar::getPixmap() const {
    return p_parent->p_maxImage->pixmap();
}
void EditBar::setPixmap(const QPixmap& pm) {
    p_parent->p_maxImage->setPixmap(pm);
}
//////////////////////////
QRgb EditBar::M_convolute_pixel(int x, int y, int kernalSz)
{
    double total = 0.0;
    double red = 0.0;
    double green = 0.0;
    double blue = 0.0;
    for(int r = -kernalSz / 2; r <= kernalSz / 2; ++r) {
        for(int c = -kernalSz / 2; c <= kernalSz / 2; ++c) {
            int kernalVal = this->matrix_[(kernalSz / 2 + r) * kernalSz + (kernalSz / 2 + c)];
            total += kernalVal;
            red += qRed(this->image_.pixel(x + c, y + r)) * kernalVal;
            green += qGreen(image_.pixel(x + c, y + r)) * kernalVal;
            blue += qBlue(image_.pixel(x + c, y + r)) * kernalVal;
        }
    }

    return( total < 0.0001 ?
            qRgb(qBound(0, qRound(red), 255),
                qBound(0, qRound(green), 255),
                qBound(0, qRound(blue), 255))
          : qRgb(qBound(0, qRound(red / total), 255),
                 qBound(0, qRound(green / total), 255),
                 qBound(0, qRound(blue / total), 255))
          );
}
// do not  calculate new image untill apply button is clicked
void EditBar::slot_apply_matrix() {

    int kernalSz = sqrt(this->matrix_.size());
    QImage image_tmp(image_);

    for(int i = 2; i < image_tmp.height() - 2; ++i) {
        for(int j = 2; j < image_tmp.width() - 2; ++j) {
            image_tmp.setPixel(j, i,
                 M_convolute_pixel(j, i, kernalSz));
        }
    }
    image_ = image_tmp;
    disconnect(p_eff_apply, SIGNAL(clicked()), this, SLOT(slot_apply_matrix()));
}
