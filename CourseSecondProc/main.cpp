#include <QCoreApplication>
#include <QApplication>
#include <QDebug>
#include <unistd.h>
#include <zmq.hpp>
#include <iostream>
#include <QPixmap>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>

using namespace boost::interprocess;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_PAIR);

    socket.connect ("tcp://localhost:5555");

    zmq::message_t request;
    socket.recv (&request);
    std::string rpl = std::string(static_cast<char*>(request.data()), request.size());

    file_mapping mFile( rpl.c_str(), read_only );
    mapped_region region( mFile, read_only );

    uchar *addr = static_cast<uchar *>( region.get_address() );
    std::size_t size = region.get_size();

    qDebug() << "Recv: " << rpl.size() << addr << size << addr[0];

    QPixmap pic;
    pic.loadFromData( addr, size );
    qDebug() << pic.size() << pic.colorCount();

    return app.exec();
}
