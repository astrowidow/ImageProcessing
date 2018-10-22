//
// Created by 俵京佑 on 2018/10/22.
//

#include "ImageProcessingSolarization.h"

ImageProcessingSolarization::ImageProcessingSolarization
        (Image* src_image,
         Image* dst_image,
        double wave_num)
        : ImageProcessingUsingResultTable(src_image,
                                          dst_image),
          wave_num(wave_num)
{
    double wave_width = (double)BYTE_MAX/wave_num;
    double saw_width = wave_width/2;

    int j;
    double result_temp;
    for(int i = 0; i < EIGHT_BITS_GRADATION_NUM; i++){
        j = i%(int)wave_width;

        if(j <= saw_width) {
            result_temp = (double)(j * BYTE_MAX) / saw_width;
        }
        else{
            result_temp = -((j - wave_width)*BYTE_MAX)/saw_width;
        }

        result_temp > BYTE_MAX  ? result_temp = BYTE_MAX   : result_temp;
        result_temp < 0         ? result_temp = 0          : result_temp;

        result_table[i] = (BYTE) result_temp;
    }
}