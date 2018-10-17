//
// Created by 俵京佑 on 2018/10/18.
//

#ifndef IMAGEPROCESSING_IMAGEPROCESSINGHISTOGRAMEXTENSION_H
#define IMAGEPROCESSING_IMAGEPROCESSINGHISTOGRAMEXTENSION_H


#include "../ImageProcessing.h"

class ImageProcessingHistogramExtension : public ImageProcessing
{
private:
    Image* dst;
    Image* src;
    // ignore_threshold:
    // if the number of max (or min) pixel is lower than this number,
    // the max value is ignored
    UINT ignore_threshold = 0;
    BYTE max_value;
    BYTE min_value;
    BYTE result_table[EIGHT_BITS_GRADATION_NUM]; // computed in constructor
public:
    ImageProcessingHistogramExtension(Image* src_image,
                                      Image* dst_image);
    void execute() override;
    ~ImageProcessingHistogramExtension() override;
};


#endif //IMAGEPROCESSING_IMAGEPROCESSINGHISTOGRAMEXTENSION_H
