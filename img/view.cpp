#include "view.hpp"
#include "filter.hpp"
#include <QScrollArea>
#include <QLabel>
#include <QHBoxLayout>

View::View(QWidget *parent)
    : QWidget(parent), tScale(1)
{
    QHBoxLayout* lout = new QHBoxLayout(this);
    lout->setMargin(0);

    tScroll = new QScrollArea;
    lout->addWidget(tScroll);
    tScroll->setAlignment(Qt::AlignCenter);

    tImg = new QLabel;
    tScroll->setWidget(tImg);
    tImg->setScaledContents(true);
}

QPixmap View::currentImage() const {
    if (tImg->pixmap())
        return *tImg->pixmap();
    return QPixmap();
}

void View::setImage(const QPixmap &img) {
    tImg->setPixmap(img);
    tImg->resize(img.size() * tScale);
}

void View::setScale(double scale) {
    if (scale < 0) return;
    if (!tImg->pixmap()) return;

    if (scale == 0) {
        QSize fitSize = tScroll->maximumViewportSize();
        QSize imgSize = tImg->pixmap()->size();
        double imgRatio = double(imgSize.width()) / imgSize.height();

        if (fitSize.width() < fitSize.height()) {
            int h = int(fitSize.width() / imgRatio);
            if (h > fitSize.height()) {
                scale = double(fitSize.height()) / imgSize.height();
            }
            else {
                scale = double(fitSize.width()) / imgSize.width();
            }
        }
        else {
            int w = int(fitSize.height() * imgRatio);
            if (w > fitSize.width()) {
                scale = double(fitSize.width()) / imgSize.width();
            }
            else {
                scale = double(fitSize.height()) / imgSize.height();
            }
        }
    }

    tImg->resize(tImg->pixmap()->size() * scale);
    tScale = scale;
}
