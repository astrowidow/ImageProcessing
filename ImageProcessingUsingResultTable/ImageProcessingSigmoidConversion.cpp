//
// Created by 俵京佑 on 2018/10/22.
//

#include "ImageProcessingSigmoidConversion.h"
#include <cmath>

ImageProcessingSigmoidConversion::ImageProcessingSigmoidConversion
        (Image* src_image,
         Image* dst_image,
         double gamma)
        : ImageProcessingUsingResultTable(src_image,
                                          dst_image),
          gamma(gamma)
{
    double index;
    for(int i = 0; i < EIGHT_BITS_GRADATION_NUM; i++){
        index = -gamma*((double)i - (double)BYTE_MAX/2);
        result_table[i] = (BYTE)((double)BYTE_MAX/(1 + exp(index)));
    }
}