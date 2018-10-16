//
// Created by 俵京佑 on 2018/10/17.
//

#ifndef IMAGEPROCESSING_IMAGEPROCESSINGGAMMACORRECTION_H
#define IMAGEPROCESSING_IMAGEPROCESSINGGAMMACORRECTION_H


#include "../ImageProcessing.h"

class ImageProcessingGammaCorrection : public ImageProcessing
{
private:
    Image* dst;
    Image* src;
    double gamma;
    BYTE result_table[BYTE_MAX + 1]; // computed in constructor
public:
    ImageProcessingGammaCorrection(Image* src_image, Image* dst_image, double gamma);
    void execute() override;
    ~ImageProcessingGammaCorrection() override;
};


#endif //IMAGEPROCESSING_IMAGEPROCESSINGGAMMACORRECTION_H
