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




#ifndef BASICTOOLS_H
#define BASICTOOLS_H

#include <QtCore/QObject>
#include <QtGui/QPixmap>
#include <QtGui/QPainter>
#include <QtGui/QLabel>
#include <QtGui/QTransform>
#include <QSize>
#include <QClipboard>
#include <QApplication>

QT_BEGIN_NAMESPACE
class EditBar;
QT_END_NAMESPACE
/**
 * @brief Class for implementation of additional tools which changing state of image.
 *
 */
class BasicTools : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     *
     * @param pImageArea A pointer to ImageArea.
     * @param parent Pointer for parent.
     */
    explicit BasicTools(QObject *parent = 0);
    ~BasicTools();

    /**
     * @brief Resize image area
     *
     * @param width
     * @param height
     */
  //  void resizeCanvas(int width, int height, bool flag = false);

    /**
     * @brief Resize image
     *
     */
  //  void resizeImage();

    /**
     * @brief Rotate image
     *
     * @param flag Left or right
     */
    void rotateImage(bool flag);
    /**
     * @brief Zoom image
     *
     * @param factor Scale factor
     * @return returns true in case of success
     */
   // bool zoomImage(qreal factor);
    
private:
  //  qreal mZoomedFactor; /**< Difference between original and current image */

    QPixmap  pixmap_;
    EditBar* p_parent;


//signals:
//    void sendNewImageSize(const QSize&);
    
//public slots:
    
};

#endif // BASICTOOLS_H
