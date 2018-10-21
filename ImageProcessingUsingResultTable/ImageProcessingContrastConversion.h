//
// Created by 俵京佑 on 2018/09/25.
//

#ifndef IMAGEPROCESSING_PROCESSSTRATEGYCONTRASTCONVERSION_H
#define IMAGEPROCESSING_PROCESSSTRATEGYCONTRASTCONVERSION_H

#include "../Image.h"
#include "ImageProcessingUsingResultTable.h"

class ImageProcessingContrastConversion : public ImageProcessingUsingResultTable
{
private:
    double gain;
    double offset;
public:
    ImageProcessingContrastConversion(Image* src_image, Image* dst_image, double gain, double offset);
    ~ImageProcessingContrastConversion() override = default;
};


#endif //IMAGEPROCESSING_PROCESSSTRATEGYCONTRASTCONVERSION_H
