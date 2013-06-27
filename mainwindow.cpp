#include "mainwindow.h"
#include "maximageholder.h"

const int W_ICONSIZE = 160; //图片宽度
const int H_ICONSIZE = 100; //图片高度

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //////////////////////////
    m_font.setStyleHint(QFont::SansSerif);
    m_font.setPixelSize(16);
    m_palette.setColor(QPalette::ButtonText, QColor(240, 240, 240));
    //////////////////////////
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setMinimumSize(45,45);

    b_isWidgetsHided = false;
    p_timer = new QTimer(this);
   // p_maxImage = new QLabel(this);
    p_maxImage = new MaxImageHolder(this);
    p_closeBtn = new QPushButton(this);
    p_minBtn = new QPushButton(this);
    p_maxBtn = new QPushButton(this);

    p_homeBtn = new QPushButton(this);
    p_returnBtn = new QPushButton(this);
    p_siderBar = new SideBar(this);
    p_editBar = new EditBar(this);
    p_aboutBar = new AboutBar(this);
    //p_bottomBar = new BottomBar(this);
    p_nextBtn = new QPushButton(this);
    p_previousBtn = new QPushButton(this);
    p_ListWidget = new QListWidget(this);

    //设置QListWidget中的单元项的图片大小
    p_ListWidget->setIconSize(QSize(W_ICONSIZE, H_ICONSIZE));
    p_ListWidget->setResizeMode(QListView::Adjust);
    //设置QListWidget的显示模式
    p_ListWidget->setViewMode(QListView::IconMode);
    //设置QListWidget中的单元项不可被拖动
    p_ListWidget->setMovement(QListView::Static);
    //设置QListWidget中的单元项的间距
    p_ListWidget->setSpacing(36);

    p_ListWidget->setVisible(false);
    p_aboutBar->setVisible(false);
    //p_siderBar->setVisible(false);
    p_maxImage->setVisible(false);
    p_returnBtn->setVisible(false);
    //p_bottomBar->setVisible(false);
    p_nextBtn->setVisible(false);
    p_previousBtn->setVisible(false);

    setInitStyle();

    connect(p_timer, SIGNAL(timeout()), this, SLOT(hideWidgets()));
    connect(p_closeBtn, SIGNAL(clicked()), this, SLOT(close()));
    connect(p_maxBtn, SIGNAL(clicked()), this, SLOT(max()));
    connect(p_minBtn, SIGNAL(clicked()), this, SLOT(showMinimized()));
    connect(p_homeBtn, SIGNAL(clicked()), this, SLOT(homeClicked()));
    connect(p_returnBtn, SIGNAL(clicked()), this, SLOT(returnClicked()));
    connect(p_nextBtn, SIGNAL(clicked()), this, SLOT(showNextPic()));

    connect(p_previousBtn, SIGNAL(clicked()), this, SLOT(showPreviousPic()));
    connect(this, SIGNAL(loadedImageSignal()), this, SLOT(showImageOnWall()));
}

MainWindow::~MainWindow()
{

}
void MainWindow::setInitStyle()
{
    p_closeBtn->setStyleSheet("QPushButton{border-image: url(:/images/close.png);}"
                             "QPushButton:hover{border-image: url(:/images/close_on.png);}"
                             "QPushButton:pressed{border-image: url(:/images/close.png);}");

    p_minBtn->setStyleSheet("QPushButton{border-image: url(:/images/min.png);}"
                             "QPushButton:hover{border-image: url(:/images/min_on.png);}"
                             "QPushButton:pressed{border-image: url(:/images/min.png);}");

    p_maxBtn->setStyleSheet("QPushButton{border-image: url(:/images/max.png);}"
                             "QPushButton:hover{border-image: url(:/images/max_on.png);}"
                             "QPushButton:pressed{border-image: url(:/images/max.png);}");
    p_homeBtn->setStyleSheet("QPushButton{border-image: url(:/images/home.png);}"
                             "QPushButton:hover{border-image: url(:/images/home_on.png);}"
                             "QPushButton:pressed{border-image: url(:/images/home.png);}");

    p_returnBtn->setStyleSheet("QPushButton{border-image: url(:/images/return.png);}"
                             "QPushButton:hover{border-image: url(:/images/return_on_2.png);}"
                             "QPushButton:pressed{border-image: url(:/images/return.png);}");
    p_ListWidget->setStyleSheet("QListWidget{border-image: url(:/images/bg.png);}");

    p_nextBtn->setStyleSheet("QPushButton{border-image: url(:/images/next.png);}"
                             "QPushButton:hover{border-image: url(:/images/next_on.png);}"
                             "QPushButton:pressed{border-image: url(:/images/next.png);}");

    p_previousBtn->setStyleSheet("QPushButton{border-image: url(:/images/previous.png);}"
                             "QPushButton:hover{border-image: url(:/images/previous_on.png);}"
                             "QPushButton:pressed{border-image: url(:/images/previous.png);}");
}

