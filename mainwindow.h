#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <windows.h>
#include <windowsx.h>
#include <QtGui>
#include <QPushButton>
#include <QRect>
#include <QString>
#include <QImage>
#include <QListWidget>
#include <QListWidgetItem>
#include <QTimer>
#include <maximageholder.h>

#include <QFont>
#include <QColor>
#include <QPalette>

#include "editbar.h"
#include "aboutbar.h"

#include "sidebar.h"

struct ScaledImageInfo
{
    QImage m_ScaledImage;
    QString m_ScaledImagePath;
};

class SideBar;
class EditBar;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QStringList filter;
    QStringList fileList;
    SideBar *p_siderBar;
    EditBar *p_editBar;
    AboutBar *p_aboutBar;
    MaxImageHolder *p_maxImage;

    void setP_MaxImage(QString fileUrl);


    //void clearAll();
   // void sendMessage();
public slots:
    void max();
    void normal();
    void homeClicked();
    void returnClicked();
    void loadImage(QString);
    void showImageOnWall();
    void ItemDoubleClicked(QListWidgetItem * item);
    void showNextPic();
    void showPreviousPic();
    void resetTimer();
    void hideWidgets();
    void showWidgets();
    void showEditBar();
signals:
    void loadedImageSignal();
    //void showedImageSignal();


protected:
    void paintEvent(QPaintEvent *);
    bool winEvent(MSG *message, long *result);

private:
    void drawWindowShadow(QPainter &p);
    void setInitStyle();
    void setDisplayStyle();
    QStringList getFileList(QString directoryPath);

    bool b_isWidgetsHided;
    int currentPic;

    QTimer *p_timer;
    QRect g_mainWindowRect;

    QPushButton *p_closeBtn;
    QPushButton *p_minBtn;
    QPushButton *p_maxBtn;
    QPushButton *p_homeBtn;
    QPushButton *p_returnBtn;
    QPushButton *p_nextBtn;
    QPushButton *p_previousBtn;

    QListWidget *p_ListWidget;

protected:
    QFont m_font;
    QPalette m_palette;

public:
    const QFont& getButtonFont() const;

    const QPalette& getButtonPalette() const;
};

#endif // MAINWINDOW_H
















