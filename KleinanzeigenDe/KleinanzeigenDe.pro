#-------------------------------------------------
#
# Project created by QtCreator 2018-05-12T11:52:58
#
#-------------------------------------------------

QT       += network core gui
TEMPLATE = lib
CONFIG += plugin
TARGET = KleinanzeigenDe
DESTDIR = /root/.local/share/AnzeigenChef/plugins/agents

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
