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

SOURCES += \
    src/qvkauthview.cpp \
    src/qvkauth.cpp

HEADERS +=\
        include/qvkapi_global.h \
    include/qvkauthview.h \
    include/qvkauth.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
