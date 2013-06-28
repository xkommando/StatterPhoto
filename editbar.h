
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


//    inline QString getFileName() { return filePath_.split('/').last(); }
//    inline QImage* getImage() { return image_; }
//    inline void setImage(const QImage &image) { *image_ = image; }

public:
//    QImage *image_,  /**< Main image. */
//           _imageCopy; /**< Copy of main image, need for events. */ // ?????????????

//    QString filePath_; /**< Path where located image. */


    bool IsEdited, IsPaint, IsResize, IsRightButtonPressed;
//    QPixmap *pixmap_;
//  //  QCursor *mCurrentCursor;
//  //  qreal mZoomFactor;

    BasicTools*                 p_basicTools;
//    QUndoStack*                 p_undoStack;
//    QVector<AbstractInstrument*> vec_instrumentsHandlers;
//    AbstractInstrument*         p_instrumentHandler;
//    QVector<AbstractEffect*>    vec_effectsHandlers;
//    AbstractEffect*             p_effectHandler;


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
    void slot_binarize();
    void slot_gaussian();
    void slot_sharpen();
    void slot_eff_apply();

private:

    MainWindow*  p_parent;
    QRect self_;

    void do_print();


    Ui::EditBar *ui;

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
    void enable_effectsBtns();
    void disable_effectsBtns();
   // QButtonGroup effects_buttons_;

    QSlider*     p_slider;
    QSpinBox*    p_spinbox;

    QPushButton* p_undoBtn;
    QPushButton* p_saveBtn;
    QPushButton* p_saveAsBtn;

    QPushButton* p_printBtn;


    QPushButton* p_quitBtn;

public:

    const QPixmap* getPixmap() const;
    void setPixmap(const QPixmap& pm);
};

#endif // EDITBAR_H
