//
// Created by 俵京佑 on 2018/10/17.
//

#include <cmath>
#include "ImageProcessingGammaCorrection.h"

ImageProcessingGammaCorrection::ImageProcessingGammaCorrection
        (Image* src_image,
         Image* dst_image,
         double gamma) : ImageProcessing(src_image->getHeight(), src_image->getWidth()), gamma(gamma)
{
    src = src_image;
    dst = dst_image;

    double base;
    for(int i = 0; i < EIGHT_BITS_GRADATION_NUM; i++){
        base = (double)i/BYTE_MAX;
        result_table[i] = (BYTE) (pow(base, 1.0/gamma)*BYTE_MAX);
    }
}

void ImageProcessingGammaCorrection::execute()
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
                // gamma correction
                pixel_data = source->getPixelByte(row, col, byte_num);
                pixel_data = result_table[pixel_data];
                // set the data to dst
                destination->setPixelByte(row, col, (BYTE)pixel_data, byte_num);
            }
        }
    }
}

ImageProcessingGammaCorrection::~ImageProcessingGammaCorrection(){
    // do nothing
}