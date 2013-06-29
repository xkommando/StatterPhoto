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
    aboutbar.cpp \
    basictools.cpp

HEADERS  += \
    sidebar.h \
    maximageholder.h \
    mainwindow.h \
    editbar.h \
    aboutbar.h \
    basictools.h

FORMS    += \
    sidebar.ui \
    editbar.ui \
    aboutbar.ui

OTHER_FILES += \
    photoviewer.ico \
    app.rc \
    Liscense.txt

RESOURCES += \
    resources.qrc
