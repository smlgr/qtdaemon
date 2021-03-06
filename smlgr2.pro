TEMPLATE = app

CONFIG -= gui app_bundle
CONFIG += console

QT += core network sql
QT -= gui

TARGET = smlgr2

SOURCES += main.cpp \
    invertercomm.cpp \
    solarmaxlogger.cpp \
    sqlstorage.cpp \
    inverterdata.cpp \
    updatemobile.cpp

HEADERS += \
    invertercomm.hpp \
    config.hpp \
    solarmaxlogger.hpp \
    sqlstorage.hpp \
    inverterdata.hpp \
    updatemobile.hpp

QMAKE_CXXFLAGS += -std=c++0x