void MainWindow::setDisplayStyle()
{
    p_closeBtn->setStyleSheet("QPushButton{border-image: url(:/images/close.png);}"
                             "QPushButton:hover{border-image: url(:/images/close_on_2.png);}"
                             "QPushButton:pressed{border-image: url(:/images/close.png);}");

    p_minBtn->setStyleSheet("QPushButton{border-image: url(:/images/min.png);}"
                             "QPushButton:hover{border-image: url(:/images/min_on_2.png);}"
                             "QPushButton:pressed{border-image: url(:/images/min.png);}");

    p_maxBtn->setStyleSheet("QPushButton{border-image: url(:/images/max.png);}"
                             "QPushButton:hover{border-image: url(:/images/max_on_2.png);}"
                             "QPushButton:pressed{border-image: url(:/images/max.png);}");
}

void MainWindow::max()
{
    this->showMaximized();
    p_maxBtn->setStyleSheet("QPushButton{border-image: url(:/images/restore.png);}"
                             "QPushButton:hover{border-image: url(:/images/restore_on_2.png);}"
                             "QPushButton:pressed{border-image: url(:/images/restore.png);}");
    disconnect(p_maxBtn, SIGNAL(clicked()), this, SLOT(max()));
    connect(p_maxBtn, SIGNAL(clicked()), this, SLOT(normal()));
}

void MainWindow::normal()
{
    this->showNormal();
    p_maxBtn->setStyleSheet("QPushButton{border-image: url(:/images/max.png);}"
                             "QPushButton:hover{border-image: url(:/images/max_on_2.png);}"
                             "QPushButton:pressed{border-image: url(:/images/max.png);}");
    disconnect(p_maxBtn, SIGNAL(clicked()), this, SLOT(normal()));
    connect(p_maxBtn, SIGNAL(clicked()), this, SLOT(max()));
}

void MainWindow::homeClicked()
{
    p_siderBar->setVisible(true);
}

void MainWindow::returnClicked()
{
    p_homeBtn->setVisible(true);
    p_ListWidget->setVisible(true);
    p_returnBtn->setVisible(false);
    p_maxImage->setVisible(false);
    setInitStyle();
}

void MainWindow::ItemDoubleClicked(QListWidgetItem *item)
{
    if(!item)
    {
        return;
    }
    int nRowIndex = p_ListWidget->row(item);
    currentPic = nRowIndex;
    QString strUrl = fileList[nRowIndex];
    QPixmap objPixmap(strUrl);
    p_maxImage->setPixmap(objPixmap);
    p_maxImage->setAlignment(Qt::AlignCenter);

    p_maxImage->setVisible(true);
    p_returnBtn->setVisible(true);
    p_nextBtn->setVisible(true);
    p_previousBtn->setVisible(true);
    p_siderBar->setVisible(false);
    p_ListWidget->setVisible(false);
    p_homeBtn->setVisible(false);
//////////////////////////////
   // connect(p_editBar, SIGNAL(mouseMovedSignal()), this, SLOT(resetTimer()));
   // connect(p_editBar, SIGNAL(mousePressedSignal()), this, SLOT(resetTimer()));
/////////////////////////////////

    connect(p_maxImage, SIGNAL(mouseMovedSignal()), this, SLOT(resetTimer()));
    connect(p_maxImage, SIGNAL(mousePressedSignal()), this, SLOT(resetTimer()));
    connect(p_maxImage, SIGNAL(mousePressedSignal()), this, SLOT(showNextPic()));
    connect(p_maxImage, SIGNAL(mouseRightButtonClickedSignal()), this, SLOT(showEditBar()));

    setDisplayStyle();
    p_timer->start(3000);
}

void MainWindow::showNextPic()
{
    if (currentPic == fileList.count() - 1)
    {
        currentPic = 0;
    }
    else
    {
        currentPic++;
    }
    QString strUrl = fileList[currentPic];
    QPixmap objPixmap(strUrl);
    p_maxImage->setPixmap(objPixmap);
    p_maxImage->setAlignment(Qt::AlignCenter);
}

