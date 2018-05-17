QT       += network core gui
TEMPLATE = lib
CONFIG += plugin
TARGET = KleinanzeigenDe

macx{
    DESTDIR = $$PWD/../build/release/macos
}

win32{
    DESTDIR = $$PWD\\..\\build\\release\\windows
}

linux{
    DESTDIR = $$PWD/../build/release/linux
}

DEFINES += KLEINANZEIGENDE_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        kleinanzeigende.cpp

HEADERS += \
        kleinanzeigende.h \
    searchagentinterface.h

DISTFILES += \
    KleinanzeigenDe.json
