//
// Created by 俵京佑 on 2018/10/17.
//

#ifndef IMAGEPROCESSING_IMAGEPROCESSINGGAMMACORRECTION_H
#define IMAGEPROCESSING_IMAGEPROCESSINGGAMMACORRECTION_H

#include "ImageProcessingUsingResultTable.h"

class ImageProcessingGammaCorrection : public ImageProcessingUsingResultTable
{
private:
    double gamma;
public:
    ImageProcessingGammaCorrection(Image* src_image, Image* dst_image, double gamma);
    ~ImageProcessingGammaCorrection() override = default;
};


#endif //IMAGEPROCESSING_IMAGEPROCESSINGGAMMACORRECTION_H
