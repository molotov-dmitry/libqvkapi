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
    ../src/qvkauth.cpp \
    ../src/qvkauthview.cpp \
    accountinfo.cpp \
    dialogautent.cpp \
    dialogauthorize.cpp \
    settings.cpp \
    dialogsettings.cpp

HEADERS  += mainwindow.h \
    ../include/qvkapi_global.h \
    ../include/qvkauth.h \
    ../include/qvkauthview.h \
    accountinfo.h \
    dialogautent.h \
    dialogauthorize.h \
    settings.h \
    dialogsettings.h

FORMS    += mainwindow.ui \
    dialogautent.ui \
    dialogauthorize.ui \
    dialogsettings.ui

DEFINES += QVKAPI_TEST

RESOURCES += \
    res/resource.qrc