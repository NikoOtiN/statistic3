#-------------------------------------------------
#
# Project created by QtCreator 2014-10-30T22:25:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS += -std=c++11
TARGET = 3labOEDGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    user_func.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../Qwt-6.1.1/lib/ -lqwt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../Qwt-6.1.1/lib/ -lqwtd
else:unix: LIBS += -L$$PWD/../../../../../Qwt-6.1.1/lib/ -lqwt

INCLUDEPATH += $$PWD/../../../../../Qwt-6.1.1/include
DEPENDPATH += $$PWD/../../../../../Qwt-6.1.1/include
