//
// Created by 俵京佑 on 2018/10/18.
//

#include "ImageProcessingHistogramExtension.h"

ImageProcessingHistogramExtension::ImageProcessingHistogramExtension
        (Image* src_image,
         Image* dst_image,
         UINT neglect_threshold)
        : ImageProcessingUsingResultTable(src_image,
                                          dst_image),
          neglect_threshold(neglect_threshold)
{
    // malloc anyway
    max_pixel = new BYTE[byte_per_pixel];
    min_pixel = new BYTE[byte_per_pixel];
    this->result_table = new BYTE*[byte_per_pixel];
    for(int byte_num = 0; byte_num < byte_per_pixel; byte_num++){
        result_table[byte_num] = new BYTE[EIGHT_BITS_GRADATION_NUM];
    }

    // initialize
    src_image->calcHistogram();

    // set minimum pixel value
    UINT frequency;
    for(UINT byte_num = 0; byte_num < byte_per_pixel; byte_num++){
        for(UINT pixel_value = 0; pixel_value < EIGHT_BITS_GRADATION_NUM; pixel_value++){
            frequency = src_image->getFrequencyOfPixelValue(pixel_value, byte_num);
            if(frequency >= neglect_threshold){
                min_pixel[byte_num] = (BYTE)pixel_value;
                break;
            }
        }
    }

    // set max pixel value
    for(UINT byte_num = 0; byte_num < byte_per_pixel; byte_num++){
        for(UINT pixel_value = BYTE_MAX; pixel_value >= 0; pixel_value--){
            frequency = src_image->getFrequencyOfPixelValue(pixel_value, byte_num);
            if(frequency >= neglect_threshold){
                max_pixel[byte_num] = (BYTE)pixel_value;
                break;
            }
        }
    }

    // create result table
    double result_temp;
    for(UINT byte_num = 0; byte_num < byte_per_pixel; byte_num++) {
        for (int i = 0; i < EIGHT_BITS_GRADATION_NUM; i++) {
            result_temp =
                    (double) BYTE_MAX
                    *((double) i - (double) min_pixel[byte_num])
                    /((double) max_pixel[byte_num] - (double) min_pixel[byte_num]);
            if (result_temp > BYTE_MAX) result_temp = BYTE_MAX;
            if (result_temp < 0) result_temp = 0;
            result_table[byte_num][i] = (BYTE) result_temp;
        }
    }
}

void ImageProcessingHistogramExtension::execute(){
    // declaration
    Image* source = src_base;
    Image* destination = dst_base;
    BYTE pixel_data;

    // processing
    for(UINT row = 0; row < height; row++){
        for(UINT col = 0; col < width; col++){
            for(UCHAR byte_num = 0; byte_num < byte_per_pixel; byte_num++){
                // gamma correction
                pixel_data = source->getPixelByte(row, col, byte_num);
                pixel_data = result_table[byte_num][pixel_data];
                // set the data to dst_base
                destination->setPixelByte(row, col, pixel_data, byte_num);
            }
        }
    }
}

ImageProcessingHistogramExtension::~ImageProcessingHistogramExtension() {
    delete[] max_pixel;
    delete[] min_pixel;
    for(int byte_num = 0; byte_num < byte_per_pixel; byte_num++){
        delete[] result_table[byte_num];
    }
    delete[] result_table;
}