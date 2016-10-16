#-------------------------------------------------
#
# Project created by QtCreator 2016-03-22T22:10:33
#
#-------------------------------------------------

QT       += core gui network webkitwidgets sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QVkApiTest
TEMPLATE = app

INCLUDEPATH += ../include data dialogs pages widgets

SOURCES += main.cpp\
        mainwindow.cpp \
    ../src/qvkauth.cpp \
    ../src/qvkauthview.cpp \
    ../src/qvkrequestusers.cpp \
    ../src/qvkrequest.cpp \
    dialogs/dialogautent.cpp \
    dialogs/dialogauthorize.cpp \
    dialogs/dialogsettings.cpp \
    pages/vkpagewidget.cpp \
    pages/vkpageuser.cpp \
    data/accountinfo.cpp \
    data/imagecache.cpp \
    data/settings.cpp \
    widgets/vkimagewidget.cpp \
    data/metadata.cpp

HEADERS  += mainwindow.h \
    ../include/qvkapi_global.h \
    ../include/qvkauth.h \
    ../include/qvkauthview.h \
    ../include/qvkrequestusers.h \
    ../include/qvkuserinfo.h \
    ../include/qvkrequest.h \
    dialogs/dialogautent.h \
    dialogs/dialogauthorize.h \
    dialogs/dialogsettings.h \
    pages/vkpageuser.h \
    pages/vkpagewidget.h \
    data/accountinfo.h \
    data/imagecache.h \
    data/settings.h \
    data/resicons.h \
    widgets/vkimagewidget.h \
    data/metadata.h

FORMS    += mainwindow.ui \
    dialogs/dialogautent.ui \
    dialogs/dialogauthorize.ui \
    dialogs/dialogsettings.ui \
    pages/vkpageuser.ui

DEFINES += QVKAPI_TEST

RESOURCES += \
    res/resource.qrc
