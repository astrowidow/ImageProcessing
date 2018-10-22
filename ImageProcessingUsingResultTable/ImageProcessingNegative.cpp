//
// Created by 俵京佑 on 2018/10/22.
//

#include "ImageProcessingNegative.h"

ImageProcessingNegative::ImageProcessingNegative
        (Image* src_image,
         Image* dst_image)
        : ImageProcessingUsingResultTable(src_image,
                                          dst_image)
{
    for(int i = 0; i < EIGHT_BITS_GRADATION_NUM; i++){
        result_table[i] = BYTE_MAX - i;
    }
}