//
// Created by 俵京佑 on 2018/09/25.
//

#ifndef IMAGEPROCESSING_PROCESSSTRATEGYCONTRASTCONVERSION_H
#define IMAGEPROCESSING_PROCESSSTRATEGYCONTRASTCONVERSION_H

#include "../ImageProcessing.h"
#include "../Bitmap.h"

class ImageProcessingContrastConversion : public ImageProcessing
{
private:
    double gain;
    double offset;
    Image* dst;
    Image* src;
    Pixel* pixel;
public:
    ImageProcessingContrastConversion(Image* src_image, Image* dst_image, double gain, double offset);
    void execute() override;
    ~ImageProcessingContrastConversion() override;
};


#endif //IMAGEPROCESSING_PROCESSSTRATEGYCONTRASTCONVERSION_H
