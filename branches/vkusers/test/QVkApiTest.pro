#-------------------------------------------------
#
# Project created by QtCreator 2016-03-22T22:10:33
#
#-------------------------------------------------

QT       += core gui network webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QVkApiTest
TEMPLATE = app

INCLUDEPATH += ../include

SOURCES += main.cpp\
        mainwindow.cpp \
    ../src/qvkauth.cpp \
    ../src/qvkauthview.cpp

HEADERS  += mainwindow.h \
    ../include/qvkapi_global.h \
    ../include/qvkauth.h \
    ../include/qvkauthview.h

FORMS    += mainwindow.ui

DEFINES += QVKAPI_TEST
