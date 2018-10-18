//
// Created by 俵京佑 on 2018/10/17.
//

#include <cmath>
#include "ImageProcessingGammaCorrection.h"

ImageProcessingGammaCorrection::ImageProcessingGammaCorrection
        (Image* src_image,
         Image* dst_image,
         double gamma)
        : ImageProcessing(src_image,
                          dst_image),
          gamma(gamma)
{
    double base;
    for(int i = 0; i < EIGHT_BITS_GRADATION_NUM; i++){
        base = (double)i/BYTE_MAX;
        result_table[i] = (BYTE) (pow(base, 1.0/gamma)*BYTE_MAX);
    }
}