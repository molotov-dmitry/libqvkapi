#-------------------------------------------------
#
# Project created by QtCreator 2016-03-22T20:29:14
#
#-------------------------------------------------

QT       += network webkitwidgets

TARGET = QVkApi
TEMPLATE = lib

unix: QMAKE_POST_LINK += bash $$shell_path($$_PRO_FILE_PWD_)/make_lib.sh

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
    target.path = /usr/lib
    INSTALLS += target
}
