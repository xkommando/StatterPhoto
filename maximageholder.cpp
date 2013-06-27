#include "maximageholder.h"
#include <QMouseEvent>

MaxImageHolder::MaxImageHolder(QWidget *parent) :
    QLabel(parent)
{
    setMouseTracking(true);
}

void MaxImageHolder::mouseMoveEvent(QMouseEvent *ev)
{
    emit mouseMovedSignal();
}

void MaxImageHolder::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton)
    {

        if (ev->x() > 50 && ev->x() < this->width() - 9 && ev->y() > 30 && ev->y() < this->height() - 9)
        {
            emit mousePressedSignal();
            ev->accept();

        }
    }
    if (ev->button() == Qt::RightButton)
    {
        emit mouseRightButtonClickedSignal();
    }

}
