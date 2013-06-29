#ifndef MAXIMAGEHOLDER_H
#define MAXIMAGEHOLDER_H

#include <QLabel>


class MaxImageHolder : public QLabel
{
    Q_OBJECT
public:
    explicit MaxImageHolder(QWidget *parent = 0);

    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *ev);

private:
    //EditBar *p_editBar;

signals:
    void mouseMovedSignal();
    void mousePressedSignal();
    void mouseRightButtonClickedSignal();   
};

#endif // MAXIMAGEHOLDER_H
