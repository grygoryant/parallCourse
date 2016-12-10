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
    image.hpp

RESOURCES += \
    icons.qrc

QMAKE_CXXFLAGS += -std=c++11
QT += widgets
