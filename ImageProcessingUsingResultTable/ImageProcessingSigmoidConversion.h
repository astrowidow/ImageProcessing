//
// Created by 俵京佑 on 2018/10/22.
//

#ifndef IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGSIGMOIDCONVERSION_H
#define IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGSIGMOIDCONVERSION_H


#include "ImageProcessingUsingResultTable.h"

class ImageProcessingSigmoidConversion : public ImageProcessingUsingResultTable
{
private:
    double gamma;
public:
    ImageProcessingSigmoidConversion(Image* src_image, Image* dst_image, double gamma);
    ~ImageProcessingSigmoidConversion() override = default;
};


#endif //IMAGEPROCESSINGUSINGRESULTTABLE_IMAGEPROCESSINGSIGMOIDCONVERSION_H
