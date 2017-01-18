#include <QApplication>
#include <unistd.h>
#include <sys/types.h>
#include <QDebug>
#include "window.hpp"


int main(int ac, char** av) {
    const char *secondProcName =
            "/Users/grigorii/Documents/build-CourseSecondProc-Desktop_Qt_5_7_0_clang_64bit-Debug/CourseSecondProc";

    pid_t pid = fork();
    if( pid == 0 ) {
        execv( secondProcName, av );
    } else if ( pid > 0 ) {
        QApplication app(ac, av);

        Window win;
        win.resize(600, 400);
        win.show();

        return app.exec();
    } else {
        qDebug() << "Error in fork.";
        exit(1);
    }

//    int status = 0;
//    waitpid( pid, &status, 0 );

    return 0;
}
