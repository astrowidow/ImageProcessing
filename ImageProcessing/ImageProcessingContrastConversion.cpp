//
// Created by 俵京佑 on 2018/09/25.
//

#include "ImageProcessingContrastConversion.h"
#include "../Image.h"

ImageProcessingContrastConversion::ImageProcessingContrastConversion
        (Image* src_image,
         Image* dst_image,
         double gain,
         double offset) : ImageProcessing(src_image->getHeight(), src_image->getWidth()), gain(gain), offset(offset)
{
    src = src_image;
    dst = dst_image;

    double result_temp;
    for(int i = 0; i < EIGHT_BITS_GRADATION_NUM; i++){
        result_temp = gain*(double)i + offset;
        if(result_temp > SATURATED_PIXEL) result_temp = SATURATED_PIXEL;
        if(result_temp < 0) result_temp = 0;
        result_table[i] = (BYTE)result_temp;
    }
}

void ImageProcessingContrastConversion::execute()
{
    // declaration
    Image* source = src;
    Image* destination = dst;
    UINT byte_per_pixel = source->getBytePerPix();
    BYTE pixel_data;

    // processing
    for(UINT row = 0; row < height; row++){
        for(UINT col = 0; col < width; col++){
            for(UCHAR byte_num = 0; byte_num < byte_per_pixel; byte_num++){
                // linear contrast conversion
                pixel_data = source->getPixelByte(row, col, byte_num);
                pixel_data = result_table[pixel_data];
                // set the data to dst
                destination->setPixelByte(row, col, (BYTE)pixel_data, byte_num);
            }
        }
    }
}

ImageProcessingContrastConversion::~ImageProcessingContrastConversion(){
    // do nothing
}