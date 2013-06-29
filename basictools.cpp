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





#include "basictools.h"
#include "editbar.h"


BasicTools::BasicTools(QObject *parent) :
    QObject(parent),
    p_parent(static_cast<EditBar*>(parent)) {

   // pixmap_ = * (p_parent->getPixmap());
}

BasicTools::~BasicTools()
{}

void BasicTools::rotateImage(bool flag)
{
    QTransform transform;
    if(flag)
    {
        transform.rotate(90);
    }
    else
    {
        transform.rotate(-90);
    }

    p_parent->setPixmap(p_parent->getPixmap()->transformed(transform));

  //  QRect currentPixmapRect= p_parent->getPixmap()->rect();
//    p_parent->setPixmap(p_parent->getPixmap()->rect().right() + 6,
//                        );
    p_parent->update();
//    mPImageArea->setImage(mPImageArea->getImage()->transformed(transform));
//    mPImageArea->resize(mPImageArea->getImage()->rect().right() + 6,
//                        mPImageArea->getImage()->rect().bottom() + 6);
//    mPImageArea->update();
//    mPImageArea->setEdited(true);
//    mPImageArea->clearSelection();
}
//void BasicTools::resizeImage()
//{
//    ResizeDialog resizeDialog(mPImageArea->getImage()->size());
//    if(resizeDialog.exec() == QDialog::Accepted)
//    {
//        mPImageArea->setImage(mPImageArea->getImage()->scaled(resizeDialog.getNewSize()));
//        mPImageArea->resize(mPImageArea->getImage()->rect().right() + 6,
//                            mPImageArea->getImage()->rect().bottom() + 6);
//        mPImageArea->setEdited(true);
//        mPImageArea->clearSelection();
//    }
//}


//bool BasicTools::zoomImage(qreal factor)
//{
//    mZoomedFactor *= factor;
//    if(mZoomedFactor < 0.25)
//    {
//        mZoomedFactor = 0.25;
//        return false;
//    }
//    else if(mZoomedFactor > 4)
//    {
//        mZoomedFactor = 4;
//        return false;
//    }
//    else
//    {
//        mPImageArea->setImage(mPImageArea->getImage()->transformed(QTransform::fromScale(factor, factor)));
//        mPImageArea->resize((mPImageArea->rect().width())*factor, (mPImageArea->rect().height())*factor);
//        emit sendNewImageSize(mPImageArea->size());
//        mPImageArea->setEdited(true);
//        mPImageArea->clearSelection();
//        return true;
//    }
//}

//void BasicTools::resizeCanvas(int width, int height, bool flag)
//{
//    if(flag)
//    {
//        ResizeDialog resizeDialog(QSize(width, height));
//        if(resizeDialog.exec() == QDialog::Accepted)
//        {
//            QSize newSize = resizeDialog.getNewSize();
//            width = newSize.width();
//            height = newSize.height();
//        }
//    }

//    if(width < 1 || height < 1)
//        return;
//    QImage *tempImage = new QImage(width, height, QImage::Format_ARGB32_Premultiplied);
//    QPainter painter(tempImage);
//    painter.setPen(Qt::NoPen);
//    painter.setBrush(QBrush(Qt::white));
//    painter.drawRect(QRect(0, 0, width, height));
//    painter.drawImage(0, 0, *mPImageArea->getImage());
//    painter.end();

//    mPImageArea->setImage(*tempImage);

//    mPImageArea->resize(mPImageArea->getImage()->rect().right() + 6,
//                        mPImageArea->getImage()->rect().bottom() + 6);
//    mPImageArea->setEdited(true);
//    mPImageArea->clearSelection();
//}
