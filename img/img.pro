TEMPLATE = app
SOURCES += main.cpp \
    window.cpp \
    view.cpp \
    filter.cpp \
    image.cpp \
    simplepocohandler.cpp

HEADERS += \
    window.hpp \
    view.hpp \
    filter.hpp \
    image.hpp \
    simplepocohandler.h

RESOURCES += \
    icons.qrc

QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11

QT += widgets core gui

#LIBS += -L/usr/local/lib -lSimpleAmqpClient



LIBS += -L/opt/appinf/lib -lPocoFoundation -lPocoNet

LIBS += -L/usr/local/lib -lamqpcpp

INCLUDEPATH += /usr/local/include/

INCLUDEPATH += /opt/appinf/include

