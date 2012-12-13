#-------------------------------------------------
#
# Project created by QtCreator 2012-12-05T15:19:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtBoats
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        QtBoats.cpp \
    PlayArea.cpp \
    PlayField.cpp \
    GameState.cpp

HEADERS  += QtBoats.h \
    PlayArea.h \
    PlayField.h \
    Table2D.h \
    GameState.h
