#-------------------------------------------------
#
# Project created by QtCreator 2013-06-28T00:23:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StatterPhoto
TEMPLATE = app


SOURCES += \
    sidebar.cpp \
    maximageholder.cpp \
    mainwindow.cpp \
    main.cpp \
    editbar.cpp \
    bottombar.cpp \
    aboutbar.cpp

HEADERS  += \
    sidebar.h \
    maximageholder.h \
    mainwindow.h \
    editbar.h \
    bottombar.h \
    aboutbar.h

FORMS    += \
    sidebar.ui \
    editbar.ui \
    aboutbar.ui \
    bottombar.ui

OTHER_FILES += \
    photoviewer.ico \
    app.rc \
    _QtBigWork_.pro.user.a3b3f99 \
    _QtBigWork_.pro.user \
    _QtBigWork_.pro

RESOURCES += \
    resources.qrc
