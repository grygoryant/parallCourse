#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <vector>
#include <QPixmap>

struct Image {
    void setImage(const QPixmap& img);
    void setImage(const std::vector<float>& img, int width);

    const QPixmap& image() const { return tImg; }
    const std::vector<float>& imageF() const { return tImgF; }

private:
    QPixmap tImg;
    std::vector<float> tImgF;
};

#endif // IMAGE_HPP
