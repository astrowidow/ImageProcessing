//
// Created by 俵京佑 on 2018/10/18.
//

#ifndef IMAGEPROCESSING_IMAGEPROCESSINGHISTOGRAMEXTENSION_H
#define IMAGEPROCESSING_IMAGEPROCESSINGHISTOGRAMEXTENSION_H

#include "../ImageProcessing.h"

class ImageProcessingHistogramExtension : public ImageProcessing
{
private:
    double gain;
    double offset;
public:
    ImageProcessingHistogramExtension(Image* src_image, Image* dst_image, double gain, double offset);
    ~ImageProcessingHistogramExtension() override = default;
};


#endif //IMAGEPROCESSING_IMAGEPROCESSINGHISTOGRAMEXTENSION_H
