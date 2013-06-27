#ifndef BOTTOMBAR_H
#define BOTTOMBAR_H

#include <QFrame>
#include <QPushButton>
#include <QRect>

namespace Ui {
class BottomBar;
}

class BottomBar : public QFrame
{
    Q_OBJECT
    
public:
    explicit BottomBar(QWidget *parent = 0);
    ~BottomBar();
    
private:
    void initialChild();

    QRect g_bottomBarRect;

    Ui::BottomBar *ui;
    QPushButton* p_nextBtn;
    QPushButton* p_previousBtn;

};

#endif // BOTTOMBAR_H
