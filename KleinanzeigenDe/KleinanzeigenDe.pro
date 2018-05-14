#-------------------------------------------------
#
# Project created by QtCreator 2018-05-12T11:52:58
#
#-------------------------------------------------

QT       += network core gui
TEMPLATE = lib
CONFIG += plugin
TARGET = KleinanzeigenDe

# This Part is only for debugging on our development
CONFIG(release, debug|release) {
    macx{
        DESTDIR = $$PWD/../build/release/macos
    }

    win32{
        DESTDIR = $$PWD\\..\\build\\release\\windows
    }

    linux{
        DESTDIR = $$PWD/../build/release/linux
    }
}

CONFIG(debug, debug|release) {
    macx{
        DESTDIR = $$PWD/../build/debug/macos
    }

    win32{
        DESTDIR = $$PWD\\..\\build\\debug\\windows
    }

    linux{
        DESTDIR = $$PWD/../build/debug/linux
    }
}

DEFINES += KLEINANZEIGENDE_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        kleinanzeigende.cpp

HEADERS += \
        kleinanzeigende.h \
    searchagentinterface.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    KleinanzeigenDe.json
