#-------------------------------------------------
#
# Project created by QtCreator 2016-03-22T20:29:14
#
#-------------------------------------------------

QT       += network webkitwidgets

TARGET      = libqvkapi
TEMPLATE    = lib

OBJECTS_DIR = build/obj
RCC_DIR     = build/rcc
MOC_DIR     = build/moc
UI_DIR      = build/ui

INCLUDEPATH += include

DEFINES += QVKAPI_LIBRARY

SOURCES += \
    src/qvkauthview.cpp \
    src/qvkauth.cpp \
    src/qvkrequest.cpp \
    src/qvkrequestusers.cpp \
    src/qvkrequestalbums.cpp \
    src/qvkrequestphotos.cpp

HEADERS +=\
        include/qvkapi_global.h \
    include/qvkauthview.h \
    include/qvkauth.h \
    include/qvkrequest.h \
    include/qvkuserinfo.h \
    include/qvkrequestusers.h \
    include/qvkrequestalbums.h \
    include/qvkalbuminfo.h \
    include/qvkinfophoto.h \
    include/qvkrequestphotos.h

unix {
    target.path = /usr/local/lib
    INSTALLS += target
}
