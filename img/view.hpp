#ifndef VIEW_HPP
#define VIEW_HPP

#include <QWidget>

class QLabel;
class QScrollArea;

class View : public QWidget {
    Q_OBJECT

public:
    View(QWidget* parent = 0);

    QPixmap currentImage() const;

public slots:
    void setImage(const QPixmap& img);

    void setScale(double scale);

private:
    QLabel* tImg;
    QScrollArea* tScroll;
    double tScale;
};

#endif // VIEW_HPP
