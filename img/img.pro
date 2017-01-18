TEMPLATE = app
SOURCES += main.cpp \
    window.cpp \
    view.cpp \
    filter.cpp \
    image.cpp

HEADERS += \
    window.hpp \
    view.hpp \
    filter.hpp \
    image.hpp \
    message.h

RESOURCES += \
    icons.qrc

QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11

QT += widgets core gui

LIBS += -L/usr/local/lib -lzmq

INCLUDEPATH += /usr/local/include

