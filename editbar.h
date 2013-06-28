#ifndef EDITBAR_H
#define EDITBAR_H

#include <QFrame>
#include <QPushButton>
#include <QPrinter>

#include <QDebug>

#include "basictools.h"

//const QPixmap *image = p_parent->p_maxImage->pixmap();

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
public slots:
    void slots_rotateL();
    void slots_rotateR();
    void slots_effects();
    void slots_resize();

    void slots_undo();
    void slots_save();
    void slots_saveAs();

    void slots_print();

private:
    Ui::EditBar *ui;

    QPrinter printer;

    QPushButton* p_rotateRBtn;
    QPushButton* p_rotateLBtn;
    QPushButton* p_resizeBtn;
    QPushButton* p_effectBtn;

    QPushButton* p_undoBtn;
    QPushButton* p_saveBtn;
    QPushButton* p_saveAsBtn;

    QPushButton* p_printBtn;


    QPushButton* p_quitBtn;
    MainWindow*  p_parent;

    QRect self_;

    BasicTools* p_basicTools;
public:
    bool edited_;

    const QPixmap* getPixmap() const;
    void setPixmap(const QPixmap& pm);
};

#endif // EDITBAR_H
