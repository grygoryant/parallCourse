#include "filter.hpp"
#include <cmath>
#include <QImage>

void makeGray(const QImage &src, std::vector<float> &dst) {
    std::vector<float> buf;
    if (!src.isNull() && src.width() * src.height() > 0) {
        buf.resize(src.width() * src.height());
        for (int i = 0, y = 0, h = src.height(); y < h; ++y) {
            const QRgb* ln = (const QRgb*)src.scanLine(y);
            for (int x = 0, w = src.width(); x < w; ++x, ++i) {
                QRgb c = ln[x];
                buf[i] = (qRed(c) * 11.f + qGreen(c) * 16.f
                        + qBlue(c) * 5.f) * 0.03125f;
            }
        }
    }
    dst.swap(buf);
}

void makeImage(const std::vector<float> &src, int width,
               QImage &dst)
{
    QImage buf;
    if (!src.empty() && width > 0 && src.size() % width == 0) {
        int height = src.size() / width;
        buf = QImage(width, height, QImage::Format_RGB32);
        for (int i = 0, y = 0; y < height; ++y) {
            QRgb* ln = (QRgb*)buf.scanLine(y);
            for (int x = 0; x < width; ++x, ++i) {
                int c = int(qBound(0.f, src[i], 255.f));
                ln[x] = qRgb(c, c, c);
            }
        }
    }
    dst = buf;
}

void filterConv(const std::vector<float> &src, int width,
                const float *mask, int radius, std::vector<float> &dst)
{
    std::vector<float> buf;
    if (!src.empty() && width > 0 && src.size() % width == 0
            && mask && radius >= 0)
    {
        buf.resize(src.size(), 0);
        int maskWidth = radius * 2 + 1;
        int height = src.size() / width;
        if (maskWidth <= width && maskWidth <= height) {
            int size = maskWidth * maskWidth;
            int maxD = radius * width + radius;
            int yStep = width - maskWidth;

            for (int y = radius, yEnd = height - radius, imgI = maxD;
                 y < yEnd; ++y, imgI += radius + radius)
            {
                for (int x = radius, xEnd = width - radius; x < xEnd;
                     ++x, ++imgI)
                {
                    float val = 0;
                    for (int maskI = 0, curI = imgI - maxD;
                         maskI < size; curI += yStep)
                    {
                        for (int maskX = -radius; maskX <= radius;
                             ++maskX, ++maskI, ++curI)
                        {
                            val += src[curI] * mask[maskI];
                        }
                    }
                    buf[imgI] = val;
                }
            }

        }
    }
    buf.swap(dst);
}

void genGauss(float sigma, std::vector<float> &mask, int &radius) {
    std::vector<float> buf;
    radius = qMax(int(ceil(sigma * 3)), 0);
    if (radius > 0) {
        int w = radius * 2 + 1;
        buf.resize(w * w);
        float k1 = 1 / (2 * sigma * sigma);
        float k2 = k1 / (atan(1) * 4);
        k1 = -k1;
        float sum = 0;
        for (int y = -radius, i = 0; y <= radius; ++y) {
            for (int x = -radius; x <= radius; ++x, ++i) {
                buf[i] = k2 * exp((x * x + y * y) * k1);
                sum += buf[i];
            }
        }
        sum = 1 / sum;
        for (float& val : buf) {
            val *= sum;
        }
    }
    buf.swap(mask);
}

void filterSobel(const std::vector<float> &src, int width,
                 bool vertical,
                 std::vector<float> &dst)
{
    std::vector<float> buf;
    if (!src.empty() && width > 0 && src.size() % width == 0) {
        buf.resize(src.size(), 0);
        int height = src.size() / width;
        if (3 <= width && 3 <= height) {
            auto filterFunc = vertical ?
                        [](const float* s, int w) -> float {
                            return s[1 - w] + 2 * s[1] + s[1 + w]
                                    - s[-1 - w] - 2 * s[-1] - s[w - 1];
                        }
                        :
                        [](const float* s, int w) -> float {
                            return s[w - 1] + 2 * s[w] + s[w + 1]
                                    - s[-1 - w] - 2 * s[-w] - s[1 - w];
                        };

            for (int y = 1, yEnd = height - 1, imgI = width + 1;
                 y < yEnd; ++y, imgI += 2)
            {
                for (int x = 1, xEnd = width - 1; x < xEnd;
                     ++x, ++imgI)
                {
                    buf[imgI] = filterFunc(src.data() + imgI, width);
                }
            }
        }
    }
    buf.swap(dst);
}
