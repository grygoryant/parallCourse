QT += widgets core gui

CONFIG += c++11

TARGET = CourseSecondProc
#CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \

LIBS += -L/usr/local/lib -lzmq

INCLUDEPATH += /usr/local/include

INCLUDEPATH += /Volumes/Toshiba/grigorii/Documents/parallCourse/img

HEADERS += \
    ../parallCourse/img/message.h \
    ../img/message.h


