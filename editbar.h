#ifndef EDITBAR_H
#define EDITBAR_H

#include <QFrame>
#include <QPushButton>
#include <QDebug>
#include "mainwindow.h"

namespace Ui {
class EditBar;
}

class MainWindow;

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
private:
    Ui::EditBar *ui;

    QPushButton* p_undoBtn;

    QPushButton* p_rotateRBtn;
    QPushButton* p_rotateLBtn;
    QPushButton* p_resizeBtn;
    QPushButton* p_effectBtn;

    QPushButton* p_SaveBtn;
    QPushButton* p_SaveAsBtn;

//    QPushButton* p_

    QRect self_;

    MainWindow *p_parent;
};

#endif // EDITBAR_H
