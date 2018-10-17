//
// Created by 俵京佑 on 2018/09/25.
//

#ifndef IMAGEPROCESSING_PROCESSSTRATEGYCONTRASTCONVERSION_H
#define IMAGEPROCESSING_PROCESSSTRATEGYCONTRASTCONVERSION_H

#include "../ImageProcessing.h"
#include "../Image.h"

class ImageProcessingContrastConversion : public ImageProcessing
{
private:
    double gain;
    double offset;
    Image* dst;
    Image* src;
    BYTE result_table[EIGHT_BITS_GRADATION_NUM]; // computed in constructor
public:
    ImageProcessingContrastConversion(Image* src_image, Image* dst_image, double gain, double offset);
    void execute() override;
    ~ImageProcessingContrastConversion() override;
};


#endif //IMAGEPROCESSING_PROCESSSTRATEGYCONTRASTCONVERSION_H
