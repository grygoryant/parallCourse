#include <QCoreApplication>
#include <QApplication>
#include <QDebug>
#include <unistd.h>
#include <zmq.hpp>
#include <iostream>
#include <QPixmap>
#include <sys/mman.h>
#include "message.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_PAIR);

    std::cout << "Connecting to hello world server..." << std::endl;
    socket.connect ("tcp://localhost:5555");

    zmq::message_t request;
    uchar *addr = nullptr;
    //socket.recv(&request);
    socket.recv(&addr, sizeof(addr));

    qint64 imgSize = 0;
    socket.recv(&imgSize, sizeof(imgSize));

    qDebug() << "Recv: " << addr << imgSize;

//    QPixmap src;
//    src.loadFromData( addr, imgSize );
//    if (src.isNull()) {
//        qDebug() << "fileName";
//    }



    return app.exec();
}
