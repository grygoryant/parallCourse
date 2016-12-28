#include <QApplication>
#include <unistd.h>
#include <sys/types.h>
#include <QDebug>
#include "window.hpp"
#include "simplepocohandler.h"

int main(int ac, char** av) {
    const char *secondProcName =
            "/Users/grigorii/Documents/build-CourseSecondProc-Desktop_Qt_5_7_0_clang_64bit-Debug/CourseSecondProc";

    pid_t pid = fork();
    if( pid == 0 ) {
        execvp( secondProcName, av );
    } else if ( pid > 0 ) {
        sleep(4);
        SimplePocoHandler handler("localhost", 5672);

        AMQP::Connection connection(&handler, AMQP::Login("guest", "guest"), "/");
        AMQP::Channel channel(&connection);

        channel.onReady([&]()
        {
            if(handler.connected())
            {
                struct lol {
                    int a;
                    double b;
                    std::string s;
                };

                lol payload;
                payload.a = 666;
                payload.b = 42.42;
                payload.s = "Loooooool duuuude!";

                AMQP::Envelope e( (const char *)&payload, sizeof(lol) );
                channel.publish("", "hello", e);
                qDebug() << " [x] Payload sent.";
                handler.quit();
            } else {
                qDebug() << "Lol1";
            }
        });

        handler.loop();

    } else {
        qDebug() << "Error in fork: " << errno;
        exit(1);
    }
    int status = 0;
    waitpid( 0, &status, WNOHANG );
    return 0;
//    QApplication app(ac, av);

//    Window win;
//    win.resize(600, 400);
//    win.show();

//    return app.exec();

}


//handler.loop();
