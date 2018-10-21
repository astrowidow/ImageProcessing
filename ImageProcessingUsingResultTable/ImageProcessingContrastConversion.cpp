//
// Created by 俵京佑 on 2018/09/25.
//

#include "ImageProcessingContrastConversion.h"
#include "../Image.h"

ImageProcessingContrastConversion::ImageProcessingContrastConversion
        (Image* src_image,
         Image* dst_image,
         double gain,
         double offset)
        : ImageProcessingUsingResultTable(src_image,
                          dst_image),
          gain(gain), offset(offset)
{
    double result_temp;
    for(int i = 0; i < EIGHT_BITS_GRADATION_NUM; i++){
        result_temp = gain*(double)i + offset;
        if(result_temp > SATURATED_PIXEL) result_temp = SATURATED_PIXEL;
        if(result_temp < 0) result_temp = 0;
        result_table[i] = (BYTE)result_temp;
    }
}