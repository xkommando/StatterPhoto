

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
