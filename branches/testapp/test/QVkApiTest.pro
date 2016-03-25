#-------------------------------------------------
#
# Project created by QtCreator 2016-03-22T22:10:33
#
#-------------------------------------------------

QT       += core gui network webkitwidgets sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QVkApiTest
TEMPLATE = app

INCLUDEPATH += ../include

SOURCES += main.cpp\
        mainwindow.cpp \
    ../src/qvkapi.cpp \
    ../src/qvkauthorizeview.cpp \
    accountinfo.cpp \
    dialogautent.cpp \
    dialogauthorize.cpp \
    settings.cpp

HEADERS  += mainwindow.h \
    ../include/qvkapi_global.h \
    ../include/qvkapi.h \
    ../include/qvkauthorizeview.h \
    accountinfo.h \
    dialogautent.h \
    dialogauthorize.h \
    settings.h

FORMS    += mainwindow.ui \
    dialogautent.ui \
    dialogauthorize.ui

DEFINES += QVKAPI_TEST