void MainWindow::showPreviousPic()
{
    if (currentPic == 0)
    {
        currentPic = fileList.count() - 1;
    }
    else
    {
        currentPic--;
    }
    QString strUrl = fileList[currentPic];
    QPixmap objPixmap(strUrl);
    p_maxImage->setPixmap(objPixmap);
    p_maxImage->setAlignment(Qt::AlignCenter);
}

void MainWindow::resetTimer()
{
    if (b_isWidgetsHided)
    {
        showWidgets();
        p_timer->start(3000);
        connect(p_timer, SIGNAL(timeout()), this, SLOT(hideWidgets()));
    }
    p_timer->start();
}


void MainWindow::showWidgets()
{
    if (b_isWidgetsHided)
    {
        p_returnBtn->setVisible(true);
        p_maxBtn->setVisible(true);
        p_minBtn->setVisible(true);
        p_closeBtn->setVisible(true);
        p_nextBtn->setVisible(true);
        p_previousBtn->setVisible(true);
        b_isWidgetsHided = false;
    }
}

void MainWindow::hideWidgets()
{
    if (!b_isWidgetsHided)
    {
        p_returnBtn->setVisible(false);
        p_maxBtn->setVisible(false);
        p_minBtn->setVisible(false);
        p_closeBtn->setVisible(false);
        p_nextBtn->setVisible(false);
        p_previousBtn->setVisible(false);
        b_isWidgetsHided = true;
    }

}


void MainWindow::showImageOnWall()
{
    p_ListWidget->clear();
    p_ListWidget->setVisible(true);
    for(int i = 0; i < fileList.count(); ++i)
    {
        //获得图片路径
        QString strPath = fileList[i];
        //生成图像objPixmap
        QPixmap objPixmap(strPath);
        //生成QListWidgetItem对象
        QListWidgetItem *pItem = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(W_ICONSIZE,H_ICONSIZE))), "");
        //设置单元项的宽度和高度
        pItem->setSizeHint(QSize(W_ICONSIZE,H_ICONSIZE));
        //connect(pItem,)
        p_ListWidget->insertItem(i, pItem);
    }
    //emit showedImageSignal();
    p_siderBar->setVisible(false);
    p_maxImage->setVisible(false);
    connect(p_ListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
           this, SLOT(ItemDoubleClicked(QListWidgetItem*)));


}
void MainWindow::showEditBar()
{
    this->resize(geometry().width() + 45, geometry().height());
    p_editBar->setVisible(true);
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QColor bgColor(40, 40, 40);

    if(this->width() > 45 && this->height() > 45)
        drawWindowShadow(p);

    p.setPen(Qt::NoPen);
    p.setBrush(bgColor);
    p.drawRoundedRect(QRect(9,9,this->width() - 18,this->height() - 18),2.0f,2.0f);


    g_mainWindowRect = geometry();

    int initWidth = g_mainWindowRect.width();
    int initHeight = g_mainWindowRect.height();

    p_closeBtn->setGeometry(initWidth - 35, 10, 25, 25);
    p_maxBtn->setGeometry(initWidth - 60, 10, 25, 25);
    p_minBtn->setGeometry(initWidth - 85, 10, 25, 25);
    p_homeBtn->setGeometry(50, 50, 50, 50);
    p_siderBar->setGeometry(9, 9, 140, initHeight - 30);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // p_editBar->setGeometry(9, initHeight - 109, initWidth - 18, 200);
    //                       x              y    w       h
    p_editBar->setGeometry(initWidth - 180, 45, 145, initHeight - 110);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    p_aboutBar->setGeometry(9, 9, 300, initHeight - 18);
   // p_bottomBar->setGeometry(9, initHeight - 209, initWidth - 18, 200);
    p_ListWidget->setGeometry(160, 50, initWidth - 180, initHeight - 70);
    p_maxImage->setGeometry(9, 9, initWidth - 18, initHeight - 18);
    p_returnBtn->setGeometry(30, 30, 60, 60);

    p_nextBtn->setGeometry(initWidth - 60, initHeight - 50, 25, 25);
    p_previousBtn->setGeometry(initWidth - 100, initHeight - 50, 25, 25);

}

