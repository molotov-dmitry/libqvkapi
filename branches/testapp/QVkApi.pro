#-------------------------------------------------
#
# Project created by QtCreator 2016-03-22T20:29:14
#
#-------------------------------------------------

QT       += network webkitwidgets

TARGET = QVkApi
TEMPLATE = lib

INCLUDEPATH += include

DEFINES += QVKAPI_LIBRARY

SOURCES += src/qvkapi.cpp \
    src/qvkauthorizeview.cpp

HEADERS += include/qvkapi.h\
        include/qvkapi_global.h \
    include/qvkauthorizeview.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
