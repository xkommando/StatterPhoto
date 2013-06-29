//The MIT License (MIT)
//
//          this source is part of StatterPhto
//Copyright (c) 2013 Jack Yang, Bowen Cai, Liangpeng Zhou
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



#ifndef EDITBAR_H
#define EDITBAR_H

#include <QFrame>
#include <QPushButton>
#include <QButtonGroup>
#include <QSlider>
#include <QSpinBox>
#include <QPrinter>
#include <QDebug>
#include <QtCore/QTimer>
#include <QtGui/QImage>
#include <QtGui/QImageReader>
#include <QtGui/QImageWriter>
#include <QtGui/QUndoStack>
#include <QtGui/QFileDialog>
#include <QtGui/QTransform>

#include "basictools.h"

class AbstractInstrument;
class AbstractEffect;

namespace Ui {
class EditBar;
}
QT_BEGIN_NAMESPACE
class MainWindow;
QT_END_NAMESPACE

enum{Buttons_OffSet = 110};

class EditBar : public QFrame
{
    Q_OBJECT
    
public:
    explicit EditBar(QWidget *parent = 0);
    ~EditBar();

private:
    Ui::EditBar *ui;
    MainWindow*  p_parent;
    QRect self_;
    void mouseMoveEvent(QMouseEvent*);

public:

    bool IsEdited, HasSaved;
    int pic_direction_;
    int currentHeight_;
    QPixmap pixmap_;
    QImage  image_;
   // BasicTools*                 p_basicTools;
    QPrinter printer_;
public slots:
    void slot_rotateL();
    void slot_rotateR();
    void slot_effects();
    void slot_resize();

    void slot_undo();
    void slot_save();
    void slot_saveAs();

    void slot_print();
    void slot_quit();

    void slot_eff_gamma();
    void slot_eff_gray();
    void slot_eff_binarize();
    void slot_eff_gaussian();
    void slot_eff_sharpen();
    void slot_eff_apply();
private slots:
    void do_resize(int slider_value);
    void do_gamma(int slider_value);
    void do_gaussian(int slider_value);
    void do_sharpen(int slider_value);
    void do_print();
private:
    int eff_bincoeff1, eff_bincoeff2;
    void disable_effectsBtns();


    QPushButton* p_rotateRBtn;
    QPushButton* p_rotateLBtn;
    QPushButton* p_resizeBtn;
    QPushButton* p_effectBtn;
////////////////////////////////////////////////
    QPushButton* p_eff_gamma;
    QPushButton* p_eff_gray;
    QPushButton* p_eff_binarize;
    QPushButton* p_eff_gaussian;
    QPushButton* p_eff_sharpen;
    QPushButton* p_eff_apply;
   // QButtonGroup effects_buttons_;

    QSlider*     p_slider;
    QSpinBox*    p_spinbox;

    QPushButton* p_undoBtn;
    QPushButton* p_saveBtn;
    QPushButton* p_saveAsBtn;

    QPushButton* p_printBtn;

    QPushButton* p_quitBtn;

private:
    QList<double> matrix_;
public:
    QRgb M_convolute_pixel(int x, int y, int );
private slots:
    // do not calculate new image untill apply button is clicked
    void slot_apply_matrix();

public:
    const QPixmap* getPixmap() const;
    void setPixmap(const QPixmap& pm);
};

#endif // EDITBAR_H
