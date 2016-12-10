#ifndef FILTER_HPP
#define FILTER_HPP

#include <vector>

class QImage;

void makeGray(const QImage& src, std::vector<float>& dst);

void makeImage(const std::vector<float>& src, int width,
               QImage& dst);

void filterConv(const std::vector<float>& src, int width,
                const float* mask, int radius,
                std::vector<float>& dst);

void genGauss(float sigma, std::vector<float>& mask, int& radius);

void filterSobel(const std::vector<float>& src, int width,
                 bool vertical,
                 std::vector<float>& dst);

#endif // FILTER_HPP
