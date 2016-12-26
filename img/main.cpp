#include <QApplication>
#include "window.hpp"
#include "simplepocohandler.h"

int main(int ac, char** av) {
    QApplication app(ac, av);

    Window win;
    win.resize(600, 400);
    win.show();

    return app.exec();
}