void MainWindow::drawWindowShadow(QPainter &p)
{
    QList<QPixmap> pixmaps;
    pixmaps.append(QPixmap(":/resources/shadow_left.png"));
    pixmaps.append(QPixmap(":/resources/shadow_right.png"));
    pixmaps.append(QPixmap(":/resources/shadow_top.png"));
    pixmaps.append(QPixmap(":/resources/shadow_bottom.png"));
    pixmaps.append(QPixmap(":/resources/shadow_corner1.png"));
    pixmaps.append(QPixmap(":/resources/shadow_corner2.png"));
    pixmaps.append(QPixmap(":/resources/shadow_corner3.png"));
    pixmaps.append(QPixmap(":/resources/shadow_corner4.png"));

    p.drawPixmap(0,0,10,10,pixmaps[4]);
    p.drawPixmap(this->width() - 10,0,10,10,pixmaps[5]);
    p.drawPixmap(0,this->height() - 10,10,10,pixmaps[6]);
    p.drawPixmap(this->width() - 10,this->height() - 10,10,10,pixmaps[7]);

    p.drawPixmap(0,10,10,this->height() - 20,pixmaps[0].scaled(10,this->height() - 20));
    p.drawPixmap(this->width() - 10,10,10,this->height() - 20,pixmaps[1].scaled(10,this->height() - 20));
    p.drawPixmap(10,0,this->width() - 20,10,pixmaps[2].scaled(this->width() - 20,10));
    p.drawPixmap(10,this->height() - 10,this->width() - 20,10,pixmaps[3].scaled(this->width() - 20,10));
}

bool MainWindow::winEvent(MSG *message, long *result)
{
    switch(message->message)
    {
    case WM_NCHITTEST:
        int xPos = GET_X_LPARAM(message->lParam) - this->frameGeometry().x();
        int yPos = GET_Y_LPARAM(message->lParam) - this->frameGeometry().y();

        if ((12 < xPos && xPos < this->width() - 12 && 30 < yPos
              && yPos < this->height() - 12)
            || (this->width() - 85 < xPos && xPos < this->width() - 12
                && 12 < yPos && yPos < 30))
        {
            return false;
        }
        else
        {
            if (12 < xPos && xPos < this->width() - 85 && 0 < yPos && yPos < 30)
            {
                *result = HTCAPTION;
            }
            if(xPos > 4 && xPos < 12)
                *result = HTLEFT;
            if(xPos > (this->width() - 12) && xPos < (this->width() - 8))
                *result = HTRIGHT;
            if(yPos > 8 && yPos < 12)
                *result = HTTOP;
            if(yPos > (this->height() - 12) && yPos < (this->height() - 8))
                *result = HTBOTTOM;
            if(xPos > 8 && xPos < 12 && yPos > 8 && yPos < 12)
                *result = HTTOPLEFT;
            if(xPos > (this->width() - 12) && xPos < (this->width() - 8) && yPos > 8 && yPos < 12)
                *result = HTTOPRIGHT;
            if(xPos > 8 && xPos < 12 && yPos > (this->height() - 12) && yPos < (this->height() - 8))
                *result = HTBOTTOMLEFT;
            if(xPos > (this->width() - 12) && xPos < (this->width() - 8) && yPos > (this->height() - 12) && yPos < (this->height() - 8))
                *result = HTBOTTOMRIGHT;
            return true;

        }

    }

    return false;
}

void MainWindow::loadImage(QString directoryPath)
{
    QDir dir(directoryPath);

    filter << "*.jpg" << "*.png" << "*.bmp" << "*.gif" << "*.jpeg" << "*.pbm" << "*.xmp" << "*.xbm";

    fileList = dir.entryList (filter, QDir::Files);
    for (int i=0; i < fileList.count(); ++i)
    {
        fileList[i] = dir.path() + QString("/") + fileList.at(i);
    }

    if (!fileList.isEmpty())
    {
        emit loadedImageSignal();
        return;
    }
}

QStringList MainWindow::getFileList(QString directoryPath)
{
    QDir dir(directoryPath);

    filter << "*.jpg" << "*.png" << "*.bmp" << "*.gif" << "*.jpeg" << "*.pbm" << "*.xmp" << "*.xbm";

    fileList = dir.entryList (filter, QDir::Files);

    foreach (QString subDir, dir.entryList(QDir::Dirs|QDir::NoDotAndDotDot))
    {
        fileList += getFileList(directoryPath + QDir::separator() + subDir);
    }
}

void MainWindow::setP_MaxImage(QString fileUrl)
{
    p_siderBar->setVisible(false);
    p_editBar->setVisible(false);
    p_maxImage->setVisible(true);
    QPixmap image(fileUrl);
    p_maxImage->setPixmap(image);
    p_maxImage->setAlignment(Qt::AlignCenter);

}

//////////////////////////////
const QFont& MainWindow::getButtonFont() const {
    return this->m_font;
}

const QPalette& MainWindow::getButtonPalette() const {
    return this->m_palette;
}














