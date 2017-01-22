#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <QMainWindow>
#include <zmq.hpp>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>

using namespace boost::interprocess;

class QListWidget;
class QComboBox;
class View;
struct Image;

class Window : public QMainWindow {
    Q_OBJECT

public:
    Window(QWidget* parent = 0);
    ~Window();

public slots:
    void openImage();
    void saveImage();
    void processImage();

private slots:
    void scaleImage(int ix);
    void setCurrent(int ix);

protected:
    virtual void resizeEvent(QResizeEvent*);

private:
    View* tView;
    QComboBox* tScale;
    QListWidget* tList;

    zmq::context_t context;
    zmq::socket_t socket;

    void setImage(const QPixmap& p);

    void loadImageToShMem( const QString &fileName );
    void loadImageFromShMem();
    void detachShMem();

    QList<Image*> tImgs;
};

#endif // WINDOW_HPP
