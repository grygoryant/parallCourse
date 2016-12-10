#include "image.hpp"
#include "filter.hpp"

void Image::setImage(const QPixmap& img) {
    makeGray(img.toImage().convertToFormat(QImage::Format_RGB32), tImgF);
    QImage i;
    makeImage(tImgF, img.width(), i);
    tImg = QPixmap::fromImage(i);
}

void Image::setImage(const std::vector<float>& img, int width) {
    tImgF = img;
    QImage i;
    makeImage(tImgF, width, i);
    tImg = QPixmap::fromImage(i);
}
