CONFIG += c++14
CONFIG += console

QT += core gui
QT += widgets

TARGET = ListViewDemo
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    ListView.cpp \
    CentralWidget.cpp

HEADERS  += MainWindow.hpp \
    ListView.hpp \
    CentralWidget.hpp \
    ListViewData.hpp \
    ListViewPrivateFunction.hpp
