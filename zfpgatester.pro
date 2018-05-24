QT += core
QT += network
QT -= gui
QT += simplecmdiobase

TARGET = zfpgatester
CONFIG += console
CONFIG -= app_bundle
# for old compilers
CONFIG += c++11

TEMPLATE = app

SOURCES += \
    main.cpp \
    cmdparserzfpgatest.cpp \
    cmdhandlerzfpgatest.cpp

HEADERS += \
    cmdparserzfpgatest.h \
    cmdhandlerzfpgatest.h \
    globals.h

target.path = /usr/bin
INSTALLS += target

exists(localpaths.user.pri) {
    include(localpaths.user.pri)
}

VERSION = 0.0.1
DEFINES += APP_VERSION=\\\"$$VERSION\\\"
